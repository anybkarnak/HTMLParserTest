//
// Created by akomandyr on 24.06.16.
//

#include <iterator>
#include <curl/curl.h>
#include <sstream>
#include <algorithm>
#include "parser_model.h"


static std::set<std::string> links;

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
}


ErrorCode ParserModel::StartScan(const std::string& startLink, int maxWorkers,
                                 const std::string& searchText, int maxURLs)
{
    m_startLink = startLink;
    m_searchText = searchText;
    m_maxWorkers = maxWorkers;
    m_maxURLs = maxURLs;
    //init thread pool


    NotifyObservers(GetPageChildren(startLink));

    return ErrorCode::SUCCESS;
}

ErrorCode ParserModel::StopScan()
{
    m_startLink = "";
    m_searchText = "";
    m_maxWorkers = 0;
    m_maxURLs = 0;

    return ErrorCode::SUCCESS;
}

ErrorCode ParserModel::Pause()
{
    return ErrorCode::SUCCESS;
}

ParserModel::~ParserModel()
{

}

std::string ParserModel::GetResult(const std::string& pageContent, const std::string sample)
{
    if (pageContent.find(sample) != std::string::npos)
    {
        return "found";
    }
    else
    {
        return "not found";
    }
}


EntitiesList ParserModel::GetPageChildren(const std::string& url) const
{
    const std::string data = GetPageContent(url);

    std::string beginLink = "http://";
    std::vector<std::string> endLinks{ "\"", ">", "\'" };

    std::string::size_type start_pos = 0;
    std::string::size_type end_pos = 0;

    while (std::string::npos !=
           (start_pos = data.find(beginLink, start_pos)))
    {
        end_pos = data.find(endLinks[2], start_pos);
        for(auto&endLink:endLinks)
        {
            std::string::size_type tmpPos = data.find(endLink, start_pos);
            end_pos = std::min(end_pos,tmpPos);
        }
        //end_pos = data.find(endLinks[0], start_pos);
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
            out << stderr<<"curl_easy_perform() failed:"<<curl_easy_strerror(res);
            content = out.str();
        }
    }

    return content;
}

/*
 * Notify observers about entities statuses
 */
ErrorCode ParserModel::NotifyObservers(const EntitiesList& entities)
{
    for (auto& obs:m_observersList)
    {
        IObserverPtr observer;

        if (observer = obs.lock())
        {
            return observer->UpdateEntities(entities);
        }
        else
        {
            return ErrorCode::ERROR;
        }
    }
}