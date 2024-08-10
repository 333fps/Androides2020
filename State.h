#ifndef _STATE_H_
#define _STATE_H_

#include <memory>
struct GameData;
typedef std::shared_ptr<GameData> GameDataRef;

class State
{
public:
	State(GameDataRef p_data);
	virtual ~State();

	virtual void Init() = 0;
	virtual void HandleInput() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;
	virtual void Pause() {}
	virtual void Resume() {}
};

#endif // !_STATE_H_
