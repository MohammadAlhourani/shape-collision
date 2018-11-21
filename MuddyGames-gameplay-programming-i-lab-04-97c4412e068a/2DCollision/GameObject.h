#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <Input.h>
#include <PlayerFSM.h>
#include <AnimatedSprite.h>

class GameObject
{
protected:
	PlayerFSM m_player_fsm;
	AnimatedSprite SquareSprite;
	AnimatedSprite CapsuleSprite;
	AnimatedSprite PolySprite;
	AnimatedSprite RaySprite;
	AnimatedSprite CircleSprite;
	GameObject();
	GameObject(const AnimatedSprite&, const AnimatedSprite&, const AnimatedSprite&, const AnimatedSprite&, const AnimatedSprite&);

public:
	virtual ~GameObject() = 0;
	virtual AnimatedSprite& getAnimatedSprite() = 0;
	virtual void handleInput(Input) = 0;
	virtual void update() = 0;

	virtual int getInput() = 0;
};

#endif // !GAME_OBJECT_H
