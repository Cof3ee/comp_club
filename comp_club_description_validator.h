#pragma once

#include <vector>
#include <string>

#include "Time.h"

class comp_club_description_validator
{
public:
	comp_club_description_validator(const std::vector<std::string> &data);

	void validate();

private:
	// Проверка, является ли строка целым числом
	bool is_integer(const std::string& str, int& result);

	// Проверка, является ли строка комбинацией символов из алфавита a..z 0..9
	bool is_valid_name(const std::string& name);

	void validate_time_is_sorted(const std::vector<std::string>& data);
	
	// Функция для проверки первого элемента
	void validate_first_element(const std::string& line);

	// Функция для проверки третьего элемента
	void validate_third_element(const std::string& line);

	// Функция для проверки четвертого и последующих элементов
	void validate_other_elements(const std::string& line);

private:
	int tables_count_ = 0;  // Переменная для хранения значения первого элемента
	int cost_hour_ = 0;  // Переменная для хранения значения третьего элемента
	std::string time_of_last_event_;
	std::vector<std::string> data_;  // Вектор строк для хранения данных
};

