#include <GameObject.h>
#include <Debug.h>

GameObject::GameObject() { }

GameObject::GameObject(const AnimatedSprite& as, const AnimatedSprite& cs, const AnimatedSprite& ps, const AnimatedSprite& rs, const AnimatedSprite& crs)
	: SquareSprite(as),CapsuleSprite(cs),PolySprite(ps),RaySprite(rs),CircleSprite(crs) { }

GameObject::~GameObject() { }