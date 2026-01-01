#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <unordered_set>
#include "TileMap.h"
#include "DebugStatics.h"
#include "Cat.h"

sf::Vector2u windowSize({ 800, 600 });

int main()
{
	sf::RenderWindow window(sf::VideoMode({windowSize.x, windowSize.y}), "Themis Terraria");

	const auto onClose = [&window](const sf::Event::Closed&)
		{
			window.close();
		};

	sf::Texture catsTexture("Images/cats.png");
	Cat themis(catsTexture, "Data/black_cat_animations.dat");	
	themis.setPosition({ static_cast<float>(windowSize.x) / 2, static_cast<float>(windowSize.y)/2+100 });

	const auto onKeyPressed = [&window, &themis](const sf::Event::KeyPressed& keyPressed)
		{
			if (keyPressed.scancode == sf::Keyboard::Scancode::Space)
			{
				themis.jump();
			}
		};

	constexpr std::array<int, 128> level = {
		// Row 0: Floating Island top
	   -1, -1, -1, -1, -1,  0,  1,  2, -1, -1, -1, -1, -1, -1, -1, -1,
	    // Row 1: Floating Island bottom
	   -1, -1, -1, -1, -1, 32, 33, 34, -1, -1, -1, -1, -1, -1, -1, -1,
		// Row 2: Air gap
	   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		// Row 3: Surface peaks
	   -1, -1, -1, -1,  0,  1,  1,  1,  2, -1, -1,  0,  1,  2, -1, -1,
		// Row 4: Dirt layer with cave entrance
	    0,  1,  2, -1, 16, 17, 17, 17, 18, -1,  0, 17, 17, 18, -1, -1,
		// Row 5: Underground pockets
		16, 17, 18, -1, 32, 11, 11, 11, 11, -1, 16, 11, 11, 11, -1, -1,
		// Row 6: Dense dirt layer
		32, 11, 11, 11, 17, 17, 17, 17, 11, 11, 17, 17, 17, 11, 11, 17,
		// Row 7: Solid base foundation
		11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11
	};
	TileMap tilemap;
	if (!tilemap.load("Images/dirt.png", { 16, 16 }, level.data(), 16, 8, 2))
		return -1;

	tilemap.setPosition({ static_cast<float>(windowSize.x) / 2 , 450 });

	int32_t currentTime = 0;
	int32_t maxTime = 400;
	// run the program as long as the window is open


	DebugStatics debugStatics;
	debugStatics.createDebugRectangle(sf::FloatRect({ {0, 0}, {200.0f, 150.0f} }));

	sf::Clock clock;
	while (window.isOpen())
	{
		float delta = clock.restart().asSeconds();

		currentTime += 1;

		window.handleEvents(onClose, onKeyPressed);

		window.clear(sf::Color(160, 217, 239));

		themis.physicsProcess(delta, [&tilemap](sf::FloatRect rect) -> bool {
			return tilemap.overlaps(rect);
			});
		themis.playAnimation(delta);

		window.draw(themis);
		window.draw(tilemap);
		window.draw(debugStatics);

		window.display();
	}
}

