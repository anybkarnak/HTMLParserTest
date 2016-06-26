//
// Created by akomandyr on 24.06.16.
//

#ifndef QT_VIEW_H
#define QT_VIEW_H

#include "i_view.h"

class QTView : public IView
{
public:
    virtual ErrorCode UpdateEntities(const EntitiesList& entities);

    ~QTView()
    { }
};


#endif //HTML_PARSER_TEST_QT_VIEW_H
