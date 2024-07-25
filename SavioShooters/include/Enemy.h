#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    int HP;
    int HPMax;
    sf::Texture* texture;
    sf::Sprite shape;

    Enemy(sf::Texture* texture, sf::Vector2u windowSize, int HPMax) {
        this->HPMax = HPMax;
        HP = this->HPMax;

        shape.setTexture(*texture);
        shape.setScale(7.f, 7.f);
        shape.setPosition(rand() % windowSize.x - shape.getGlobalBounds().width + 100, -100);
    }

    ~Enemy() {}
};

#endif // ENEMY_H
