#pragma once
#include <string>
#include "cbasetypes.hpp"
void performance_create(std::string name);
void performance_start(std::string name, const char* debug_file, const uintptr debug_line);
void performance_stop(std::string name, const char* debug_file, const uintptr debug_line);
int64 performance_get_milliseconds(std::string name);
uint64 performance_get_totalcount(std::string name);
void performance_report(std::string name, const char* debug_file, const uintptr debug_line);
void performance_destory(std::string name);
void performance_create_and_start(std::string name, const char* debug_file, const uintptr debug_line);
void performance_stop_and_report(std::string name, const char* debug_file, const uintptr debug_line);

#define performance_start(name) performance_start((name), __FILE__, static_cast<uintptr>(__LINE__))
#define performance_stop(name) performance_stop((name), __FILE__, static_cast<uintptr>(__LINE__))
#define performance_report(name) performance_report((name), __FILE__, static_cast<uintptr>(__LINE__))
#define performance_create_and_start(name) performance_create_and_start((name), __FILE__, static_cast<uintptr>(__LINE__))
#define performance_stop_and_report(name) performance_stop_and_report((name), __FILE__, static_cast<uintptr>(__LINE__))
