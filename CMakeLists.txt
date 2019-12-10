cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_SCRIPTS ${CMAKE_SOURCE_DIR}/cmake)

include(${CMAKE_SCRIPTS}/version.cmake)
include(${CMAKE_SCRIPTS}/compiler_options.cmake)

project(telnet_sniffer VERSION ${TELNET_SNIFFER_MAJOR}.${TELNET_SNIFFER_MINOR})

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/version.txt.in 
	${CMAKE_CURRENT_BINARY_DIR}/version.txt
)

add_subdirectory(main)
