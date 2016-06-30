//
// Created by akomandyr on 24.06.16.
//

#include <iterator>
#include <curl/curl.h>
#include <sstream>
#include <algorithm>
#include "parser_model.h"
#include <thread>
#include <iostream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*) userp)->append((char*) contents, size * nmemb);
    return size * nmemb;
}


ParserModel::ParserModel():
        m_startLink(""),
        m_searchText(""),
        m_maxWorkers(0),
        m_maxURLs(0)
{

}

ErrorCode ParserModel::AddObserver(IObserverWptr observer)
{
    m_observersList.push_back(observer);

    return ErrorCode::_SUCCESS;
}

//it can be developed by ThreadPool, but it is inly a prototype=)
ErrorCode ParserModel::StartProcessing()
{
    while (!m_isPaused)
    {
        if (m_usedWorkers < m_maxWorkers)
        {
            std::string link = m_tasks.pop();
            if (!link.empty())
            {

                //debug solution
                //std::cout<<link<<std::endl;

                std::thread worker(&ParserModel::ProcessEntity, this, link);
                worker.detach();
            }
        }
    }

    return ErrorCode::_SUCCESS;
}

ErrorCode ParserModel::StartScan(const std::string& startLink, int maxWorkers,
                                 const std::string& searchText, int maxURLs)
{
    m_startLink = startLink;
    m_searchText = searchText;
    m_maxWorkers = maxWorkers;
    m_maxURLs = maxURLs;
    m_openURLs = 0;
    m_isPaused = false;
    m_usedWorkers = 0;
    //init tasks queue, get first links
    //ProcessEntity(m_startLink);
    std::thread t1(&ParserModel::ProcessEntity, this, m_startLink);
    t1.detach();

    std::thread t2(&ParserModel::StartProcessing, this);
    t2.detach();


    return ErrorCode::_SUCCESS;
}

ErrorCode ParserModel::StopScan()
{
    m_startLink = "";
    m_searchText = "";
    m_maxWorkers = 0;
    m_maxURLs = 0;
    m_usedWorkers = 0;
    m_openURLs = 0;
    m_isPaused = false;

    return ErrorCode::_SUCCESS;
}

ErrorCode ParserModel::Pause()
{
    if (m_isPaused)
    {
        std::thread t2(&ParserModel::StartProcessing, this);
        t2.detach();
        m_isPaused = false;
    }
    else
    {
        m_isPaused = true;
    }

    return ErrorCode::_SUCCESS;
}

ParserModel::~ParserModel()
{

}

std::string ParserModel::GetResult(const std::string& pageContent) const
{
    if (pageContent.find(m_searchText) != std::string::npos)
    {
        return "found";
    }
    else
    {
        if (pageContent.find("curl_easy_perform() failed") != std::string::npos)
        {
            return pageContent;
        }
        else
        {
            return "not found";
        }
    }
}

ErrorCode ParserModel::ProcessEntity(const std::string& url)
{
    //manage number of working threads =)prototype solution
    m_usedWorkers++;

    const std::string data = GetPageContent(url);

    Entity entity;
    entity.link = url;
    entity.status = GetResult(data);
    EntitiesList list{ entity };
    NotifyObservers(list);

    EntitiesList children = GetPageChildren(data);
    NotifyObservers(children);

    for (auto& ent:children)
    {
        //all chilrens of entity pushed into tasks queue
        m_tasks.push(ent.link);
    }

    m_usedWorkers--;
    return ErrorCode::_SUCCESS;
}

EntitiesList ParserModel::GetPageChildren(const std::string& data)
{
    std::set<std::string> links;

    std::string beginLink = "http://";
    std::vector<std::string> endLinks{ "\"", ">", "\'" };

    std::string::size_type start_pos = 0;
    std::string::size_type end_pos = 0;

    while (std::string::npos !=
           (start_pos = data.find(beginLink, start_pos)))
    {
        m_openURLs++;
        if (m_openURLs - 1 >= m_maxURLs)
        {
            break;
        }

        end_pos = data.find(endLinks[2], start_pos);
        for (auto& endLink:endLinks)
        {
            std::string::size_type tmpPos = data.find(endLink, start_pos);
            end_pos = (std::min)(end_pos, tmpPos);
        }

        unsigned int urlLen = end_pos - start_pos;
        std::string urlStr = data.substr(start_pos, urlLen);
        links.insert(urlStr);
        start_pos = end_pos;
    }

    EntitiesList list;

    for (auto& link:links)
    {
        Entity ent;
        ent.link = link;
        list.push_back(ent);

    }

    return list;
}

std::string ParserModel::GetPageContent(const std::string& url) const
{
    //each worker need locally copy of curl instance
    CURL* curl;
    CURLcode res;
    std::string content;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            std::ostringstream out;
            out << stderr << "curl_easy_perform() failed:" << curl_easy_strerror(res);
            content = out.str();
        }
    }

    return content;
}

/*
 * Notify observers about entities statuses
 */
ErrorCode ParserModel::NotifyObservers(const EntitiesList& entities) const
{
    std::lock_guard<std::mutex> lock(m_obsMutex);

    for (auto& obs:m_observersList)
    {
        IObserverPtr observer;

        if (observer = obs.lock())
        {
            return observer->UpdateEntities(entities);
        }
        else
        {
            return ErrorCode::_ERROR;
        }
    }

    return ErrorCode::_SUCCESS;
}
