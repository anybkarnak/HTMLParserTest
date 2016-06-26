//
// Created by akomandyr on 24.06.16.
//

#include <iterator>
#include <curl/curl.h>
#include <sstream>

#include "parser_model.h"


static std::set<std::string> links;


ParserModel::ParserModel() :
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


ErrorCode ParserModel::StartScan(const std::string &startLink, int maxWorkers,
                                 const std::string &searchText, int maxURLs)
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

std::string ParserModel::GetResult(const std::string &pageContent, const std::string sample)
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




EntitiesList ParserModel::GetPageChildren(const std::string &url) const
{
    const std::string data = GetPageContent(url);

    EntitiesList list;
    Entity ent1;
    ent1.link = data;
    list.push_back(ent1);
    Entity ent2;
    ent2.link = "_A";
    list.push_back(ent2);

//    for(auto& link:links)
//    {
//        Entity ent;
//        ent.link = link;
//        list.push_back(ent);
//    }

    return list;
}

std::string ParserModel::GetPageContent(const std::string &url) const
{
    CURL *curl;
    CURLcode res;
    std::string content;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::ostringstream out;
        out << res;

        content = out.str();
    }

    return content;
}

/*
 * Notify observers about entities statuses
 */
ErrorCode ParserModel::NotifyObservers(const EntitiesList &entities)
{
    for (auto &obs:m_observersList)
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