//
// Created by akomandyr on 24.06.16.
//

#ifndef QT_VIEW_H
#define QT_VIEW_H

#include "i_view.h"
#include "i_presenter.h"
#include <QWidget>
#include <QDir>
#include <mutex>
#include <utility>
#include <condition_variable>

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
class QLineEdit;
QT_END_NAMESPACE

//use standart example QWidget file searcher

class QTView : public QWidget, public IView
{
Q_OBJECT
public:

    explicit QTView(QWidget *parent = 0);
    virtual ErrorCode UpdateEntities(const EntitiesList& entities);
    ErrorCode SetPresenter(IPresenterPtr presenter);
    ~QTView();

private slots:

    void Start();
    void Stop();
    void Pause();

private:
    void Sync();
    void DrawTable();
    //buttons
    QPushButton*  m_startButton;
    QPushButton*  m_pauseButton;
    QPushButton*  m_stopButton;
    //text areas
    QLineEdit*    m_startUrlEdit;
    QLineEdit*    m_numberOfWorkersEdit;
    QLineEdit*    m_textSearchSampleEdit;
    QLineEdit*    m_numberofMaxURLsEdit;
    //labels
    QLabel*       m_startUrlLabel;
    QLabel*       m_numberOfWorkersLabel;
    QLabel*       m_textSearchSampleLabel;
    QLabel*       m_numberofMaxURLsLabel;
    //resultofsearchstatustable
    QTableWidget* m_searchStatusTable;

    //table rows
    std::map<std::shared_ptr<QTableWidgetItem>, std::shared_ptr<QTableWidgetItem> >  m_items;

    IPresenterPtr m_presenter;
    std::vector<Entity>  m_entList;

    std::condition_variable m_goodstopCond;
    std::mutex m_stopMutex;
    bool m_updateDone;
};
//! [0]
typedef std::shared_ptr<QTView> QTViewPtr;

#endif //HTML_PARSER_TEST_QT_VIEW_H
