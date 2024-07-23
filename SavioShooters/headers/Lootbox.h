#ifndef LOOTBOX_H
#define LOOTBOX_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class LootBox
{
    public:
        sf::Sprite shape;
        sf::Texture* texture;

        LootBox(sf::Texture* texture, sf::Vector2u windowSize) 
        {
            this->texture = texture;
            shape.setTexture(*texture);
            shape.setPosition(rand() % windowSize.x - shape.getGlobalBounds().width + 100, -100);
        }

        int buff()
        {
            return rand() % 10 + 1;
        }

        ~LootBox() {}
};

#endif // LOOTBOX_H