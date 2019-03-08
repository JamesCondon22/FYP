#pragma once
#ifndef ENEMY
#define ENEMY
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "ContextDecisionMaker.h"
#include "MathHelper.h"
#include "Obstacle.h"
#include "DirectionalLine.h"

class Enemy
{
public:
	Enemy() { ; }
	virtual ~Enemy() { ; }
	virtual void update(double dt, sf::Vector2f position) = 0;
	virtual void render(sf::RenderWindow & window) = 0;
	virtual sf::Vector2f getVel() = 0;
	virtual sf::Vector2f getPos() = 0;
	virtual int getId() = 0;
};

#endif