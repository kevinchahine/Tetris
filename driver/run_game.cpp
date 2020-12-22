#include "run_game.h"

#include <iostream>
#include <string>
#include <chrono>
#include <memory>

#include <iocolor/iocolor.h>

#pragma warning ( push, 3 )
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#pragma warning ( pop )

// Include game classes (Model)
#include <Tetris/core/Game.h>
#include <Tetris/core/Tetrominos.hpp>

// Include display classes (View)
#include <Tetris/core/DisplayBase.h>
#include <Tetris/core/ColoredConsoleDisplay.h>
#include <Tetris/core/GraphicalDisplay.h>

// Include controller and solver classes (Controller)
#include <Tetris/core/Controllers.hpp>
#include <Tetris/ai/AiController.h>
#include <Tetris/ai/Solvers.hpp>

// Include heuristics for ai controllers
#include <Tetris/ai/Heuristics.hpp>

using namespace std;

void tetris::driver::runGame()
{
	tetris::core::TetrominoBase piece1 = tetris::core::TetrominoI();
	tetris::core::TetrominoBase piece2 = tetris::core::TetrominoS();

	// --- Set up Game (MODEL) ---
	tetris::core::Game game;
	game.awake();

	// --- Set up Display (VIEW) ---
	unique_ptr<tetris::core::DisplayBase> displayPtr =
		//make_unique<tetris::core::ColoredConsoleDisplay>();
		make_unique<tetris::core::GraphicalDisplay>();

	displayPtr->rasterize(game);
	displayPtr->show();

	// --- Set up controller (CONTROLLER) ---
	unique_ptr<tetris::core::ControllerBase> controllerPtr =
		//make_unique<tetris::core::KeyboardController>();
		//make_unique<tetris::ai::DfsSolver>();
		//make_unique<tetris::ai::RandomSolver>();
		make_unique<tetris::ai::DropSolver>();

	controllerPtr->gamePtr() = &game;

	dynamic_cast<tetris::ai::AiController*>(controllerPtr.get())->heuristicPtr() =
		//make_unique<tetris::ai::HolyHeuristic>();
		make_unique<tetris::ai::OrangeJuiceHeuristic>();

	controllerPtr->reset();

	std::function<void(const tetris::core::Move& move)> onControllerInput = [&](const tetris::core::Move& move) {
		game.update(move);
	};

	controllerPtr->setCallback(move(onControllerInput));

	// --- Game Loop ---
	while (true /*game.isGameOver()*/)
	{
		displayPtr->rasterize(game);
		displayPtr->show();
		this_thread::sleep_for(chrono::milliseconds(33));

		controllerPtr->getInput();
	}
}
