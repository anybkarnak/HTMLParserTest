//
// Created by akomandyr on 24.06.16.
//

#include <iostream>

int main(int argc,      // Number of strings in array argv
         char* argv[])  // Array of command-line argument strings
{
    int count;
// Display each command-line argument.
    std::cout << "\nCommand-line arguments:\n";
    for (count = 0; count < argc; count++)
        std::cout << "  argv[" << count << "]   "
        << argv[count] << "\n";

    return 0;
}