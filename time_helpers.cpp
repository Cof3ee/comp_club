#include "time_helpers.h"

#include <cmath>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

bool time_helpers::compare_times(const string& first, const string& second)
{
    int firstHour = stoi(first.substr(0, first.find(':')));
    int firstMinute = stoi(first.substr(first.find(':') + 1, 2));
    int secondHour = stoi(second.substr(0, second.find(':')));
    int secondMinute = stoi(second.substr(second.find(':') + 1, 2));

    if (firstHour > secondHour)
    {
        return true;
    }
    else if (firstHour == secondHour)
    {
        if (firstMinute == secondMinute)
        {
            return false;
        }
        else
        {
            return firstMinute >= secondMinute;
        }
    }
    return false;
}

int time_helpers::time_to_minutes(const string& time_str)
{
    stringstream ss(time_str);
    int hours, minutes;
    char colon;
    ss >> hours >> colon >> minutes && colon == ':' && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59;
    
    return hours * 60 + minutes;
}

Time time_helpers::parse_time(const string& time_str)
{
    Time time;
    stringstream ss(time_str);
    char colon;

    if (!(ss >> time.hour >> colon >> time.minute) || colon != ':')
    {
        throw runtime_error(time_str);
    }

    if (time.hour < 0 || time.hour > 23 || time.minute < 0 || time.minute > 59)
    {
        throw runtime_error(time_str);
    }
    return time;
}

bool time_helpers::validate_time_range(const std::string& time_range)
{
    stringstream ss(time_range);
    string start_time_str;
    string end_time_str;

    //Checking whether data from the ss stream will be written correctly
    if (!(ss >> start_time_str >> end_time_str))
    {
        throw std::runtime_error(time_range);
    }

    Time startTime = parse_time(start_time_str);
    Time endTime = parse_time(end_time_str);

    //Check that the start time is before the end time
    if (startTime.hour > endTime.hour || (startTime.hour == endTime.hour && startTime.minute >= endTime.minute))
    {
        throw std::runtime_error(time_range);
    }

    return true;
}

std::string time_helpers::format_time(int total_minutes)
{
    int hours = total_minutes / 60;
    int minutes = total_minutes % 60;
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes;
    return ss.str();
}

std::string time_helpers::calculate_time_difference(const std::string& end_sitting_time, const std::string& start_sitting_time)
{
        int startMinutes = time_to_minutes(end_sitting_time);
        int endMinutes = time_to_minutes(start_sitting_time);

        int differenceMinutes = endMinutes - startMinutes;
        return format_time(differenceMinutes);
}

std::string time_helpers::calculate_time_sum(const std::string& time1, const std::string& time2)
{
        int minutes1 = time_to_minutes(time1);
        int minutes2 = time_to_minutes(time2);
        int totalMinutes = minutes1 + minutes2;

        // We process the case if the total time is more than 24 hours
        totalMinutes = totalMinutes % (24 * 60);

        return format_time(totalMinutes);
}

int time_helpers::get_ceiled_hours(const std::string& timeStr)
{
        int totalMinutes = time_to_minutes(timeStr);
        // Convert the total number of minutes to hours, rounding up
        double hours = static_cast<double>(totalMinutes) / 60.0;
        return static_cast<int>(std::ceil(hours));
}