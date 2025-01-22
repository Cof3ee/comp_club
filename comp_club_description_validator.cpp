#include "comp_club_description_validator.h"
#include "time_helpers.h"

#include <sstream> 
#include <cctype>
#include <stdexcept>
#include <algorithm>

using namespace std;

comp_club_description_validator::comp_club_description_validator(const std::vector<std::string>& data) : data_(data)
{
    // Проверяем, что входной вектор не пустой
    if (data_.empty())
    {
        throw std::runtime_error("Error: Input data is empty.");
    }
}

void comp_club_description_validator::validate()
{
    // Проверяем, что во входном векторе не меньше трех элементов
    if (data_.size() < 3) 
    {
        throw std::runtime_error("Error: There are not enough elements in the input data.");
    }
    // Проверка первого элемента (целое число больше 0)
    validate_first_element(data_[0]);
    // Проверка второго элемента (диапазон времени)
    time_helpers::validate_time_range(data_[1]);
    // Проверка третьего элемента (целое число не равно 0 и больше 0)
    validate_third_element(data_[2]);
    //Проверка последовательности времени events
    validate_time_is_sorted({data_.begin()+3,data_.end()});
    // Проверка четвертого и последующих элементов
    for (size_t index = 3; index < data_.size(); ++index) 
    {
       validate_other_elements(data_[index]);
    }
}

bool comp_club_description_validator::is_integer(const string& str, int& result)
{
    if (str.empty()) return false; // Если строка пуста, то это не число
    std::stringstream ss(str);
    ss >> result;
    return !ss.fail() && ss.eof(); // Возвращаем true, если чтение успешно и достигнут конец строки
}

bool comp_club_description_validator::is_valid_name(const string& name)
{
    for (char c : name)
    {
        // Проверяем, что каждый символ является буквой или цифрой
        if (!isalnum(c)) 
        {
            return false; // Если встретили недопустимый символ, то возвращаем false
        }
    }
    return true; // Если все символы допустимы, то возвращаем true
}

void comp_club_description_validator::validate_time_is_sorted(const std::vector<std::string>& data)
{
    vector<int> times;
    times.reserve(data.size());

    for (const auto& str : data)
    {
        times.push_back(time_helpers::time_to_minutes(str));
    }
    
    if (!std::is_sorted(times.begin(), times.end()))
    {
        throw runtime_error("Error: Time in events is not sorted");
    }
}

void comp_club_description_validator::validate_first_element(const string& line)
{
    int tables_count;
    // Проверяем, что первый элемент является целым числом больше 0
    if (!is_integer(line, tables_count) || tables_count <= 0)
    {
        throw runtime_error(line);
    }
    tables_count_ = tables_count; // Сохраняем значение первого элемента
}

void comp_club_description_validator::validate_third_element(const std::string& line)
{
    int cost_hour;
    // Проверяем, что третий элемент является целым числом больше 0
    if (!is_integer(line, cost_hour) || cost_hour <= 0)
    {
        throw runtime_error(line);
    }
    cost_hour_ = cost_hour; // Сохраняем значение третьего элемента
}

void comp_club_description_validator::validate_other_elements(const std::string& line)
{
    stringstream ss(line);
    string time_str;
    int id = 0;
    string name;
    int table_number = 0;

    // Проверяем, что успешно прочитаны время, идентификатор и имя клиента
    if (!(ss >> time_str >> id >> name)) 
    {
        throw std::runtime_error(line);
    }
    
    try
    {
        // Пытаемся разобрать время
        time_helpers::parse_time(time_str);
    }
    catch (exception& ex)
    {
        throw std::runtime_error(line);
    }

    // Проверяем, что идентификатор находится в допустимых границах
    if (id != 1 && id != 2 && id != 3 && id != 4 && id != 11 && id != 12 && id != 13)
    {
        throw std::runtime_error(line);
    }
    // Проверяем, что имя клиента является допустимым
    if (!is_valid_name(name))
    {
        throw std::runtime_error(line);
    }

    // Проверяем, есть ли номер стола (четвертый элемент)
    if (ss >> table_number) 
    {
        // Проверяем, что номер стола находится в допустимых границах
        if (table_number <= 0 || table_number > tables_count_) 
        {
            throw std::runtime_error(line);
        }
    }
}


