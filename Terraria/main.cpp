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
				std::cout << "Jump!\n";
			}
		};

	sf::Texture dirtTexture("Images/dirt.png");
	sf::Sprite dirt(dirtTexture, {{18, 0}, {16, 16}});	
	dirt.scale({ 3.0f, 3.0f });

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
	
		for (const auto& pos : dirtPositions)
		{
			dirt.setPosition(pos);
			window.draw(dirt);
		}

		window.display();
	}
}
