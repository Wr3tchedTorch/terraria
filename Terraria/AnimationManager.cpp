#include "AnimationManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool AnimationManager::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        // Skip comments or empty lines
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string name;
        int x, y, w, h;

        if (ss >> name >> x >> y >> w >> h) {
            frameMap[name] = sf::IntRect({ {x, y}, {w, h} });
        }
    }
    return true;
}

sf::IntRect AnimationManager::getFrameTextureRect(std::string frameName)
{
    return frameMap[frameName];    
}

bool AnimationManager::frameExists(std::string frameName)
{
    return frameMap.find(frameName) != frameMap.end();
}

void AnimationManager::setAnimation(std::string animationPrefix)
{
   m_currentAnimation = animationPrefix;
   m_currentFrame = 0;
}

void AnimationManager::nextFrame(bool loop, std::optional<std::string> nextAnimationPrefix)
{
    std::string frameName = m_currentAnimation + std::to_string(m_currentFrame+1);
    if (frameExists(frameName))
    {
        m_currentFrame++;
        return;
    }
    if (loop)
    {
        m_currentFrame = 0;
        return;
    }
    if (nextAnimationPrefix.has_value())
    {
        m_currentAnimation = nextAnimationPrefix.value();
        m_currentFrame = 0;
    }
}

std::string AnimationManager::getCurrentAnimationFrameName() const
{
    return m_currentAnimation + std::to_string(m_currentFrame);
}
