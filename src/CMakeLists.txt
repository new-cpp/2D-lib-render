
cmake_minimum_required (VERSION 3.21)

# Add source to this project's executable.
add_executable (${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp game.cpp circle.cpp object.cpp)
#link to libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ThirdParty)