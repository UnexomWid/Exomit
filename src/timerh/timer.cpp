/*
 * TimerH - A C++ library for timing code and formatting time.
 * Copyright (C) 2018-2019  UnexomWid

 * timer.cpp - Contains the definition of the library.

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

#include "timer.h"

CHRONOMETER time_now()
{
	return std::chrono::high_resolution_clock::now();
}

ULL get_exec_time_h(CHRONOMETER start)
{
	return std::chrono::duration_cast<std::chrono::hours>(time_now() - start).count();
}

ULL get_exec_time_m(CHRONOMETER start)
{
	return std::chrono::duration_cast<std::chrono::minutes>(time_now() - start).count();
}

ULL get_exec_time_s(CHRONOMETER start)
{
	return std::chrono::duration_cast<std::chrono::seconds>(time_now() - start).count();
}

ULL get_exec_time_ms(CHRONOMETER start)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(time_now() - start).count();
}

ULL get_exec_time_mis(CHRONOMETER start)
{
	return std::chrono::duration_cast<std::chrono::microseconds>(time_now() - start).count();
}

ULL get_exec_time_ns(CHRONOMETER start)
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(time_now() - start).count();
}

std::string format_time_ms(ULL milliseconds)
{
	std::string sTime;

	ULL tmp = milliseconds / 86400000; //Days.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " day";
		if(tmp > 1)
			sTime += 's';
		milliseconds %= 86400000;
	}

	tmp = milliseconds / 3600000; // Hours.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " hour";
		if (tmp > 1)
			sTime += 's';
		milliseconds %= 3600000;
	}

	tmp = milliseconds / 60000; // Minutes.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " minute";
		if (tmp > 1)
			sTime += 's';
		milliseconds %= 60000;
	}

	tmp = milliseconds / 1000; // Seconds.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " second";
		if (tmp > 1)
			sTime += 's';
		milliseconds %= 60000;
	}

	tmp = milliseconds; // Milliseconds.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " millisecond";
		if (tmp > 1)
			sTime += 's';
	}
	else if (sTime == "")
	{
		sTime += "0 milliseconds";
	}

	return sTime;
}

std::string format_time_mis(ULL microseconds)
{
	std::string sTime;

	ULL tmp = microseconds / 86400000000; //Days.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " day";
		if (tmp > 1)
			sTime += 's';
		microseconds %= 86400000000;
	}

	tmp = microseconds / 3600000000; // Hours.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " hour";
		if (tmp > 1)
			sTime += 's';
		microseconds %= 3600000000;
	}

	tmp = microseconds / 60000000; // Minutes.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " minute";
		if (tmp > 1)
			sTime += 's';
		microseconds %= 60000000;
	}

	tmp = microseconds / 1000000; // Seconds.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " second";
		if (tmp > 1)
			sTime += 's';
		microseconds %= 60000000;
	}

	tmp = microseconds / 1000; // Milliseconds.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " millisecond";
		if (tmp > 1)
			sTime += 's';
		microseconds %= 1000;
	}

	tmp = microseconds; // Microseconds.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " microsecond";
		if (tmp > 1)
			sTime += 's';
	}
	else if (sTime == "")
	{
		sTime += "0 microseconds";
	}

	return sTime;
}

std::string format_time_ns(ULL nanoseconds)
{
	std::string sTime;

	ULL tmp = nanoseconds / 86400000000000; //Days.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " day";
		if (tmp > 1)
			sTime += 's';
		nanoseconds %= 86400000000000;
	}

	tmp = nanoseconds / 3600000000000; // Hours.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " hour";
		if (tmp > 1)
			sTime += 's';
		nanoseconds %= 3600000000000;
	}

	tmp = nanoseconds / 60000000000; // Minutes.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " minute";
		if (tmp > 1)
			sTime += 's';
		nanoseconds %= 60000000000;
	}

	tmp = nanoseconds / 1000000000; // Seconds.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " second";
		if (tmp > 1)
			sTime += 's';
		nanoseconds %= 60000000000;
	}

	tmp = nanoseconds / 1000000; // Milliseconds.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " millisecond";
		if (tmp > 1)
			sTime += 's';
		nanoseconds %= 1000000;
	}

	tmp = nanoseconds / 1000; // Microseconds.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " microsecond";
		if (tmp > 1)
			sTime += 's';
		nanoseconds %= 1000;
	}
	
	tmp = nanoseconds; // Nanoseconds.
	if (tmp != 0)
	{
		if (sTime != "")
			sTime += ", ";
		sTime += std::to_string(tmp);
		sTime += " nanosecond";
		if (tmp > 1)
			sTime += 's';
	}
	else if (sTime == "")
	{
		sTime += "0 nanoseconds";
	}

	return sTime;
}

std::string getf_exec_time_ms(CHRONOMETER start)
{
	return format_time_ms(get_exec_time_ms(start));
}

std::string getf_exec_time_mis(CHRONOMETER start)
{
	return format_time_mis(get_exec_time_mis(start));
}

std::string getf_exec_time_ns(CHRONOMETER start)
{
	return format_time_ns(get_exec_time_ns(start));
}