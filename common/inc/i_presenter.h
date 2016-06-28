//
// Created by akomandyr on 24.06.16.
//

#ifndef I_PRESENTER_H
#define I_PRESENTER_H

#include "common_types.h"

class IPresenter
{
public:

    virtual ErrorCode StartScan(const std::string& startLink, int maxWorkers, const std::string& searchText, int maxURLs) = 0;
    virtual ErrorCode StopScan() = 0;
    virtual ErrorCode Pause() = 0;

    virtual ~IPresenter(){}
};
typedef std::weak_ptr<IPresenter> IPresenterPtr;
#endif //HTML_PARSER_TEST_I_PRESENTER_H
