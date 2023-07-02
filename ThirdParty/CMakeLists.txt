#static sdl build (avoid copying .dll)
option(BUILD_SHARED_LIBS "Build using static libraries" OFF)
#set(SDL_SHARED OFF)
#set(SDL_STATIC ON)
#set(SDL_TEST OFF)
add_subdirectory(SDL2)

add_library(ThirdParty INTERFACE )
target_link_libraries(ThirdParty INTERFACE SDL2::SDL2 )
