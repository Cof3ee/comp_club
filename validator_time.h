#pragma once

#include "Time.h"
#include <string>

class validator_time
{
public:
	static bool validate_time_range(const std::string& timeRange);

	static Time parse_time(const std::string& timeStr);
};

