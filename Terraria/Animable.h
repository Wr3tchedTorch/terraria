#include "AnimationManager.h"
#include "Entity.h"

#pragma once
class Animable : public Entity
{
public:
	
	Animable(sf::Texture& texture, std::string animationsDataFileName);

	void setCurrentFrame(std::string animationName);
	void setAnimation(std::string animationName);
	void playAnimation(float delta);
	void setMaxAnimationDelayTime(float timeInMilliseconds);

private:
	float m_currentAnimationTime = 0;
	float m_maxAnimationDelayTime = 100.0f;
	int m_currentFrame = 0;	

	AnimationManager m_animationManager;

	void nextFrame();
};

