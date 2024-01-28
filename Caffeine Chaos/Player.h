#pragma once
#include <SFML/Graphics.hpp>
class Player {

protected:
	sf::RectangleShape playerBody;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	int speed;
	int direction;
	int x;
	int y;

public:
	void move(sf::Vector2f t_movement);
	void initialiseplayer();
	sf::RectangleShape getBody();
	
	





};

