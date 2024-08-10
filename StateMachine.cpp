#include "StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::AddState(StateRef p_newState, bool p_isReplacing)
{
	this->m_isAdding = true;
	this->m_isReplacing = p_isReplacing;

	this->m_newState = std::move(p_newState);
}

void StateMachine::RemoveState()
{
	this->m_isRemoving = true;
}

void StateMachine::ProcessStateChanges()
{
	if (this->m_isRemoving && !this->m_states.empty())
	{
		this->m_states.pop();

		if (!this->m_states.empty())
		{
			this->m_states.top()->Resume();
		}

		this->m_isRemoving = false;
	}

	if (this->m_isAdding)
	{
		if (!this->m_states.empty())
		{
			if (this->m_isReplacing)
			{
				this->m_states.pop();
			}
			else
			{
				this->m_states.top()->Pause();
			}
		}

		this->m_states.push(std::move(this->m_newState));
		this->m_states.top()->Init();
		this->m_isAdding = false;
	}
}

StateRef& StateMachine::GetActiveState()
{
	return this->m_states.top();
}
