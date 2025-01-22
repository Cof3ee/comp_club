#pragma once

#include "comp_club.h"
#include <set>
#include <string>
#include <map>
#include <queue>

class comp_club_manger
{
public:
	comp_club_manger(const comp_club &club_data);

	void manage_day();
private:
	void start_day();

	void end_day();

	void process_ID_event(const comp_club::event& event);

	void handle_client_arrival(const comp_club::event& event);

	void handle_client_seating(const comp_club::event& event);

	void handle_client_waiting(const comp_club::event& event);
	
	void handle_client_leaving(const comp_club::event& event);

	void session_is_start(const comp_club::event& event);

	void session_is_over(const comp_club::event& event);

	//Ќе придумал нормальное название, это дл€ ID 11
	void client_kicked(const comp_club::event& event);

	void client_seating_from_queue(const comp_club::event& event, const int &vacant_table);

	int revenue_calculation_for_table(const std::pair<int, std::string> &table);

	comp_club club_;

	std::set <std::string> clients_in_club;
	std::queue <std::string> clients_waiting;

	struct client_name_and_time
	{
		std::string name;
		std::string time;
	};
	//«а каким столом сидит клиент, во сколько сел
	std::map<int, client_name_and_time> guest_seating_log;
	//«а каким столом, сколько времени просижено
	std::map<int, std::string> table_sitting_times;
	// акой клиент сидит за каким столом
	std::map<std::string, int>  table_occupants;
};

