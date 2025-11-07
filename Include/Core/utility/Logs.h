#pragma once
#include <format>  

static const char* RED = "\033[31m";
static const char* GREEN = "\033[32m";
static const char* YELLOW = "\033[33m";

static const char* BOLD = "\033[1m";
static const char* RESET = "\033[0m\n";


template<typename... Args>
void Error(std::format_string<Args...> format, Args&&... args) {
    auto formatted = std::format(format, std::forward<Args>(args)...);
    std::printf("%s %sError: %s %s", RED,BOLD ,formatted.c_str(),RESET);
}

template<typename... Args>
void Log(std::format_string<Args...> format, Args&&... args) {
    auto formatted = std::format(format, std::forward<Args>(args)...);
    std::printf("%s %sLog: %s %s", GREEN,BOLD ,formatted.c_str(),RESET);
}

template<typename... Args>
void Warn(std::format_string<Args...> format, Args&&... args) {
    auto formatted = std::format(format, std::forward<Args>(args)...);
	std::printf("%s %sWarn: %s %s", YELLOW,BOLD ,formatted.c_str(),RESET);
}
