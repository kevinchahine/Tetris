#include <iostream>
#include <string>
#include <chrono>
#include <memory>

#include <iocolor/iocolor.h>

#pragma warning ( push, 3 )
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#pragma warning ( pop )

#include <Tetris/core/Game.h>

#include <Tetris/core/DisplayBase.h>
#include <Tetris/core/ColoredConsoleDisplay.h>
#include <Tetris/core/GraphicalDisplay.h>

using namespace std;

int main(int* argc, char** argv)
{
	cout 
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
		<< iocolor::setfg(iocolor::BLUE) << "==================\n";

	tetris::core::Game game;
	
	unique_ptr<tetris::core::DisplayBase> displayPtr =
		make_unique<tetris::core::GraphicalDisplay>();
		//make_unique<tetris::core::ColoredConsoleDisplay>();
	
	displayPtr->rasterize(game);
	displayPtr->show();

	cin.get();
	return 0;
}