#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include <memory>
#include <stack>

#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
	StateMachine();

	StateMachine(StateMachine&) = delete;
	StateMachine& operator=(StateMachine&) = delete;

	~StateMachine();

	void AddState(StateRef p_newState, bool p_isReplacing = true);
	void RemoveState();
	void ProcessStateChanges();
	StateRef& GetActiveState();

private:
	std::stack<StateRef> m_states;
	StateRef m_newState;

	bool m_isRemoving{ false };
	bool m_isAdding{ false };
	bool m_isReplacing{ false };
};

#endif // !_STATE_MACHINE_H_
