#ifndef INPUT_H
#define INPUT_H
class Input
{
public:
	Input();
	~Input();

	enum Action
	{
		Square,
		Capsule,
		Poly,
		Ray,
		Circle
	};

	void setCurrent(Action);
	Action getCurrent();

private:
	Action m_current;
};
#endif