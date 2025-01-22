#pragma once

#include <vector>
#include <string>

#include "Time.h"

class comp_club_description_validator
{
public:
	comp_club_description_validator(const std::vector<std::string> &data);

	void validate();

private:
	// Checking if a string is an integer
	bool is_integer(const std::string& str, int& result);

	// Checking if a string is a combination of characters from the alphabet a..z 0..9
	bool is_valid_name(const std::string& name);

	//Checking that event times are in order
	void validate_time_is_sorted(const std::vector<std::string>& data);
	
	void validate_first_element(const std::string& line);

	void validate_third_element(const std::string& line);

	// Method for checking events
	void validate_other_elements(const std::string& line);

private:
	int tables_count_ = 0; 
	int cost_hour_ = 0; 
	std::string time_of_last_event_;
	std::vector<std::string> data_; 
};

