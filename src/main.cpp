// main.cpp : Defines the entry point for the application.
//

#include "main.hpp"
#include  "SDL.h"


int main(int argc, char* argv[])
{
	SDL_Log("Hello CMake.");

	return 0;
}

#if defined(_WIN32)
int wmain(int argc, char* argv[])
{
	main(argc, argv);
}
#endif


