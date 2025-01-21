#include "validator_time.h"

#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

Time validator_time::parse_time(const string& time_str)
{
	Time time;
	stringstream ss(time_str);
	char colon;

	if (!(ss >> time.hour >> colon >> time.minute) || colon != ':')
	{
		throw exception();
	}

	if (time.hour < 0 || time.hour > 23 || time.minute < 0 || time.minute > 59)
	{
		throw exception();
	}
	return time;
}

bool validator_time::validate_time_range(const string& time_range)
{
	stringstream ss(time_range);
	string start_time_str;
	string end_time_str;

	//ѕроверка правильно ли запишутс€ данные из потока ss
	if (!(ss >> start_time_str >> end_time_str))
	{
		throw std::runtime_error(time_range);
	}

	Time startTime = parse_time(start_time_str);
	Time endTime = parse_time(end_time_str);

	// ѕроверить, что врем€ начала раньше времени конца
	if (startTime.hour > endTime.hour || (startTime.hour == endTime.hour && startTime.minute >= endTime.minute))
	{
		throw std::runtime_error(time_range);
	}

	return true;
}
