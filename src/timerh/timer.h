/*
 * TimerH - A C++ library for timing code and formatting time.
 * Copyright (C) 2018-2019  UnexomWid

 * timer.h - Contains the declaration of the library.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <chrono>
#include <string>

#pragma once

#define CHRONOMETER std::chrono::high_resolution_clock::time_point
#define ULL unsigned long long

// Gets the current time.
CHRONOMETER time_now();

// Gets the execution time in hours.
ULL get_exec_time_h(CHRONOMETER start);
// Gets the execution time in minutes.
ULL get_exec_time_m(CHRONOMETER start);
// Gets the execution time in seconds.
ULL get_exec_time_s(CHRONOMETER start);
// Gets the execution time in milliseconds.
ULL get_exec_time_ms(CHRONOMETER start);
// Gets the execution time in microseconds.
ULL get_exec_time_mis(CHRONOMETER start);
// Gets the execution time in nanoseconds.
ULL get_exec_time_ns(CHRONOMETER start);

// Formats a number representing milliseconds as a string.
std::string format_time_ms(ULL milliseconds);
// Formats a number representing microseconds as a string.
std::string format_time_mis(ULL microseconds);
// Formats a number representing nanoseconds as a string.
std::string format_time_ns(ULL nanoseconds);

// Gets the formatted execution time with the precision of a millisecond.
std::string getf_exec_time_ms(CHRONOMETER start);
// Gets the formatted execution time with the precision of a microsecond.
std::string getf_exec_time_mis(CHRONOMETER start);
// Gets the formatted execution time with the precision of a nanosecond.
std::string getf_exec_time_ns(CHRONOMETER start);