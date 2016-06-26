//
// Created by akomandyr on 24.06.16.
//

#ifndef PRESENTER_H
#define PRESENTER_H

#include "i_observer.h"
#include "i_presenter.h"
#include "i_model.h"
#include "i_view.h"

class Presenter : public IObserver, public IPresenter
{
public:

    Presenter();
    ErrorCode UpdateEntities(const EntitiesList& entities);

private:
    IModelPtr m_model;
    std::vector<IViewPtr> m_views;
};

#endif //HTML_PARSER_TEST_PRESENTER_H
