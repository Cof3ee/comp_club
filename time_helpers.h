#pragma once

#include <string>

#include "Time.h"

class time_helpers
{
public:

	static bool compare_times(const std::string& valid_time, const std::string& testing_time);

	// Функция для вычисления разницы между двумя временами в формате "ЧЧ:ММ"
	static std::string calculate_time_difference(const std::string& start_Time, const std::string& end_Time);

	// Функция для сложения двух времен в формате "ЧЧ:ММ"
	static std::string calculate_time_sum(const std::string& time1, const std::string& time2);

	// Функция для получения часов, округленных в большую сторону
	static int get_ceiled_hours(const std::string& time_str);

	// Функция для преобразования времени из формата "ЧЧ:ММ" в минуты
	static int time_to_minutes(const std::string& time_str);

	//Функция для преобразования времени из string в структуру Time
	static Time parse_time(const std::string& time_str);

	//Функция для проверки правильно ли записано время
	static bool validate_time_range(const std::string& time_range);
private:
	// Функция для форматирования минут в формат "ЧЧ:ММ"
	static std::string format_time(int total_minutes);
};

