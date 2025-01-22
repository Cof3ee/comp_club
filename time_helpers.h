#pragma once

#include <string>

#include "Time.h"

class time_helpers
{
public:

	static bool compare_times(const std::string& valid_time, const std::string& testing_time);

	//Function to calculate the difference between two times in the format "HH:MM"
	static std::string calculate_time_difference(const std::string& start_Time, const std::string& end_Time);

	//Function for adding two times in the format "HH:MM"
	static std::string calculate_time_sum(const std::string& time1, const std::string& time2);

	//Function to get hours rounded up
	static int get_ceiled_hours(const std::string& time_str);

	//Function to convert time from "HH:MM" format to minutes
	static int time_to_minutes(const std::string& time_str);

	//Function to convert time from string to Time structure
	static Time parse_time(const std::string& time_str);

	//Function to check whether the time is recorded correctly
	static bool validate_time_range(const std::string& time_range);
private:
	//Function for formatting minutes in "HH:MM" format
	static std::string format_time(int total_minutes);
};

