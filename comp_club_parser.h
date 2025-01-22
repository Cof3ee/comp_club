#pragma once

#include <vector>
#include <string>
#include "comp_club.h"

class comp_club_parser
{
public:
	static comp_club parse(const std::vector<std::string>& data);
};