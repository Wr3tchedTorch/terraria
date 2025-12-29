#include "Animable.h"
#include <iostream>

Animable::Animable(sf::Texture& texture, std::string animationsDataFileName) : Entity(texture)
{
	m_animationManager.loadFromFile(animationsDataFileName);
}

void Animable::setCurrentFrame(std::string animationName)
{
	if (!m_animationManager.frameExists(animationName))
	{
		return;
	}
	sf::IntRect textureRect = m_animationManager.getFrameTextureRect(animationName);

	sf::Vector2f spriteSize(textureRect.size);
	m_sprite.setOrigin({ spriteSize.x / 2, spriteSize.y / 2 });

	m_sprite.setTextureRect(textureRect);
}

void Animable::setAnimation(std::string animationName)
{
	m_animationManager.setAnimation(animationName);
	setCurrentFrame(m_animationManager.getCurrentAnimationFrameName());
}

void Animable::playAnimation(float delta)
{
	m_currentAnimationTime += 1000 * delta;
	std::cout << "delta: " << std::to_string(delta) << " delta * 1000: " << std::to_string(1000 * delta) << " current_animation_time: " << std::to_string(m_currentAnimationTime) << "\n";
	
	if (m_currentAnimationTime >= m_maxAnimationDelayTime)
	{
		nextFrame();

		m_currentAnimationTime = 0;
	}
}

void Animable::setMaxAnimationDelayTime(float timeInMilliseconds)
{
	if (timeInMilliseconds < 0)
	{
		timeInMilliseconds = 0;
	}
	m_maxAnimationDelayTime = timeInMilliseconds;
}

void Animable::nextFrame()
{
	m_animationManager.nextFrame(true);
	setCurrentFrame(m_animationManager.getCurrentAnimationFrameName());
}
