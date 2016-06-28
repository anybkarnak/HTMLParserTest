//
// Created by akomandyr on 24.06.16.
//

#ifndef I_VIEW_H
#define I_VIEW_H
#include "common_types.h"

class IView
{
public:
    virtual ErrorCode UpdateEntities(const EntitiesList& entities) = 0;
    virtual ~IView(){}
};

typedef std::shared_ptr<IView> IViewPtr;

#endif //HTML_PARSER_TEST_I_VIEW_H
