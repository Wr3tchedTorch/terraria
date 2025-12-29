#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

#include "Cat.h"

sf::Vector2u windowSize({ 800, 600 });

int main()
{
	sf::RenderWindow window(sf::VideoMode({windowSize.x, windowSize.y}), "Themis Terraria");

	const auto onClose = [&window](const sf::Event::Closed&)
		{
			window.close();
		};

	const auto onTextEntered = [&window](const sf::Event::TextEntered& textEntered)
		{
			if (textEntered.unicode < 128)
				std::cout << "ASCII character typed: " << static_cast<char>(textEntered.unicode) << std::endl;
		};

	sf::Texture catsTexture("Images/cats.png");

	Cat cat(catsTexture, "Data/black_cat_animations.dat");	
	cat.setPosition({ static_cast<float>(windowSize.x) / 2, 
					  static_cast<float>(windowSize.y) / 2 });

	std::string animationWalkPrefix = "walk";
	std::string animationIdlePrefix = "idle";
	cat.setAnimation(animationWalkPrefix);
	
	int32_t currentTime = 0;
	int32_t maxTime = 400;
	// run the program as long as the window is open

	sf::Clock clock;
	while (window.isOpen())
	{
		float delta = clock.restart().asSeconds();

		currentTime += 1;

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
				continue;
			}
		}

		window.clear(sf::Color(160, 217, 239));

		cat.PhysicsProcess(delta);
		cat.PlayAnimation(delta);

		window.draw(cat);

		window.display();
	}
}
