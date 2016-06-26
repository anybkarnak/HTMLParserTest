//
// Created by akomandyr on 24.06.16.
//

#ifndef I_OBSERVER_H
#define I_OBSERVER_H

#include "common_types.h"

class IObserver
{
    ErrorCode UpdateEntities(const EntitiesList& entities);
};
typedef std::weak_ptr<IObserver> IObserverWptr;
#endif //HTML_PARSER_TEST_I_OBSERVER_H
