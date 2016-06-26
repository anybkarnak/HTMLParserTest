//
// Created by akomandyr on 24.06.16.
//

#include <iostream>
#include <i_view.h>
#include <qt_view.h>
#include "presenter.h"
#include "parser_model.h"


int main(int argc,      // Number of strings in array argv
         char* argv[])  // Array of command-line argument strings
{
    int count;
// Display each command-line argument.
    std::cout << "\nCommand-line arguments:\n";
    for (count = 0; count < argc; count++)
        std::cout << "  argv[" << count << "]   "
        << argv[count] << "\n\n";

    ParserModelPtr model = std::make_shared<ParserModel>();
    IViewPtr view = std::make_shared<QTView>();
    PresenterPtr presenter = std::make_shared<Presenter>(model);
    presenter->AddView(view);
    model->AddObserver(presenter);

    presenter->StartScan("http://www.gnu.org/software/libc/manual/html_node/Regular-Expressions.html", 0,"1",1);
    return 0;
}