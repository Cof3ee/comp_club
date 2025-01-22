#pragma once

#include <string>

#include "Time.h"

class time_helpers
{
public:

	static bool compare_times(const std::string& valid_time, const std::string& testing_time);

	// ������� ��� ���������� ������� ����� ����� ��������� � ������� "��:��"
	static std::string calculate_time_difference(const std::string& start_Time, const std::string& end_Time);

	// ������� ��� �������� ���� ������ � ������� "��:��"
	static std::string calculate_time_sum(const std::string& time1, const std::string& time2);

	// ������� ��� ��������� �����, ����������� � ������� �������
	static int get_ceiled_hours(const std::string& time_str);

	// ������� ��� �������������� ������� �� ������� "��:��" � ������
	static int time_to_minutes(const std::string& time_str);

	//������� ��� �������������� ������� �� string � ��������� Time
	static Time parse_time(const std::string& time_str);

	//������� ��� �������� ��������� �� �������� �����
	static bool validate_time_range(const std::string& time_range);
private:
	// ������� ��� �������������� ����� � ������ "��:��"
	static std::string format_time(int total_minutes);
};

