#pragma once

#include <vector>
#include <string>
#include "comp_club.h"

class comp_club_parser
{
public:
	static comp_club parse_data(const std::vector<std::string>& data);
};

