// Include runtime files
#include "run_game.h"
#include "training.h"

// Include test files
#include "TestIndividual.h"
#include "TestMoveSequence.h"

#include <iocolor/iocolor.h>

using namespace std;

/*
	See program_options_notes.txt for ideas
	See updates.txt for updates
	See notes.txt in ai project
*/

int main(int* argc, char** argv)
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

	tetris::driver::runGame();
	//tetris::driver::train1();

	//tetris::driver::testIndividualSerialize();
	//tetris::driver::testSolutionSequencePrint();

	//cin.get();
	return 0;
}