#include "comp_club_parser.h"

#include <sstream>

using namespace std;

comp_club comp_club_parser::parse(const vector<string>& data)
{
    comp_club club_data_;

    // Parsing the number of tables
   stringstream ss_num_tables(data[0]);
    ss_num_tables >> club_data_.num_tables;

    // Parsing start and end times of work
    stringstream ss_time(data[1]);
    ss_time >> club_data_.start_time >> club_data_.end_time;

    // Hourly cost parsing
    stringstream ss_cost_hour(data[2]);
    ss_cost_hour >> club_data_.cost_hour;

    // Event parsing
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

        club_data_.all_events.push_back(event);
    }
    return club_data_;
}
