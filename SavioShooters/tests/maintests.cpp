#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include "../include/Lootbox.h"
#include "../include/Bullet.h"
#include "../include/Player.h"
#include "../include/Enemy.h"

TEST_CASE("Player initialization", "[Player]") {
    sf::Texture textureTest;
    textureTest.create(50,50);
    sf::SoundBuffer bufferTest;

    bufferTest.loadFromFile("../audio/coin.wav");

    Player test(&textureTest, &bufferTest);

    REQUIRE(test.shape.getTexture() == &textureTest);
}

TEST_CASE("Enemy initialization", "[Enemy]") {
    sf::Texture textureTest;
    sf::Vector2u sizez(100.f,100.f);
    textureTest.create(50,50);
    int HPtest = 10;

    Enemy test(&textureTest, sizez, HPtest);

    REQUIRE(test.shape.getTexture() == &textureTest);
    REQUIRE(test.HPMax == HPtest);

}

TEST_CASE("Bullet initialization", "[Bullet]") {
    sf::Texture textureTest;
    sf::Vector2f sizez(100.f,100.f);
    textureTest.create(50,50);

    Bullet test(&textureTest, sizez);

    REQUIRE(test.shape.getTexture() == &textureTest);

}

TEST_CASE("LootBox initialization", "[LootBox]") {
    sf::Texture textureTest;
    sf::Vector2u sizez(100.f,100.f);
    textureTest.create(50, 50);
    LootBox test(&textureTest, sizez);

    REQUIRE(test.texture == &textureTest);
}

TEST_CASE("LootBox buff value", "[LootBox]") {
    sf::Texture textureTest;
    sf::Vector2u sizez(100.f,100.f);
    textureTest.create(50, 50);
    LootBox test(&textureTest, sizez);

    int buffValue = test.buff();
    REQUIRE(buffValue >= 1);
    REQUIRE(buffValue <= 10);    
}