// @author Germán Caíno
// @version 1.0.0 30/11/17
// -----------------------------------------
#ifdef _DEBUG
#include "vld.h"
#endif
// -----------------------------------------
#include "GameLoop.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
// -----------------------------------------
int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	try
	{
		lpa::GameLoop game;
		game.run();
	}
	catch (...)
	{
		std::cerr << "Abnormal termination\n" << std::endl;
	}
	return 0;
}

