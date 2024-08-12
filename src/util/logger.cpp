#include <aragorn/util/logger.hpp>

#pragma mark - Logger
#pragma region Logger {

using namespace util;

void Logger::info(const std::string& msg) {
    std::cout << this -> get_formatted_msg(RESET, "INFO", msg) << std::endl;
}

void Logger::warning(const std::string& msg) {
    std::cerr << this -> get_formatted_msg(RED, "WARNING", msg) << std::endl;
}

void Logger::debug(const std::string& msg) {
    std::cout << this -> get_formatted_msg(BLUE, "DEBUG", msg) << std::endl;
}

std::string Logger::get_formatted_msg(const color color, const std::string& name, const std::string& msg) {

    time_t curr_t = time(0);
    tm* local_tm = localtime(&curr_t);

    char ts[20];
    strftime(ts, sizeof(ts), "%Y/%m/%d %H:%M:%S", local_tm);

    std::ostringstream ln;
    ln << "[aragorn][" << ts << "]";

    switch (color) {
        case RESET:
            ln << "[" << name << "]: " << msg; break;
        case RED:
            ln << FORMAT_RED("[" << name << "]: " << msg); break;
        case BLUE:
            ln << FORMAT_BLUE("[" << name << "]: " << msg); break;
    }

    return ln.str();
}

#pragma endregion Logger }