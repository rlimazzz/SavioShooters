#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    sf::Sprite shape;

    Bullet(sf::Texture* texture, sf::Vector2f pos) {
        shape.setTexture(*texture);
        shape.setScale(0.05f, 0.05f);
        shape.setPosition(pos);
    }

    ~Bullet() {}
};

#endif // BULLET_H
