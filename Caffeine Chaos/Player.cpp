#include "Player.h"



void Player::move(sf::Vector2f t_movement)
{
    playerBody.move(t_movement);
}

void Player::initialiseplayer()
{
    playerBody.setSize(sf::Vector2f(80.0f, 100.0f));
    playerBody.setFillColor(sf::Color::Transparent);
    playerBody.setPosition(500.0f, 550.0f);
}

sf::RectangleShape Player::getBody()
{
    //playerBody.setPosition(500.0f, 610.0f);
    return playerBody;
}


