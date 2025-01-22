#include "comp_club_description_validator.h"
#include "time_helpers.h"

#include <sstream> 
#include <cctype>
#include <stdexcept>
#include <algorithm>

using namespace std;

comp_club_description_validator::comp_club_description_validator(const vector<string>& data) : data_(data)
{
    // Checking that the input vector is not empty
    if (data_.empty())
    {
        throw runtime_error("Error: Input data is empty.");
    }
}

void comp_club_description_validator::validate()
{
    // We check that the input vector contains at least three elements
    if (data_.size() < 3) 
    {
        throw runtime_error("Error: There are not enough elements in the input data.");
    }
    // Check the first element (integer greater than 0)
    validate_first_element(data_[0]);
    // Checking the second element (time range)
    time_helpers::validate_time_range(data_[1]);
    // Checking the third element (integer is not equal to 0 and greater than 0)
    validate_third_element(data_[2]);
    // Checking the time sequence of events
    validate_time_is_sorted({data_.begin()+3,data_.end()});
    // Checking the fourth and subsequent elements
    for (size_t index = 3; index < data_.size(); ++index) 
    {
       validate_other_elements(data_[index]);
    }
}

bool comp_club_description_validator::is_integer(const string& str, int& result)
{
    if (str.empty()) return false; // If the string is empty, then it is not a number
    stringstream ss(str);
    ss >> result;
    return !ss.fail() && ss.eof(); // Return true if reading is successful and the end of the line is reached
}

bool comp_club_description_validator::is_valid_name(const string& name)
{
    for (char c : name)
    {
        // Checking that each character is a letter or number
        if (!isalnum(c)) 
        {
            return false; // If we encounter an invalid character, we return false
        }
    }
    return true;
}

void comp_club_description_validator::validate_time_is_sorted(const vector<string>& data)
{
    vector<int> times;
    times.reserve(data.size());

    for (const auto& str : data)
    {
        times.push_back(time_helpers::time_to_minutes(str));
    }
    
    if (!is_sorted(times.begin(), times.end()))
    {
        throw runtime_error("Error: Time in events is not sorted");
    }
}

void comp_club_description_validator::validate_first_element(const string& line)
{
    int tables_count;
    // Checking that the first element is an integer greater than 0
    if (!is_integer(line, tables_count) || tables_count <= 0)
    {
        throw runtime_error(line);
    }
    tables_count_ = tables_count;
}

void comp_club_description_validator::validate_third_element(const string& line)
{
    int cost_hour;
    // Checking that the third element is an integer greater than 0
    if (!is_integer(line, cost_hour) || cost_hour <= 0)
    {
        throw runtime_error(line);
    }
    cost_hour_ = cost_hour;
}

void comp_club_description_validator::validate_other_elements(const string& line)
{
    stringstream ss(line);
    string time_str;
    int id = 0;
    string name;
    int table_number = 0;

    // We check that the time, identifier and client name have been successfully read
    if (!(ss >> time_str >> id >> name)) 
    {
        throw runtime_error(line);
    }
    
    try
    {
        time_helpers::parse_time(time_str);
    }
    catch (exception& ex)
    {
        throw runtime_error(line);
    }

    // Checking that the identifier is within acceptable limits
    if (id != 1 && id != 2 && id != 3 && id != 4 && id != 11 && id != 12 && id != 13)
    {
        throw runtime_error(line);
    }
 
    if (!is_valid_name(name))
    {
        throw runtime_error(line);
    }

    // Check if there is a table number
    if (ss >> table_number) 
    {
        if (table_number <= 0 || table_number > tables_count_) 
        {
            throw runtime_error(line);
        }
    }
}


