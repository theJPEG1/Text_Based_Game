#ifndef PRETTYCOLORS_H
#define PRETTYCOLORS_H

#include <string>
    using std::string;
    
#include <iostream>
    using std::cout;

#include <iostream> // For console output (cout)
#include <thread>   // For std::this_thread::sleep_for
#include <chrono>   // For std::chrono::seconds


class PrettyColors
{
    public:
        string BLACK = "\033[30m";
        string RED = "\033[31m";
        string GREEN = "\033[32m";
        string YELLOW = "\033[33m";
        string BLUE = "\033[34m";
        string MAGENTA = "\033[35m";
        string CYAN = "\033[36m";
        string WHITE = "\033[37m";
        string DEFAULT = "\033[39m";

        void clearScreen() 
        {
            cout << "\033[2J\033[1;1H";
            cout.flush(); // Ensure the output is immediately sent to the terminal
        };

        void pauseTerminal(int seconds)
        {
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
        };
};

#endif