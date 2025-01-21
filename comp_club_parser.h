#pragma once

#include <vector>
#include <string>
#include "comp_club.h"

class comp_club_parser
{
public:
	comp_club_parser(const std::vector<std::string>& data);

	comp_club get_comp_club_data() const;
private:
	comp_club parse_data(const std::vector<std::string>& data);

	comp_club club_data_;
};

