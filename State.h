#ifndef _STATE_H_
#define _STATE_H_

class State
{
public:
	virtual ~State() {}

	virtual void Init() = 0;
	virtual void HandleInput() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;
	virtual void Pause() { }
	virtual void Resume() { }
};

#endif // !_STATE_H_
