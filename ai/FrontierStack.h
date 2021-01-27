#pragma once

#include "ai.h"

#include <stack>
#include <set>
#include <iterator>

namespace tetris
{
	namespace ai
	{

		// Represents a stack based frontier
		// When pushing new states to frontier, it efficiently checks if state is already 
		// added by comparing its hash value
		// Make sure contained data types can be hashed using std::hash
		// See class SolutionSequence for hash value calculations
		template<typename STATE>
		class FrontierStack
		{
		public:
			// Non constant overload is left out on purpose since changing the top state
			// will require changing the hash values also.
			//STATE& top() { return m_states.top(); }				 
			const STATE& top() const { return m_states.top(); }

			bool empty() const { return m_states.empty(); }

			void clear();

			size_t size() const { return m_states.size(); }

			// Determines if state is already in the frontier
			// Calculates the hash of state and compares it those in Frontier
			bool contains(const STATE& state) const;

			// Adds state to top of the frontier.
			// Only adds state if it is not already in the frontier
			// Calculates the hash of state and compares it those in Frontier
			void push(const STATE& state);
			void push(STATE&& state);

			void pop();

			void swap(FrontierStack& other);

		private:
			std::stack<STATE> m_states;

			// hash values of each state in m_states
			// Used to efficiently check to see if new states have already
			// been added
			std::set<size_t> m_hashes;
		};

		template<typename STATE>
		void FrontierStack<STATE>::clear()
		{
			std::stack<STATE> emptyStack; 
			m_states.swap(emptyStack);

			m_hashes.clear();
		}

		template<typename STATE>
		bool FrontierStack<STATE>::contains(const STATE& state) const
		{
			return m_hashes.count(std::hash<STATE>{}(state)) > 0;
		}

		template<typename STATE>
		void FrontierStack<STATE>::push(const STATE& state)
		{
			// Calculate hash value of state
			size_t hash_value = std::hash<STATE>{}(state);

			// Make sure state is not already in frontier
			if (m_hashes.count(hash_value) == 0) {
				// Proceed to add state to frontier
				m_states.push(state);

				m_hashes.insert(hash_value);
			}
		}

		template<typename STATE>
		void FrontierStack<STATE>::push(STATE&& state)
		{
			// Calculate hash value of state
			size_t hash_value = std::hash<STATE>{}(state);

			// Make sure state is not already in frontier
			if (m_hashes.count(hash_value) == 0) {
				// Proceed to add state to frontier
				m_states.push(std::move(state));

				m_hashes.insert(hash_value);
			}
		}

		template<typename STATE>
		void FrontierStack<STATE>::pop()
		{
			// Calculate hash value of top state
			size_t hash_value = std::hash<STATE>{}(m_states.top());

			// Find that hash and if found remove it from set
			auto it = m_hashes.find(hash_value);
			if (it != m_hashes.end()) {
				m_hashes.erase(it);
			}

			// Pop state 
			m_states.pop();
		}

		template<typename STATE>
		void FrontierStack<STATE>::swap(FrontierStack& other)
		{
			std::swap(this->m_states, other.m_states);
			std::swap(this->m_hashes, other.m_hashes);
		}
	}
}
