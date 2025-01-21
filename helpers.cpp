#include "helpers.h"

#include <cmath>
#include <sstream>
#include <stdexcept>
#include <iomanip>

bool helpers::compare_times(const std::string& first, const std::string& second)
{
    int firstHour = std::stoi(first.substr(0, first.find(':')));
    int firstMinute = std::stoi(first.substr(first.find(':') + 1, 2));
    int secondHour = std::stoi(second.substr(0, second.find(':')));
    int secondMinute = std::stoi(second.substr(second.find(':') + 1, 2));

    if (firstHour > secondHour)
    {
        return true;
    }
    else if (firstHour == secondHour)
    {
        return firstMinute >= secondMinute;
    }
    return false;
}

int helpers::time_to_minutes(const std::string& time_str)
{
    std::stringstream ss(time_str);
    int hours, minutes;
    char colon;
    ss >> hours >> colon >> minutes && colon == ':' && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59;
    
    return hours * 60 + minutes;
}

std::string helpers::format_time(int total_minutes)
{
    int hours = total_minutes / 60;
    int minutes = total_minutes % 60;
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes;
    return ss.str();
}

std::string helpers::calculate_time_difference(const std::string& end_sitting_time, const std::string& start_sitting_time)
{
        int startMinutes = time_to_minutes(end_sitting_time);
        int endMinutes = time_to_minutes(start_sitting_time);

        int differenceMinutes = endMinutes - startMinutes;
        return format_time(differenceMinutes);
}

std::string helpers::calculate_time_sum(const std::string& time1, const std::string& time2)
{
        int minutes1 = time_to_minutes(time1);
        int minutes2 = time_to_minutes(time2);
        int totalMinutes = minutes1 + minutes2;

        // Обрабатываем случай если общее время больше 24 часов
        totalMinutes = totalMinutes % (24 * 60);

        return format_time(totalMinutes);
}

int helpers::get_ceiled_hours(const std::string& timeStr)
{
        int totalMinutes = time_to_minutes(timeStr);
        // Преобразуем общее количество минут в часы с округлением в большую сторону
        double hours = static_cast<double>(totalMinutes) / 60.0;
        return static_cast<int>(std::ceil(hours));
}
