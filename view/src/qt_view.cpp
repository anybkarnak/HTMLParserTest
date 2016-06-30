//
// Created by akomandyr on 24.06.16.
//

#include <iostream>
#include "qt_view.h"
#include <QtWidgets>
#include <thread>
#include <chrono>

static const std::string StartButtonName = "&START";
static const std::string StopButtonName = "&STOP";
static const std::string PauseButtonName = "&PAUSE";

ErrorCode QTView::UpdateEntities(const EntitiesList& entities)
{

    for (auto& ent:entities)
    {
        auto it = find_if(m_entList.begin(), m_entList.end(),
                          [ &ent ](Entity m_ent)
                          {
                              return m_ent.link.compare(ent.link) == 0;
                          });

        if (it != std::end(m_entList))
        {
            it->status = ent.status;
        }
        else
        {
            m_entList.push_back(ent);
            //std::cout << "Error occured, process entity, which is not a some child" << std::endl;
        }
    }

    //m_searchStatusTable->setRowCount(0);
    //m_searchStatusTable->clear();


    // std::shared_ptr<QTableWidgetItem> linkItem;
    //  std::shared_ptr<QTableWidgetItem> statusItem;
    for (auto& entity:m_entList)
    {
        //change existing table item
        int rows = m_searchStatusTable->rowCount();
        bool isChanged = false;
        for(int i = 0 ; i<rows; ++i)
        {
            if(m_searchStatusTable->item(i,0)->text().toStdString().compare(entity.link)==0)
            {
                isChanged = true;
                m_searchStatusTable->item(i,1)->setText(tr(entity.status.c_str()));
            }
        }
        //add new item to table
        if(!isChanged)
        {
            QTableWidgetItem* linkItem = new QTableWidgetItem(tr(entity.link.c_str()));
            linkItem->setFlags(linkItem->flags());

            QTableWidgetItem* statusItem = new QTableWidgetItem(tr(entity.status.c_str()));
            statusItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            statusItem->setFlags(statusItem->flags());

            m_searchStatusTable->insertRow(rows);
            m_searchStatusTable->setItem(rows, 0, linkItem);
            m_searchStatusTable->setItem(rows, 1, statusItem);
        }

        //delete linkItem;
        //delete statusItem;
        //std::cout << "URL  " << entity.link << "   status =  " << entity.status << std::endl;
    }
    //update view on the table
    m_searchStatusTable->reset();
    return ErrorCode::_SUCCESS;
}

ErrorCode QTView::SetPresenter(IPresenterPtr presenter)
{
    m_presenter = presenter;

    return ErrorCode::_SUCCESS;
}

QTView::~QTView()
{

}

void QTView::Start()
{
    std::shared_ptr<IPresenter> presenter;
    if (presenter = m_presenter.lock())
    {
        std::string startLink = m_startUrlEdit->text().toStdString();
        int maxWorkers = m_numberOfWorkersEdit->text().toInt();
        std::string searchText = m_textSearchSampleEdit->text().toStdString();
        int maxURLs = m_numberofMaxURLsEdit->text().toInt();
        //m_searchStatusTable->clear();
        presenter->StartScan(startLink, maxWorkers, searchText, maxURLs);

        m_startButton->setDisabled(true);

    }
    else
    {
        std::cout << "Presenter Error" << std::endl;
    }
}

void QTView::Stop()
{
    std::shared_ptr<IPresenter> presenter;
    if (presenter = m_presenter.lock())
    {
        presenter->StopScan();
        //wait for threads, which use an table and ent list (need w8 just one notiffy)
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        m_searchStatusTable->setRowCount(0);
        m_searchStatusTable->clear();
        m_entList.clear();

        m_startButton->setEnabled(true);
        QStringList labels;
        labels << tr("URL") << tr("STATUS");
        m_searchStatusTable->setHorizontalHeaderLabels(labels);
        //m_items.clear();
    }
    else
    {
        std::cout << "Presenter Error" << std::endl;
    }

}

void QTView::Pause()
{
    std::shared_ptr<IPresenter> presenter;
    if (presenter = m_presenter.lock())
    {
        presenter->Pause();
    }
    else
    {
        std::cout << "Presenter Error" << std::endl;
    }
}


//! [0]
QTView::QTView(QWidget* parent)
        :QWidget(parent)
{

    //! [1]
    QGridLayout* mainLayout = new QGridLayout;



    //labels
    m_startUrlLabel = new QLabel(tr("Start URL:"));
    m_numberOfWorkersLabel = new QLabel(tr("Max threads:"));
    m_textSearchSampleLabel = new QLabel(tr("Text Sample:"));
    m_numberofMaxURLsLabel = new QLabel(tr("Max URL:"));

    mainLayout->addWidget(m_startUrlLabel, 0, 0);
    mainLayout->addWidget(m_numberOfWorkersLabel, 1, 0);
    mainLayout->addWidget(m_textSearchSampleLabel, 2, 0);
    mainLayout->addWidget(m_numberofMaxURLsLabel, 3, 0);

    //text areas
    m_startUrlEdit = new QLineEdit();
    m_numberOfWorkersEdit = new QLineEdit();
    m_numberOfWorkersEdit->setValidator(new QIntValidator(0, INT32_MAX, this));
    m_textSearchSampleEdit = new QLineEdit();
    m_numberofMaxURLsEdit = new QLineEdit();
    m_numberofMaxURLsEdit->setValidator(new QIntValidator(0, INT32_MAX, this));

    mainLayout->addWidget(m_startUrlEdit, 0, 1);
    mainLayout->addWidget(m_numberOfWorkersEdit, 1, 1);
    mainLayout->addWidget(m_textSearchSampleEdit, 2, 1);
    mainLayout->addWidget(m_numberofMaxURLsEdit, 3, 1);

    //buttons
    m_startButton = new QPushButton(tr(StartButtonName.c_str()), this);
    connect(m_startButton, &QAbstractButton::clicked, this, &QTView::Start);

    m_pauseButton = new QPushButton(tr(PauseButtonName.c_str()), this);
    connect(m_pauseButton, &QAbstractButton::clicked, this, &QTView::Pause);

    m_stopButton = new QPushButton(tr(StopButtonName.c_str()), this);
    connect(m_stopButton, &QAbstractButton::clicked, this, &QTView::Stop);

    mainLayout->addWidget(m_startButton, 4, 0);
    mainLayout->addWidget(m_pauseButton, 4, 1);
    mainLayout->addWidget(m_stopButton, 4, 2);

    //resultofsearchstatustable
    m_searchStatusTable;
    //has a 0rows and 2 cols
    m_searchStatusTable = new QTableWidget(0, 2);
    m_searchStatusTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList labels;
    labels << tr("URL") << tr("STATUS");
    m_searchStatusTable->setHorizontalHeaderLabels(labels);
    m_searchStatusTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_searchStatusTable->verticalHeader()->hide();
    m_searchStatusTable->setShowGrid(false);

//! [0]
    mainLayout->addWidget(m_searchStatusTable, 5, 0, 1, 2);

    setLayout(mainLayout);

    setWindowTitle(tr("Search Some Text In URL"));
    resize(700, 600);
}