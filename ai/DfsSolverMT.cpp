#include "pch.h"
#include "DfsSolverMT.h"

using namespace std;
using namespace tetris::core;

namespace tetris
{
	namespace ai
	{
		void DfsSolverMT::reset()
		{
			m_moveSequence.clear();
		}

		Move DfsSolverMT::getInput(const core::Game & game)
		{
			if (m_moveSequence.empty()) {

				m_moveSequence = solve(game).sequence();

				if (m_moveSequence.empty()) {
					throw std::exception("No solution was found\n");
				}
			}
			else {
			}

			Move selection = m_moveSequence.front();

			m_moveSequence.pop_front();

			return selection;
		}

		unique_ptr<ControllerBase> DfsSolverMT::clone()
		{
			return make_unique<DfsSolverMT>(*this);
		}

		string DfsSolverMT::name()
		{
			return "DFS1-MT";
		}

		SolutionSequence DfsSolverMT::solve(const core::Game & game)
		{
			return SolutionSequence();
		}

		SolutionSequence DfsSolverMT::solveImpl(const core::Game & game)
		{
			return SolutionSequence();
		}
	}
}
