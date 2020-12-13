#include "pch.h"
#include "KeyboardController.h"

#include <iostream>
#include <time.h>
#include <chrono>
#include <functional>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>      // for _kbhit() and _getch()
#else
#pragma warning ("KeyboardController only works on windows. Do no use KeyboardController if not on windows")
#endif

using namespace std;

namespace tetris
{
	namespace core
	{
		KeyboardController::KeyboardController()
		{
			startAsyncOp();
		}

		KeyboardController::~KeyboardController() noexcept
		{
			// Tell thread to stop what its doing and return
			stopAsyncOp();
		}

		void KeyboardController::reset()
		{
			// Nothing to do here
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
			//myThread.join();
		}

		void KeyboardController::startAsyncOp()
		{
			stopFlag = false;

			// Define input operation (this will be called on a separate thread)
			function<void()> promptUserInput = [&]() {
				// Prompt user for keybord hit
				//cout << "\Enter move (wasd q) (x to exit):";

				// Keep accepting user inputs until user enters an 'x'
				// Or the stopFlag is set to true
				do
				{
#ifdef _WIN32	
					// Check to see if user hit the keyboard (non-blocking)
					if (_kbhit()) {
						// What key did user hit (_getch() is blocking)
						char ch = _getch();

						bool isValid = this->input.setMove(ch);

						if (isValid && m_callback != nullptr) {
							m_callback(this->input);
						}
					}
#else
					throw std::exception("conio only works on windows. See KeyboardController.cpp");
#endif
					this_thread::sleep_for(chrono::milliseconds(33));  // No more work to be done here

				} while (stopFlag == false);
			};

			// Kick off thread
			myThread = std::thread{ promptUserInput };
		}
	}
}
