#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <GameObject.h>
#include <Player.h>
#include <NPC.h>
#include <Input.h>
#include <Debug.h>

using namespace std;



int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Load a NPC's sprites to display
	sf::Texture Texture;
	if (!Texture.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Setup Default Animated Sprite
	AnimatedSprite Square(Texture);
	Square.addFrame(sf::IntRect(3, 3, 84, 84));
	Square.addFrame(sf::IntRect(88, 3, 84, 84));
	Square.addFrame(sf::IntRect(173, 3, 84, 84));
	Square.addFrame(sf::IntRect(258, 3, 84, 84));
	Square.addFrame(sf::IntRect(343, 3, 84, 84));
	Square.addFrame(sf::IntRect(428, 3, 84, 84));

	AnimatedSprite Capsule(Texture);
	Capsule.addFrame(sf::IntRect(9, 115, 71, 28));
	Capsule.addFrame(sf::IntRect(94, 115, 71, 28));
	Capsule.addFrame(sf::IntRect(179, 115, 71, 28));
	Capsule.addFrame(sf::IntRect(264, 115, 71, 28));
	Capsule.addFrame(sf::IntRect(349, 115, 71, 28));
	Capsule.addFrame(sf::IntRect(434, 115, 71, 28));

	AnimatedSprite Poly(Texture);
	Poly.addFrame(sf::IntRect(7,175,73,77));
	Poly.addFrame(sf::IntRect(92, 175, 73, 77));
	Poly.addFrame(sf::IntRect(177, 175, 73, 77));
	Poly.addFrame(sf::IntRect(262, 175, 73, 77));
	Poly.addFrame(sf::IntRect(347, 175, 73, 77));
	Poly.addFrame(sf::IntRect(432, 175, 73, 77));

	AnimatedSprite Ray(Texture);
	Ray.addFrame(sf::IntRect(8, 285, 70, 29));
	Ray.addFrame(sf::IntRect(96, 285, 70, 29));
	Ray.addFrame(sf::IntRect(184, 285, 70, 29));
	Ray.addFrame(sf::IntRect(272, 285, 70, 29));
	Ray.addFrame(sf::IntRect(360, 285, 70, 29));
	Ray.addFrame(sf::IntRect(448, 285, 70, 29));

	AnimatedSprite Circle(Texture);
	Circle.addFrame(sf::IntRect(15, 352, 56, 63));
	Circle.addFrame(sf::IntRect(102, 352, 56, 63));
	Circle.addFrame(sf::IntRect(189, 352, 56, 63));
	Circle.addFrame(sf::IntRect(276, 352, 56, 63));
	Circle.addFrame(sf::IntRect(363, 352, 56, 63));
	Circle.addFrame(sf::IntRect(450, 352, 56, 63));

	// Setup the NPC
	GameObject &npc = NPC(Square,Capsule,Poly,Ray,Circle);

	// Setup the Player
	GameObject &player = Player(Square,Capsule,Poly,Ray,Circle);

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(npc.getAnimatedSprite().getPosition().x, npc.getAnimatedSprite().getPosition().y);
	aabb_npc.max = c2V(
		npc.getAnimatedSprite().getPosition().x +
		npc.getAnimatedSprite().getGlobalBounds().width,
		npc.getAnimatedSprite().getPosition().y +
		npc.getAnimatedSprite().getGlobalBounds().height);

	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);

	c2Circle circle_player;

	c2Capsule capsule_player;

	c2Poly poly_player;

	c2Ray ray_player;

	// Initialize Input
	Input PlayerInput;

	Input NpcInput;

	// Collision result
	int result = 0;

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		
		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y);

		if (move_to.x < 0) {
			direction.x *= -1;
			move_to.x = 0;
		}
		else if (move_to.x + npc.getAnimatedSprite().getGlobalBounds().width >= 800) { 
			direction.x *= -1;
			move_to.x = 800 - npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.y < 0) { 
			direction.y *= -1;
			move_to.y = 0;
		}
		else if (move_to.y + npc.getAnimatedSprite().getGlobalBounds().height >= 600) {
			direction.y *= -1;
			move_to.y = 600 - npc.getAnimatedSprite().getGlobalBounds().height;
		}
		
		npc.getAnimatedSprite().setPosition(move_to);

		// Update NPC AABB set x and y
		aabb_npc.min = c2V(
			npc.getAnimatedSprite().getPosition().x, 
			npc.getAnimatedSprite().getPosition().y
		);

		aabb_npc.max = c2V(
			npc.getAnimatedSprite().getPosition().x +
			npc.getAnimatedSprite().getGlobalBounds().width,
			npc.getAnimatedSprite().getPosition().y +
			npc.getAnimatedSprite().getGlobalBounds().height
		);

		// Update Player AABB
		aabb_player.min = c2V(
			player.getAnimatedSprite().getPosition().x, 
			player.getAnimatedSprite().getPosition().y
		);
		aabb_player.max = c2V(
			player.getAnimatedSprite().getPosition().x +
			player.getAnimatedSprite().getGlobalBounds().width, 
			player.getAnimatedSprite().getPosition().y + 
			player.getAnimatedSprite().getGlobalBounds().height
		);

		//circle for player
		circle_player.p = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
		circle_player.r = 10;

		//capsule player
		capsule_player.r = 21.5;
		capsule_player.a = c2V(player.getAnimatedSprite().getPosition().x + capsule_player.r, player.getAnimatedSprite().getPosition().y + capsule_player.r);
		capsule_player.b = c2V(player.getAnimatedSprite().getPosition().x - capsule_player.r + player.getAnimatedSprite().getGlobalBounds().width,
								player.getAnimatedSprite().getPosition().y + capsule_player.r);
		
		//polyplayer
		poly_player.count = 3;
		poly_player.verts[0] = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y + player.getAnimatedSprite().getGlobalBounds().height);
		poly_player.verts[1] = c2V(player.getAnimatedSprite().getPosition().x / 2.0f, player.getAnimatedSprite().getPosition().y);
		poly_player.verts[2] = c2V(player.getAnimatedSprite().getPosition().x + player.getAnimatedSprite().getGlobalBounds().width,
			player.getAnimatedSprite().getPosition().y + player.getAnimatedSprite().getGlobalBounds().height);

		c2Poly * poly_player_p = &poly_player;

		c2Norms(poly_player_p->verts, poly_player_p->norms, poly_player_p->count);

		//rayplayer

		ray_player.p = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
		
		ray_player.t = 41;

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				{
					PlayerInput.setCurrent(Input::Action::Square);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					PlayerInput.setCurrent(Input::Action::Capsule);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					PlayerInput.setCurrent(Input::Action::Poly);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
				{
					PlayerInput.setCurrent(Input::Action::Ray);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
				{
					PlayerInput.setCurrent(Input::Action::Circle);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
				{
					NpcInput.setCurrent(Input::Action::Square);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
				{
					NpcInput.setCurrent(Input::Action::Capsule);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
				{
					NpcInput.setCurrent(Input::Action::Poly);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
				{
					NpcInput.setCurrent(Input::Action::Ray);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
				{
					NpcInput.setCurrent(Input::Action::Circle);
				}
				break;
			default:
				break;
			}
		}

		// Handle input to Player
		player.handleInput(PlayerInput);

		npc.handleInput(NpcInput);

		// Update the Player
		player.update();

		// Update the Player
		npc.update();

		// Check for collisions
		
		if (player.getInput() == 0 && npc.getInput() == 0)
		{
			result = c2AABBtoAABB(aabb_player, aabb_npc);
		}
		else if (player.getInput() == 1 && npc.getInput() == 0)
		{
			result = c2AABBtoCapsule(aabb_npc,capsule_player);
		}
		else if (player.getInput() == 2 && npc.getInput() == 0)
		{
			result = c2AABBtoPoly(aabb_npc, poly_player_p,0);
		}
		else if (player.getInput() == 3 && npc.getInput() == 0)
		{
			result = c2RaytoAABB(ray_player, aabb_npc,0);
		}
		else if (player.getInput() == 4 && npc.getInput() == 0)
		{
			result = c2CircletoAABB(circle_player, aabb_npc);
		}

		cout << ((result != 0) ? ("Collision") : "") << endl;
		if (result) {
			//player.getAnimatedSprite().setColor(sf::Color(255, 0, 0));
		}
		else {
			//player.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		}
		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSprite());

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};