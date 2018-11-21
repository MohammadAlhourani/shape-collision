#include <iostream>
#include <NPC.h>
#include <Idle.h>
#include <Debug.h>

NPC::NPC() : GameObject()
{
	m_player_fsm.setCurrent(new Idle());
	m_player_fsm.setPrevious(new Idle());
}

NPC::NPC(const AnimatedSprite& s, const AnimatedSprite&c,const AnimatedSprite& p, const AnimatedSprite& r, const AnimatedSprite& cr) 
	: GameObject(s,c,p,r,cr)
{
	m_player_fsm.setCurrent(new Idle());
	m_player_fsm.setPrevious(new Idle());
}

NPC::~NPC()
{
}

AnimatedSprite& NPC::getAnimatedSprite()
{
	if (m_input == 0)
	{
		int frame = SquareSprite.getCurrentFrame();
		SquareSprite.setTextureRect(SquareSprite.getFrame(frame));
		return SquareSprite;
	}
	else if (m_input == 1)
	{
		int frame = CapsuleSprite.getCurrentFrame();
		CapsuleSprite.setTextureRect(CapsuleSprite.getFrame(frame));
		return CapsuleSprite;
	}
	else if (m_input == 2)
	{
		int frame = PolySprite.getCurrentFrame();
		PolySprite.setTextureRect(PolySprite.getFrame(frame));
		return PolySprite;
	}
	else if (m_input == 3)
	{
		int frame = RaySprite.getCurrentFrame();
		RaySprite.setTextureRect(RaySprite.getFrame(frame));
		return RaySprite;
	}
	else if (m_input == 4)
	{
		int frame = CircleSprite.getCurrentFrame();
		CircleSprite.setTextureRect(CircleSprite.getFrame(frame));
		return CircleSprite;
	}
}

void NPC::handleInput(Input in)
{
	DEBUG_MSG("Handle Input");

	m_input = in.getCurrent();
}

void NPC::update()
{
	//std::cout << "Handle Update" << std::endl;
	SquareSprite.update();
	CapsuleSprite.update();
	PolySprite.update();
	RaySprite.update();
	CircleSprite.update();
}

int NPC::getInput()
{
	return m_input;
}

