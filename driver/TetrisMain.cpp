#include <iostream>
#include <string>
#include <chrono>

#include <iocolor/iocolor.h>

#pragma warning ( push, 3 )
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#pragma warning ( pop )


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



	cin.get();
	return 0;
}