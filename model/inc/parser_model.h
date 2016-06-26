//
// Created by akomandyr on 24.06.16.
//

#ifndef PARSER_MODEL_H
#define PARSER_MODEL_H

#include "i_model.h"
#include "i_observer.h"
#include "page_scanner.h"

class ParserModel : public IModel
{
public:
    ParserModel();
    ErrorCode StartScan(const std::string& startLink, int maxWorkers, const std::string& searchText, int maxURLs);
    ErrorCode StopScan();
    ErrorCode Pause();
    ~ParserModel();

private:

    PageScannerPtr m_pageScanner;

    std::vector<IObserverWptr> m_observersList;

    std::string m_startLink;

    int m_maxWorkers;

    std::string m_searchText;

};

#endif //HTML_PARSER_TEST_PARSER_MODEL_H
