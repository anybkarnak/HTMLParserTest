//
// Created by akomandyr on 24.06.16.
//

#ifndef HTML_PARSER_TEST_I_PRESENTER_H
#define HTML_PARSER_TEST_I_PRESENTER_H

class IPresenter
{
public:

    virtual ErrorCode StartScan(const std::string& startLink, int maxWorkers, const std::string& searchText, int maxURLs) = 0;
    virtual ErrorCode StopScan() = 0;
    virtual ErrorCode Pause() = 0;

    virtual ~IPresenter(){}
};

#endif //HTML_PARSER_TEST_I_PRESENTER_H
