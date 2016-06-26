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

    Presenter(IModelPtr model);
    ErrorCode AddView(IViewPtr view);
    virtual ErrorCode StartScan(const std::string& startLink, int maxWorkers, const std::string& searchText, int maxURLs);
    virtual ErrorCode StopScan();
    virtual ErrorCode Pause();
    ErrorCode UpdateEntities(const EntitiesList& entities);

private:
    IModelPtr m_model;
    std::vector<IViewPtr> m_views;
};

typedef std::shared_ptr<Presenter> PresenterPtr;
#endif //HTML_PARSER_TEST_PRESENTER_H
