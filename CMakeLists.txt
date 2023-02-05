cmake_minimum_required(VERSION 3.22.1)

# Default project config
project(cCalendar VERSION 0.1) # Project name and version
add_executable(cCalendar main.c) # Defines the executable name
# target_link_libraries() # Include some libs if needed
install(TARGETS cCalendar DESTINATION bin) # Tells where to store the binaries
