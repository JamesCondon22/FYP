#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "ContextDecisionMaker.h"
#include "MathHelper.h"
#include "Obstacle.h"
#include "DirectionalLine.h"
#include "../Menus/State.h"
#include "GameNode.h"
#include "Behaviour.h"



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
	virtual bool getActive() = 0;
	virtual void setActive(bool active) = 0;
	virtual double getPathLength() = 0;
	virtual double getInterceptionTime() = 0;
	virtual double getAverageExecTime() = 0;
	virtual double getTimeEfficiency() = 0;
	virtual void setCollided(bool collide) = 0;
	virtual std::string getName() = 0;
	virtual sf::Color getColor() = 0;
	virtual void setState(GameState state) = 0;
	virtual void setBehaviourState(BehaviourState *state) = 0;
	virtual void setVisuals(bool visuals) = 0;
	virtual bool getVisuals() = 0;
};
