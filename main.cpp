//
// Created by akomandyr on 24.06.16.
//

#include <iostream>
#include <i_view.h>
#include <qt_view.h>
#include "presenter.h"
#include "parser_model.h"
#include <QApplication>


int main(int argc,      // Number of strings in array argv
         char* argv[])  // Array of command-line argument strings
{
    int count;
// Display each command-line argument.
    std::cout << "\nCommand-line arguments:\n";
    for (count = 0; count < argc; count++)
        std::cout << "  argv[" << count << "]   "
        << argv[count] << "\n\n";

    QApplication a(argc, argv);

    ParserModelPtr model = std::make_shared<ParserModel>();
    QTViewPtr view = std::make_shared<QTView>();
    PresenterPtr presenter = std::make_shared<Presenter>(model);
    presenter->AddView(view);
    model->AddObserver(presenter);
    view->SetPresenter(presenter);

    view->show();

    return a.exec();

    //
    //return 0;
}