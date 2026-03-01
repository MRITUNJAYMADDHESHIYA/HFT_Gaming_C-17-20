#pragma once

#include<chrono>

// Returns the current Unix time in microseconds
inline u_int64_t unix_time(){
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void print_file_contents(std::string_view file_path);
void print_fill(std::pair<int,double> fill, int quantity,  u_int64_t start_time, u_int64_t end_time);
