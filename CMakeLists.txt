cmake_minimum_required(VERSION 3.14)

project(comp_club)

set(CMAKE_CXX_STANDARD 20)

add_executable(comp_club comp_club.h comp_club_parser.cpp comp_club_description_validator.cpp comp_club_parser.h event_id.h Time.h 
	comp_club_description_validator.h helpers.cpp validator_time.cpp comp_club_manger.cpp helpers.h validator_time.h comp_club_manger.h    
	main.cpp)               