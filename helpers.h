#pragma once

#include <string>

class helpers
{
public:

	static bool compare_times(const std::string& valid_time, const std::string& testing_time);

	// Функция для вычисления разницы между двумя временами в формате "ЧЧ:ММ"
	static std::string calculate_time_difference(const std::string& startTime, const std::string& endTime);

	// Функция для сложения двух времен в формате "ЧЧ:ММ"
	static std::string calculate_time_sum(const std::string& time1, const std::string& time2);

	// Функция для получения часов, округленных в большую сторону
	static int get_ceiled_hours(const std::string& timeStr);

	// Функция для преобразования времени из формата "ЧЧ:ММ" в минуты
	static int time_to_minutes(const std::string& timeStr);
private:
	// Функция для форматирования минут в формат "ЧЧ:ММ"
	static std::string format_time(int totalMinutes);
};

