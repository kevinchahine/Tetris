#pragma once

// Include Displays
#include <Tetris/core/GraphicalDisplay.h>
#include <Tetris/core/ColoredConsoleDisplay.h>

// Include Controllers/Solvers
#include <Tetris/core/KeyboardController.h>
#include <Tetris/ai/Solvers.hpp>

// Include Trainers/Optimizers
#include <Tetris/ai/Optimizer.h>

#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include <boost/program_options.hpp>	// Break this down into only the headers we need (or remove it)

namespace tetris
{
	namespace driver
	{
		// Sets up, parses and handles program options.
		class ClParser
		{
		public:		// ---------------- PUBLIC METHODS ------------------------
			ClParser();
			ClParser(const ClParser &) = default;
			ClParser(ClParser &&) noexcept = default;
			virtual ~ClParser() noexcept = default;
			ClParser & operator=(const ClParser &) = default;
			ClParser & operator=(ClParser &&) noexcept = default;

			void handle(int argc, char ** argv);

		public:

		private:	// ---------------- PRIVATE METHODS -----------------------

			// ------------------------ SWITCHES ------------------------------

			void handleSwitches(const boost::program_options::variables_map & vm);

			void showHelp() const;

			void listOptions() const;

			// ------------------------ OPTIONS -------------------------------

			void handleOptions(const boost::program_options::variables_map & vm);

			void setController(const std::string & controller);

			void setHeuristic(const std::string & heuristic);

			void setDisplay(const std::string & display);

			void setGameMode(const std::string & mode);

			void playGame();

			void setGenerationLimit(int generationLimit);

			void setPopulationSize(int populationSize);

			void setTimeLimit(int timeLimit);

			void setOutputDir(const std::string & outDir);

			void setTrainingParams(const boost::program_options::variables_map & vm);

			void train();

			void printWarning(const std::string & message, std::ostream & os = std::cout) const;

		private:	// ---------------- PRIVATE FIELDS ------------------------

			boost::program_options::options_description switchesDesc = boost::program_options::options_description("Switches");
			boost::program_options::options_description optionsDesc = boost::program_options::options_description("Options");
			boost::program_options::options_description desc = boost::program_options::options_description("Tetris Yay :) !!!");

			std::unique_ptr<tetris::core::DisplayBase> m_displayPtr;
			std::unique_ptr<tetris::core::ControllerBase> m_controllerPtr;
			std::unique_ptr<tetris::ai::HeuristicBase> m_heuristicPtr;

			std::unique_ptr<tetris::ai::Session> m_trainingSessionPtr;

			// Should be set to either call this->play() or this->train() or nullptr
			std::function<void()> m_gameMode = nullptr;
		};
	}
}

