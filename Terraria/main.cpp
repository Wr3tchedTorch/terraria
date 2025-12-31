#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <unordered_set>

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
	Cat cat(catsTexture, "Data/black_cat_animations.dat");	
	cat.setPosition({ static_cast<float>(windowSize.x) / 2, 0 });
	cat.setScale({ 3.0f, 3.0f });

	const auto onKeyPressed = [&window, &cat](const sf::Event::KeyPressed& keyPressed)
		{
			if (keyPressed.scancode == sf::Keyboard::Scancode::Space)
			{
				cat.jump();
			}
		};

	sf::Texture dirtTexture("Images/dirt.png");
	
	// create a triangle strip
	sf::VertexArray triangleStrip(sf::PrimitiveType::TriangleStrip, 4);

	// define it as a rectangle, located at (10, 10) and with size 100x100
	triangleStrip[0].position = sf::Vector2f(10.f, 10.f);
	triangleStrip[1].position = sf::Vector2f(10.f, 110.f);
	triangleStrip[2].position = sf::Vector2f(110.f, 10.f);
	triangleStrip[3].position = sf::Vector2f(110.f, 110.f);

	// define its texture area to be a 25x50 rectangle starting at (0, 0)
	triangleStrip[0].texCoords = sf::Vector2f(0.f, 0.f);
	triangleStrip[1].texCoords = sf::Vector2f(0.f, 50.f);
	triangleStrip[2].texCoords = sf::Vector2f(25.f, 0.f);
	triangleStrip[3].texCoords = sf::Vector2f(25.f, 50.f);

	int32_t currentTime = 0;
	int32_t maxTime = 400;
	// run the program as long as the window is open

	std::vector<sf::Vector2f> dirtPositions;
	for (int i = 0; i < 10; i++)
	{
		dirtPositions.push_back({ static_cast<float>(windowSize.x) / 2 + 16 * 3 * i, 555 });
		dirtPositions.push_back({ static_cast<float>(windowSize.x) / 2 - 16 * 3 * i, 555 });
	}

	sf::Clock clock;
	while (window.isOpen())
	{
		float delta = clock.restart().asSeconds();

		currentTime += 1;

		window.handleEvents(onClose, onKeyPressed);

		window.clear(sf::Color(160, 217, 239));

		cat.physicsProcess(delta, dirtPositions);
		cat.playAnimation(delta);

		window.draw(cat);
		window.draw(triangleStrip, &dirtTexture);	

		window.display();
	}
}

