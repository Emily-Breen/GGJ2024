#pragma once
#include <SFML/Graphics.hpp>
class Customer
{
protected:
	sf::RectangleShape customerBody;
    float speed = 2;
	bool isActive;
	bool atCounter;
	sf::Vector2f velocity;
	


public:
	void initialiseCustomer();
	void moveTowardCounter(sf::Vector2f targetPosition);
	void moveFromCounter(sf::Vector2f targetPosition);
	void setAtCounter(bool atCounterValue);
	bool isAtCounter() const;
	void stop();
	void spawnCustomer(sf::Vector2f spawnPosition);
	sf::RectangleShape getCustomerBody();
	bool isInactive();
	
};

