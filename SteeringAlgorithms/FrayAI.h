#pragma once
#ifndef FRAYAI
#define FRAYAI
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ContextDecisionMaker.h"

class FrayAI
{
public:
	FrayAI();
	~FrayAI();
	void update(double dt, sf::Vector2f position);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVel();
	sf::Vector2f normalize(sf::Vector2f vec);
	sf::RectangleShape m_rect;
	sf::Vector2f getPos();
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int size;
	double static const DEG_TO_RAD;
	double m_rotation;
	double m_speed;
	double MAX_SPEED;
	sf::Vector2f m_heading;
	ContextDecisionMaker mapDecisions;
};

#endif