//
// Created by akomandyr on 24.06.16.
//

#ifndef I_MODEL_H
#define I_MODEL_H

#include "common_types.h"

class IModel
{
public:

    virtual ErrorCode StartScan(const std::string& startLink, int maxWorkers, const std::string& searchText, int maxURLs) = 0;
    virtual ErrorCode StopScan() = 0;
    virtual ErrorCode Pause() = 0;

    virtual ~IModel()
    { };
};

typedef std::shared_ptr<IModel> IModelPtr;

#endif //HTML_PARSER_TEST_I_MODEL_H
