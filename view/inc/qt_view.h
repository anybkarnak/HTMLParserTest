//
// Created by akomandyr on 24.06.16.
//

#ifndef QT_VIEW_H
#define QT_VIEW_H

#include "i_view.h"
#include "i_presenter.h"
#include <QWidget>
#include <QDir>

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

    IPresenterPtr m_presenter;
    std::set<Entity>  m_entList;
};
//! [0]
typedef std::shared_ptr<QTView> QTViewPtr;

#endif //HTML_PARSER_TEST_QT_VIEW_H
