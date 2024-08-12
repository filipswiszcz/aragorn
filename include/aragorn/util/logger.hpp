#include <iostream>

#include <string>
#include <sstream>
#include <ctime>

#ifndef LOGGER_H
#define LOGGER_H

#define RESET_CODE "\x1B[0m"
#define RED_CODE   "\x1B[31m"
#define BLUE_CODE  "\x1B[36m"

#define FORMAT_RED(x) RED_CODE << x << RESET_CODE
#define FORMAT_BLUE(x) BLUE_CODE << x << RESET_CODE

namespace util {

    enum color {

        RESET,
        RED,
        BLUE

    };

    class Logger {

        public:

            void info(const std::string& msg);

            void warning(const std::string& msg);

            void debug(const std::string& msg);

        private:

            std::string get_formatted_msg(const color color, const std::string& name, const std::string& msg);

    };

} // namespace util

#endif