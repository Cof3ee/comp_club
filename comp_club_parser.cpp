#include "comp_club_parser.h"

#include <sstream>

using namespace std;

comp_club_parser::comp_club_parser(const vector<string>& data)
{
	club_data_ = parse_data(data);
}

comp_club comp_club_parser::get_comp_club_data() const
{
	return club_data_;
}

comp_club comp_club_parser::parse_data(const vector<string>& data)
{
    comp_club club;

    // Парсинг количества столов
   stringstream ss_num_tables(data[0]);
    ss_num_tables >> club.num_tables;

    // Парсинг времени начала и конца работы
    stringstream ss_time(data[1]);
    ss_time >> club.start_time >> club.end_time;

    // Парсинг стоимости часа
    stringstream ss_cost_hour(data[2]);
    ss_cost_hour >> club.cost_hour;

    // Парсинг событий
    for (size_t i = 3; i < data.size(); ++i)
    {
        comp_club::event event;
        stringstream event_ss(data[i]);
        int table_number;
        int event_id;

        event_ss >> event.time >> event_id >> event.client_name;

        event.id = ::event_id(event_id);

        if (event_ss >> table_number)
        {
            event.num_table = table_number;
        }
        else
        {
            event.num_table = nullopt;
        }

        club.all_events.push_back(event);
    }
    return club;
}
