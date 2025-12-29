#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AnimationManager
{

public:
    bool loadFromFile(const std::string& filename);

    sf::IntRect getFrameTextureRect(std::string frameName);    
    bool frameExists(std::string frameName);
    void setAnimation(std::string animationPrefix);
    void nextFrame(bool loop, std::optional<std::string> nextAnimationPrefix = std::nullopt);
    std::string getCurrentAnimationFrameName() const;    

private:
    std::map<std::string, sf::IntRect> frameMap;
    
    std::string m_currentAnimation;
    int m_currentFrame = 0;
};

