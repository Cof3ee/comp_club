#pragma once

#include <string>

class helpers
{
public:

	static bool compare_times(const std::string& valid_time, const std::string& testing_time);

	// ������� ��� ���������� ������� ����� ����� ��������� � ������� "��:��"
	static std::string calculate_time_difference(const std::string& startTime, const std::string& endTime);

	// ������� ��� �������� ���� ������ � ������� "��:��"
	static std::string calculate_time_sum(const std::string& time1, const std::string& time2);

	// ������� ��� ��������� �����, ����������� � ������� �������
	static int get_ceiled_hours(const std::string& timeStr);

	// ������� ��� �������������� ������� �� ������� "��:��" � ������
	static int time_to_minutes(const std::string& timeStr);
private:
	// ������� ��� �������������� ����� � ������ "��:��"
	static std::string format_time(int totalMinutes);
};

