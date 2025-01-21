#pragma once
#include <string>
#include <optional>
#include <vector>

#include "event_id.h"

struct comp_club
{
	unsigned int num_tables;
	std::string start_time;
	std::string end_time;
	unsigned int cost_hour;
	
	struct event
	{
		std::string time;
		event_id id;
		std::string client_name;
		std::optional <int> num_table;
	};
	std::vector<event> all_events;
};
