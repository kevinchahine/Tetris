#include "pch.h"
#include "KeyboardController.h"

#include <iostream>
#include <time.h>
#include <chrono>
#include <Windows.h>
#include <conio.h>      // for _kbhit() and _getch()
#include <functional>

using namespace std;

namespace tetris
{
	namespace core
	{
		KeyboardController::KeyboardController()
		{
			initAsyncOp();
		}

		KeyboardController::~KeyboardController() noexcept
		{
			// Tell thread to stop what its doing and return
			stopAsyncOp();
		}

		void KeyboardController::reset()
		{
			// No nothing
		}

		Move KeyboardController::getInput()
		{
			Move ret = input;

			input.setMove(Move::NONE);

			return ret;
		}

		void KeyboardController::stopAsyncOp()
		{
			// When thread reads this in its loop, it will return and close itself
			stopFlag = true;
		}

		void KeyboardController::initAsyncOp()
		{
			std::function<void()> promptUserInput = [&]() {
				// Prompt user for keybord hit
				std::cout << "\nEnter move (wasd) (x to exit):\n";

				// Keep accepting user inputs until user enters an 'x'
				// Or the stopFlag is set to true
				do
				{
					// Check to see if user hit the keyboard (non-blocking)
					if (_kbhit()) {
						// What key did user hit (_getch() is blocking)
						char ch = _getch();

						bool isValid = this->input.setMove(ch);

						// Prompt user for keyboard hit
						//std::cout << "Enter move (wasd) (x to exit):\n";
					}

					//this_thread::sleep_for(chrono::milliseconds(100));  // No more work to be done here

				} while (this->input.getMove() == Move::EXIT || stopFlag == false);

				// Kick off thread
				myThread = std::thread{ promptUserInput };
			};
		}
	}
}
