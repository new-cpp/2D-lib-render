 
 # H1 SDL3 libraries as git submodule:
 
 ### H3 HOW TO create:
 
 -Add sdl as a submodule:
	git submodule add https://github.com/libsdl-org/SDL.git ./ThirdParty/SDL/
 
 
 -Root CMAKElists.txt:
	```
	cmake_minimum_required(VERSION 3.1.0)
	project(render)
	
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	
	add_subdirectory(ThirdParty)
	add_subdirectory(src)
	
	```
  -Inside src dir:
  ```
	cmake_minimum_required (VERSION 3.21)
	
	# Add source to this project's executable.
	add_executable (${PROJECT_NAME})
	target_sources(${PROJECT_NAME} PRIVATE main.cpp)
	#link to libraries
	target_link_libraries(${PROJECT_NAME} PRIVATE ThirdParty)
	
  ```
  -Inside ThirdParty dir:
  ```
	#(avoid copying .dll)
	option(BUILD_SHARED_LIBS "Build using static libraries" OFF)
	set(SDL_SHARED OFF)
	set(SDL_STATIC ON)
	set(SDL_TEST OFF)
	add_subdirectory(SDL)
	
	add_library(ThirdParty INTERFACE )
	target_link_libraries(ThirdParty INTERFACE SDL3::SDL3)

  ```

   ### H3 Or just Fork or clone this repo:
	-In case a SDL folder still empty after updating submodules through cmd:
	```
	git submodule update --init --recursive
	```
	Solution (that works for me!!! ) : 
	```
	git rm --cached  SDL
	```
	

	