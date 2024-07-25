#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Bullet.h"

class Player {
public:
    sf::Sprite shape;
    sf::Texture* texture;
    sf::Sound soundDying;
    int HP;
    int HPMax;
    int score;

    std::vector<Bullet> bullets;

    Player(sf::Texture* texture, sf::SoundBuffer* dyingBuffer) {
        HPMax = 10;
        HP = HPMax;
        score = 0;

        this->texture = texture;
        shape.setTexture(*texture);
        soundDying.setBuffer(*dyingBuffer);
    }

    void reset() {
        HPMax = 10;
        HP = HPMax;
        score = 0;
    }

    ~Player() {}
};

#endif // PLAYER_H
