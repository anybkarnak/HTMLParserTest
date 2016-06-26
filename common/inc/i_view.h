//
// Created by akomandyr on 24.06.16.
//

#ifndef I_VIEW_H
#define I_VIEW_H
#include "common_types.h"

class IView
{
public:
    ErrorCode UpdateEntities(const EntitiesList& entities);
    ~IView(){}
};

typedef std::shared_ptr<IView> IViewPtr;

#endif //HTML_PARSER_TEST_I_VIEW_H
