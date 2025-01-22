#include "comp_club_manger.h"
#include "time_helpers.h"

#include <iostream>

using namespace std;

comp_club_manger::comp_club_manger(const comp_club& club_data) : club_(club_data)
{
	for (int num_table = 1; num_table < club_data.num_tables+1; num_table++)
	{
		guest_seating_log[num_table];
		table_sitting_times[num_table];
	}
}

void comp_club_manger::manage_day()
{
	start_day();
	end_day();
}

void comp_club_manger::start_day()
{
	cout << club_.start_time << endl;

	for (const auto& event : club_.all_events)
	{
		cout << event.time << " ";
		cout << static_cast <int>(event.id) << " ";
		cout << event.client_name << " ";
		
		if (event.num_table != nullopt)
		cout << event.num_table.value() << endl;
		else
		cout << endl;

		process_ID_event(event);
	}
}

void comp_club_manger::end_day()
{
	if (!clients_in_club.empty())
	{
		for (auto name : clients_in_club)
		{
			comp_club::event event_;
			
			event_.client_name = name;
			event_.time = club_.end_time;
			event_.num_table = table_occupants[name];

			client_kicked(event_);
		}
		clients_in_club.clear();
	}
	cout << club_.end_time << endl;

	for(auto table : table_sitting_times)
	{
		cout << table.first<<" ";
		cout<<revenue_calculation_for_table(table)<<" ";
		cout << table.second << endl;
	}
}

void comp_club_manger::process_ID_event(const comp_club::event& event)
{
	switch (event.id)
	{
	case event_id::client_arrival:
		handle_client_arrival(event);
		break;
	case event_id::client_seating:
		handle_client_seating(event);
		break;
	case event_id::client_waiting:
		handle_client_waiting(event);
		break;
	case event_id::client_leaving:
		handle_client_leaving(event);
		break;
	default:
		break;
	}
}

//Пришёл клиент
void comp_club_manger::handle_client_arrival(const comp_club::event& event) 
{
	if (time_helpers::compare_times(club_.start_time,event.time)) //Пришёл в нерабочие часы
	{
		cout << event.time << " " << "13 " << "NotOpenYet" << endl;
	}
	else if (clients_in_club.find(event.client_name) != clients_in_club.end()) //Уже есть в клубе
	{
		cout << event.time << " " << "13 " << "YouShallNotPass" << endl; 
	}
	else //Пришёл новый клиент
	{
		clients_in_club.insert(event.client_name);
	}
}

//Клиент сел за стол
void comp_club_manger::handle_client_seating(const comp_club::event& event)
{
	if (!guest_seating_log[*event.num_table].name.empty())//Если выбранный стол занят
	{
		cout << event.time << " " << "13 " << "PlaceIsBusy" << endl;
	}
	else if(table_occupants.find(event.client_name)==table_occupants.end()) //Если клиент просто садится за стол
	{
		session_is_start(event);
	}
	else //Если клиент пересаживается 
	{
		session_is_over(event);
		session_is_start(event);
	}
}

//Встал в очередь
void comp_club_manger::handle_client_waiting(const comp_club::event& event)
{
	//Есть ли свободные столы
	bool free_table = false;
	
	//Проверяем заняты ли столы
	for (int index = 1; index <= guest_seating_log.size(); index++)
	{
		if (guest_seating_log[index].name.empty())
		{
			cout << event.time << " " << "13 " << "ICanWaitNoLonger!" << endl;
			free_table = true;
			break;
		}
	}

	if (!free_table)
	{
		if(clients_waiting.size()<=club_.num_tables)
		{
			clients_waiting.emplace(event.client_name);
			
			if(clients_in_club.find(event.client_name)==clients_in_club.end())
			{
				clients_in_club.emplace(event.client_name);
			}
		}
		else
		{
			client_kicked(event);
		}
	}
}

//Клиент который был за столом, уходит
void comp_club_manger::handle_client_leaving(const comp_club::event& event)
{
	if (clients_in_club.find(event.client_name) == clients_in_club.end())
	{
		cout << event.time << " " << "13 " << "ClientUnknown" << endl;
	}
	else
	{
		//Освободившийся стол
		const int vacant_table = table_occupants[event.client_name];
		session_is_over(event);
		clients_in_club.erase(event.client_name);

		if(!clients_waiting.empty())
		{
			client_seating_from_queue(event, vacant_table);
		}
	}
}

void comp_club_manger::session_is_start(const comp_club::event& event)
{
	//Сажаем клиента за стол
	guest_seating_log[*event.num_table].name = event.client_name;
	guest_seating_log[*event.num_table].time = event.time;

	//Ведём учёт за каким столом сидит клиент
	table_occupants[event.client_name] = *event.num_table;
}

void comp_club_manger::session_is_over(const comp_club::event& event)
{
	const string session_start_time = guest_seating_log[table_occupants[event.client_name]].time;
	auto& table = table_sitting_times[table_occupants[event.client_name]];

	if (table.empty()) //Если столу записывается время впервые
	{
		table = time_helpers::calculate_time_difference(session_start_time, event.time);
	}
	else //Сумирование времени за столом, с последней сессией
	{
		string last_session_time = time_helpers::calculate_time_difference(session_start_time, event.time);
		table = time_helpers::calculate_time_sum(last_session_time, table);
	}
	guest_seating_log[table_occupants[event.client_name]].name = "";
	guest_seating_log[table_occupants[event.client_name]].time = "";

	table_occupants.erase(event.client_name);
}

void comp_club_manger::client_kicked(const comp_club::event& event)
{
	cout << event.time << " " << "11 " << event.client_name << endl;

	if (clients_in_club.find(event.client_name) != clients_in_club.end())
	{
		session_is_over(event);
	}
}

void comp_club_manger::client_seating_from_queue(const comp_club::event& event, const int& vacant_table)
{
	cout << event.time << " " << "12 " << clients_waiting.front() << " " << vacant_table << endl;

	comp_club::event event_ = event;
	event_.client_name = clients_waiting.front();
	event_.num_table = vacant_table;

	session_is_start(event_);

	clients_waiting.pop();
}

int comp_club_manger::revenue_calculation_for_table(const std::pair<int, std::string> &table)
{
	int total_working_hours = time_helpers::get_ceiled_hours(table_sitting_times[table.first]);

	return total_working_hours * club_.cost_hour;
}
