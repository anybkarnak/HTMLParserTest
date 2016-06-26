//
// Created by akomandyr on 24.06.16.
//

#ifndef PARSER_MODEL_H
#define PARSER_MODEL_H

#include "i_model.h"
#include "i_observer.h"


class ParserModel : public IModel
{
public:
    ParserModel();
    ErrorCode AddObserver(IObserverWptr observer);
    virtual ErrorCode StartScan(const std::string& startLink, int maxWorkers, const std::string& searchText, int maxURLs);
    virtual ErrorCode StopScan();
    virtual ErrorCode Pause();
    ~ParserModel();

private:

    std::string GetResult(const std::string& pageContent, const std::string sample);
    EntitiesList GetPageChildren(const std::string& url) const;
    std::string GetPageContent(const std::string& url) const;
    /*
     * Notify observers about entities statuses
     */
    ErrorCode NotifyObservers(const EntitiesList& entities);

    std::vector<IObserverWptr> m_observersList;

    std::string m_startLink;

    int m_maxWorkers;

    std::string m_searchText;

    int m_maxURLs;
};

typedef std::shared_ptr<ParserModel> ParserModelPtr;
#endif //HTML_PARSER_TEST_PARSER_MODEL_H
