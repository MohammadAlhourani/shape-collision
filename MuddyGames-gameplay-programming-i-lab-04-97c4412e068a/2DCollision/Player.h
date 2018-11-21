#ifndef PLAYER_H
#define PLAYER_H

#include <GameObject.h>
#include <Input.h>
#include <PlayerFSM.h>
#include <AnimatedSprite.h>

class Player : public GameObject
{
	int t_input = 0;

public:
	Player();
	~Player();
	Player(const AnimatedSprite&, const AnimatedSprite&, const AnimatedSprite&, const AnimatedSprite&, const AnimatedSprite&);
	AnimatedSprite& getAnimatedSprite();
	void handleInput(Input);
	void update();

	int getInput();
};

#endif // !PLAYER_H
