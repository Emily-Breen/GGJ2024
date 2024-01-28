#include "Customer.h"
#include <iostream>

void Customer::initialiseCustomer()
{
    customerBody.setSize(sf::Vector2f(80.0f, 100.0f));
    customerBody.setFillColor(sf::Color::Magenta);
    customerBody.setPosition(-10.0f, 225.0f);
    isActive = false;
}

void Customer::moveTowardCounter(sf::Vector2f targetPosition)
{
    sf::Vector2f customerPos = customerBody.getPosition();
    float customerHeight = customerBody.getSize().y;

    // Calculate the direction to the target
    sf::Vector2f direction = targetPosition - customerPos;

    // Calculate the distance to the target
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Normalize the direction
    direction /= distance;

    //std::cout << "Customer moving toward counter: " << customerPos.x << ", " << customerPos.y << std::endl;
    customerPos += direction * speed;

    
    if (customerPos.y + customerHeight > targetPosition.y)
    {
        customerPos.y = targetPosition.y - customerHeight;
        setAtCounter(true);
    }

    // Set the new position
    customerBody.setPosition(customerPos);
}

void Customer::moveFromCounter(sf::Vector2f targetPosition)
{
    sf::Vector2f customerPos = customerBody.getPosition();
    float customerHeight = customerBody.getSize().y;
    
    sf::Vector2f direction = targetPosition - customerPos; // Calculate the direction to the target

    //mag
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

   
    direction /= distance; //Normalize

    customerPos += direction * speed;

    if (customerPos.y + customerHeight > targetPosition.y)
    {
        customerPos.y = targetPosition.y - customerHeight;
        customerPos += direction * speed;
    }
    customerBody.setPosition(customerPos);
}

void Customer::setAtCounter(bool atCounterValue)
{
    atCounter = atCounterValue;
}

bool Customer::isAtCounter() const
{
    return atCounter;
}

void Customer::stop()
{
    velocity = sf::Vector2f(0.0f, 0.0f);
}

void Customer::spawnCustomer(sf::Vector2f spawnPosition)
{
    customerBody.setPosition(spawnPosition);
    isActive = true;
}


sf::RectangleShape Customer::getCustomerBody()
{
    return customerBody;
}

bool Customer::isInactive()
{
    return !isActive; // Return true if the customer is inactive
}
