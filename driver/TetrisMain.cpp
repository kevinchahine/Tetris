// Include runtime files
#include "run_game.h"
#include "training.h"
#include "CLHandler.h"

// Include test files
#include "TestIndividual.h"
#include "TestMoveSequence.h"

#include <iocolor/iocolor.h>

#include <iostream>

using namespace std;

/*
	See program_options_notes.txt for ideas
	See updates.txt for updates
	See notes.txt in ai project
*/

int main(int argc, char** argv)
{
	cout
		<< iocolor::push()
		<< iocolor::setfg(iocolor::RED) << "==================\n"
		<< iocolor::setfg(iocolor::GREEN) << "===== "
		<< iocolor::setfg(iocolor::CYAN) << 'T'
		<< iocolor::setfg(iocolor::RED) << 'E'
		<< iocolor::setfg(iocolor::YELLOW) << 'T'
		<< iocolor::setfg(iocolor::GREEN) << 'R'
		<< iocolor::setfg(iocolor::MAGENTA) << 'I'
		<< iocolor::setfg(iocolor::BLUE) << 'S'
		<< iocolor::setfg(iocolor::GREEN) << " ====="
		<< iocolor::setfg(iocolor::WHITE) << '\n'
		<< iocolor::setfg(iocolor::BLUE) << "==================\n"
		<< iocolor::pop();

	try
	{
		tetris::driver::CLHandler clHandler;

		//tetris::driver::train1();
		//tetris::core::Game game;
		//tetris::core::ColoredConsoleDisplay disp;
		//disp.rasterize(game);
		//disp.show();

		clHandler.handle(argc, argv);
	}
	catch (const std::exception& e)
	{
		cout << iocolor::push()
			<< iocolor::red()
			<< "Exception caught: " << e.what() 
			<< iocolor::pop() << '\n';
	}

	chrono::seconds waitTime(2);
	cout << "Closing in " << waitTime.count() << " seconds...";
	this_thread::sleep_for(waitTime);
	
	//cout << "Press any key to continue";
	//cin.get();

	return 0;
}