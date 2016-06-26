//
// Created by akomandyr on 24.06.16.
//

#ifndef I_OBSERVER_H
#define I_OBSERVER_H

#include "common_types.h"

class IObserver
{
public:
    virtual ErrorCode UpdateEntities(const EntitiesList& entities) = 0;
    virtual ~IObserver(){}
};

typedef std::weak_ptr<IObserver> IObserverWptr;
typedef std::shared_ptr<IObserver> IObserverPtr;
#endif //HTML_PARSER_TEST_I_OBSERVER_H
