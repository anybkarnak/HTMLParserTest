//
// Created by akomandyr on 24.06.16.
//

#include "presenter.h"

Presenter::Presenter(IModelPtr model) : m_model(model)
{
}

ErrorCode Presenter::StartScan(const std::string &startLink, int maxWorkers, const std::string &searchText, int maxURLs)
{
    return m_model->StartScan(startLink, maxWorkers, searchText, maxURLs);
}

ErrorCode Presenter::StopScan()
{
    return m_model->StopScan();
}

ErrorCode Presenter::Pause()
{
    return m_model->Pause();
}

ErrorCode Presenter::UpdateEntities(const EntitiesList &entities)
{
    for (auto &view:m_views)
    {
        view->UpdateEntities(entities);
    }
}

ErrorCode Presenter::AddView(IViewPtr view)
{
    m_views.push_back(view);
}