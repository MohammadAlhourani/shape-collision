#ifndef NPC_H
#define NPC_H

#include <GameObject.h>
#include <Input.h>
#include <PlayerFSM.h>
#include <AnimatedSprite.h>

class NPC : public GameObject
{
private:
	int	m_input = 0;

public:
	NPC();
	~NPC();
	NPC(const AnimatedSprite&, const AnimatedSprite&, const AnimatedSprite&, const AnimatedSprite&, const AnimatedSprite&);
	AnimatedSprite& getAnimatedSprite();
	void handleInput(Input);
	void update();

	int getInput();
};

#endif // !NPC_H
