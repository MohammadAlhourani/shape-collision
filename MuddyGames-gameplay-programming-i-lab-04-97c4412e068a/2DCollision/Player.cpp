#include <iostream>
#include <Player.h>
#include <Idle.h>
#include <Debug.h>

Player::Player() : GameObject()
{
	m_player_fsm.setCurrent(new Idle());
	m_player_fsm.setPrevious(new Idle());
}

Player::Player(const AnimatedSprite& s, const AnimatedSprite& c,const AnimatedSprite& p, const AnimatedSprite& r, const AnimatedSprite& cr)
	: GameObject(s,c,p,r,cr)
{
	m_player_fsm.setCurrent(new Idle());
	m_player_fsm.setPrevious(new Idle());
}

Player::~Player()
{
}

AnimatedSprite& Player::getAnimatedSprite()
{
	if (t_input == 0)
	{
		int frame = SquareSprite.getCurrentFrame();
		SquareSprite.setTextureRect(SquareSprite.getFrame(frame));
		return SquareSprite;
	}
	else if (t_input == 1)
	{
		int frame = CapsuleSprite.getCurrentFrame();
		CapsuleSprite.setTextureRect(CapsuleSprite.getFrame(frame));
		return CapsuleSprite;
	}
	else if (t_input == 2)
	{
		int frame = PolySprite.getCurrentFrame();
		PolySprite.setTextureRect(PolySprite.getFrame(frame));
		return PolySprite;
	}
	else if (t_input == 3)
	{
		int frame = RaySprite.getCurrentFrame();
		RaySprite.setTextureRect(RaySprite.getFrame(frame));
		return RaySprite;
	}
	else if (t_input == 4)
	{
		int frame = CircleSprite.getCurrentFrame();
		CircleSprite.setTextureRect(CircleSprite.getFrame(frame));
		return CircleSprite;
	}
}

void Player::handleInput(Input in)
{
	DEBUG_MSG("Handle Input");

	t_input = in.getCurrent();
}

void Player::update()
{
	//std::cout << "Handle Update" << std::endl;
	SquareSprite.update();
	CapsuleSprite.update();
	PolySprite.update();
	RaySprite.update();
	CircleSprite.update();
}

int Player::getInput()
{
	return t_input;
}

