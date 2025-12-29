#include "Animable.h"

namespace sf {
	class Texture;
}

#pragma once
class Cat : public Animable
{
public:
	float speed = 100.0f;

	using Animable::Animable;
	void physicsProcess(float delta);
};

