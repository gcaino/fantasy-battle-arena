// @author Germán Caíno
// @version 1.0.0 30/11/17
// @version 2.0.0 25/03/23
// -----------------------------------------
#include "pch.h"
// -----------------------------------------
#ifdef _DEBUG
#include "vld.h"
#endif
// -----------------------------------------
#include "GameLoop.h"
// -----------------------------------------
int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	try
	{
		lpa::GameLoop game;
		game.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception Unhalded: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Abnormal termination\n" << std::endl;
	}
	return 0;
}

