//
// Created by akomandyr on 24.06.16.
//

#include <iostream>
#include "qt_view.h"

ErrorCode QTView::UpdateEntities(const EntitiesList& entities)
{
    for(auto &entity:entities)
    {
        std::cout<<"URL  "<<entity.link<<"status =  "<<entity.status<<std::endl;
    }
}