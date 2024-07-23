#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <unistd.h>
#include <cstdlib>
#include "./headers/Player.h"
#include "./headers/Enemy.h"
#include "./headers/Bullet.h"
#include "./headers/Lootbox.h"

int main()
{
    //Window and some other useful stuff
    sf::RenderWindow window(sf::VideoMode(1366, 720), "Savio Shooters");
    int moveVariation = 10, shootTimer = 20, enemySpawnTimer = 0;
    sf::Color outLineDecoration(99, 35, 120);

    srand(time(NULL));
    window.setFramerateLimit(60);

    //Setting up textures, fonts, sounds, etc, handling possible errors
    sf::Font font;
    if(!font.loadFromFile("./fonts/airstrike.ttf"))
    {
        std::cout << "Failed to load airstrike font\n";
    }

    sf::Texture spaceshipTexture;
    if(!spaceshipTexture.loadFromFile("./sprites/spaceship.png"))
    {
        std::cout<< "Failed to load spaceship Texture\n";
    }

    sf::Texture bulletTexture;
    if(!bulletTexture.loadFromFile("./sprites/bullet.png"))
    {
        std::cout << "Failed to load bullet texture\n";
    }

    sf::Texture oneEyeTexture;
    if(!oneEyeTexture.loadFromFile("./sprites/oneEyeDemon.png")) 
    {
        std::cout << "Failed to load the oneEyeDemon texture\n";
    }

    sf::Texture catTexture;
    if(!catTexture.loadFromFile("./sprites/cat.png")) 
    {
        std::cout << "Failed to load the cat texture\n";
    }

    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("./images/space.png"))
    {
        std::cout << "Failed to load the space texture\n";
    }

    sf::Texture lemonTexture;
    if(!lemonTexture.loadFromFile("./sprites/lemon.png"))
    {
        std::cout << "Failed to load the lemon texture\n";
    }

    sf::Texture chestTexture;
    if(!chestTexture.loadFromFile("./sprites/mysteryChest.png"))
    {
        std::cout << "Failed to load the mystery chest texture\n";
    }


    //Audio things
    sf::Music bgMusic;
    if(!bgMusic.openFromFile("./audio/theme.ogg"))
    {
        std::cout << "Failed to load the theme song\n";
    }
    bgMusic.setVolume(20.f);
    bgMusic.play();
    bgMusic.setLoop(true);

    sf::SoundBuffer boomBuffer;
    if(!boomBuffer.loadFromFile("./audio/boom12.wav"))
    {
        std::cout << "Failed to load the boom sound effect\n";
    }

    sf::SoundBuffer coinBuffer;
    if(!coinBuffer.loadFromFile("./audio/coin.wav")) 
    {
        std::cout << "Failed to load the coin sound effect\n";
    }
    sf::Sound coinSound;
    coinSound.setBuffer(coinBuffer);

    sf::SoundBuffer failedBuffer;
    if(!failedBuffer.loadFromFile("./audio/lose.wav"))
    {
        std::cout << "failed to load the failed sound effect\n";
    }
    sf::Sound failedSound;
    failedSound.setBuffer(failedBuffer);

    sf::SoundBuffer gunfireBuffer;
    if(!gunfireBuffer.loadFromFile("./audio/gunfire.wav")) 
    {
        std::cout << "failed to load the gunfire sound effect\n";
    }
    sf::Sound gunfireSound;
    gunfireSound.setVolume(20.f);
    gunfireSound.setBuffer(gunfireBuffer);

    //Texts
    sf::Text hpText;
    hpText.setFont(font);
    hpText.setOutlineThickness(5);
    hpText.setOutlineColor(outLineDecoration);
    hpText.setCharacterSize(20);
    hpText.setFillColor(sf::Color::White);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setOutlineThickness(5);
    scoreText.setOutlineColor(outLineDecoration);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setOutlineThickness(5);
    gameOverText.setOutlineColor(outLineDecoration);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::White);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setOutlineThickness(5);
    restartText.setOutlineColor(outLineDecoration);
    restartText.setCharacterSize(40);
    restartText.setFillColor(sf::Color::White);

    //Main player initializer
    Player mPlayer(&spaceshipTexture, &boomBuffer);
    mPlayer.shape.setScale(5.f, 5.f);
    mPlayer.shape.setPosition((window.getSize().x - mPlayer.shape.getGlobalBounds().width)/2, (window.getSize().y - mPlayer.shape.getGlobalBounds().height));

    //Setting up the option for restart and surrender
    sf::Vector2f sizer(150.f, 50.f);
    sf::Vector2f unsizer(0.f, 0.f);
    sf::RectangleShape restartRect;
    sf::RectangleShape surrenderRect;

    //Chest initializer
    std::vector<LootBox> chests;

    //Enemies initializer
    std::vector<Enemy> enemies;


    while (window.isOpen())
    {
        //handling events l
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Resized) 
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        if(mPlayer.HP <= 0)
        {

            /*
            This part of the code is very unorganized but basically we are showing the menu of gameOver
            to our player
            */
            restartText.setPosition(window.getSize().x / 3, window.getSize().y / 3 + 50);
            restartText.setString("RESTART THE GAME?");
            restartText.setCharacterSize(40);
            
            gameOverText.setPosition(window.getSize().x / 3, window.getSize().y / 3);
            gameOverText.setString("GAME OVER");
            gameOverText.setCharacterSize(40);

            surrenderRect.setPosition(window.getSize().x / 3 + 250 , window.getSize().y / 3 + 100);
            surrenderRect.setFillColor(sf::Color::Red);
            surrenderRect.setSize(sizer);

            restartRect.setPosition(window.getSize().x / 3  , window.getSize().y / 3 + 100);
            restartRect.setSize(sizer);
            restartRect.setFillColor(sf::Color::Green);


            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
            {
                if(restartRect.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y - 50))
                {
                    coinSound.play();
                    mPlayer.reset();
                    mPlayer.shape.setPosition((window.getSize().x - mPlayer.shape.getGlobalBounds().width)/2, (window.getSize().y - mPlayer.shape.getGlobalBounds().height));
                    restartRect.setSize(unsizer);
                    surrenderRect.setSize(unsizer);
                    restartText.setCharacterSize(0);
                    gameOverText.setCharacterSize(0);
                    continue;
                }
                else if(surrenderRect.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y - 50))
                {
                    failedSound.play();
                    sleep(3);
                    window.close();
                }
            }
        }else {
            //Timers 
            int chestSpawn = rand() % 2000;
            if(chestSpawn == 1) 
            {
                chests.push_back(LootBox(&chestTexture, window.getSize()));
            }
            if(shootTimer < 25) 
            {
                shootTimer++;
            }
            if(enemySpawnTimer < 15)
            {
                enemySpawnTimer++;
            }
            if(enemySpawnTimer >= 15) 
            {
                int randomEnemy = rand() % 10 + 1;
                if(randomEnemy >= 1 && randomEnemy <= 5) 
                {
                    enemies.push_back(Enemy(&oneEyeTexture, window.getSize(), 1));  
                }
                else if(randomEnemy > 5 && randomEnemy <= 9) 
                {
                    enemies.push_back(Enemy(&catTexture, window.getSize(), 2));  
                }
                else if(randomEnemy == 10)
                {
                    enemies.push_back(Enemy(&lemonTexture, window.getSize(), 3));  
                }
                enemySpawnTimer = 0;
            }

            //Player Controls
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 25)
            {
                gunfireSound.play();
                sf::Vector2f playerPos = mPlayer.shape.getPosition();
                mPlayer.bullets.push_back(Bullet(&bulletTexture, sf::Vector2f(playerPos.x + 105, playerPos.y)));
                mPlayer.bullets.push_back(Bullet(&bulletTexture, sf::Vector2f(playerPos.x + 10 , playerPos.y)));
                shootTimer = 0;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                mPlayer.shape.move(0.f, -moveVariation);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
            {
                mPlayer.shape.move(0.f, moveVariation);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            {
                mPlayer.shape.move(-moveVariation, 0.f);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            {
                mPlayer.shape.move(moveVariation, 0.f);
            }

            //Hp text configuration
            hpText.setPosition(mPlayer.shape.getPosition().x, mPlayer.shape.getPosition().y - hpText.getGlobalBounds().height);
            hpText.setString(std::to_string(mPlayer.HP) + "/" + std::to_string(mPlayer.HPMax));

            //Score text configuration
            scoreText.setPosition(0, window.getSize().y - 70);
            scoreText.setString("SCORE : " + std::to_string(mPlayer.score));

            //Colision with window
            if(mPlayer.shape.getPosition().x <= 0) 
            {
                mPlayer.shape.setPosition(0.f, mPlayer.shape.getPosition().y);
            }
            if(mPlayer.shape.getPosition().x >= window.getSize().x - mPlayer.shape.getGlobalBounds().width) 
            {
                mPlayer.shape.setPosition(window.getSize().x - mPlayer.shape.getGlobalBounds().width, mPlayer.shape.getPosition().y);
            }
            if(mPlayer.shape.getPosition().y <= 0) 
            {
                mPlayer.shape.setPosition(mPlayer.shape.getPosition().x, 0.f);
            }
            if(mPlayer.shape.getPosition().y >= window.getSize().y - mPlayer.shape.getGlobalBounds().height)
            {
                mPlayer.shape.setPosition(mPlayer.shape.getPosition().x, window.getSize().y - mPlayer.shape.getGlobalBounds().height);
            }

            //background image configuration
            sf::Sprite bgSprite;
            bgSprite.setTexture(backgroundTexture);
            bgSprite.setScale(0.8f,0.8f);
            

            window.clear();
            window.draw(bgSprite);

            window.draw(mPlayer.shape);

            //Bullets
            for(size_t i = 0;i < mPlayer.bullets.size();i++) 
            {
                mPlayer.bullets[i].shape.move(0.f, -20.f);
                if(mPlayer.bullets[i].shape.getPosition().x > window.getSize().x) 
                {
                    mPlayer.bullets.erase(mPlayer.bullets.begin() + i);
                    break;
                }
                else if(mPlayer.bullets[i].shape.getPosition().y > window.getSize().y) 
                {
                    mPlayer.bullets.erase(mPlayer.bullets.begin() + i);
                    break;
                }
                for(size_t j = 0;j < enemies.size();j++) 
                {
                    if(mPlayer.bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
                    {
                        if(enemies[j].HP <= 0) 
                        {
                            enemies.erase(enemies.begin() + j);
                            mPlayer.score += 5;

                        }else 
                        {
                            enemies[j].HP -= 1;
                        }
                        mPlayer.bullets.erase(mPlayer.bullets.begin() + i);
                        break;
                    }
                }
                for(size_t j = 0;j < chests.size();j++) 
                {
                    if(mPlayer.bullets[i].shape.getGlobalBounds().intersects(chests[j].shape.getGlobalBounds()))
                    {
                        mPlayer.HP += chests[j].buff();
                        if(mPlayer.HP > 10) 
                        {
                            mPlayer.HP = 10;
                        }
                        chests.erase(chests.begin() + j);

                    }
                }
            }

            //Shooting bullets animation
            for(size_t i = 0;i < mPlayer.bullets.size();i++) 
            {
                window.draw(mPlayer.bullets[i].shape);
            }

            //Enemies animation
            for(size_t i = 0;i < enemies.size();i++) 
            {
                enemies[i].shape.move(0.f, +2.f);
        
                if(enemies[i].shape.getPosition().y >= window.getSize().y) 
                {
                    enemies.erase(enemies.begin() + i);
                    break;
                }
                if(enemies[i].shape.getGlobalBounds().intersects(mPlayer.shape.getGlobalBounds()))
                {
                    enemies.erase(enemies.begin() + i);
                    mPlayer.HP--;

                    if(mPlayer.HP <= 0) 
                    {
                        mPlayer.soundDying.play();
                    }

                    break;
                }
            }

            //Spawning enemies
            for(size_t i = 0;i < enemies.size();i++) 
            {
                window.draw(enemies[i].shape);
            }

            //Chests animation
            for(size_t i = 0;i < chests.size();i++) 
            {
                chests[i].shape.move(0.f, +2.f);

                if(chests[i].shape.getPosition().y >= window.getSize().y) 
                {
                    chests.erase(chests.begin() + i);
                    break;
                }
                if(chests[i].shape.getGlobalBounds().intersects(mPlayer.shape.getGlobalBounds()))
                {
                    mPlayer.HP += chests[i].buff();
                    chests.erase(chests.begin() + i);

                    if(mPlayer.HP > 10)
                    {
                        mPlayer.HP = 10;
                    }
                    break;
                }
            }

            for(size_t i = 0;i < chests.size();i++) 
            {
                chests[i].shape.setScale(5.f, 5.f);
                window.draw(chests[i].shape);
            }
        }

        //UI
        window.draw(hpText);
        window.draw(restartText);
        window.draw(scoreText);
        window.draw(gameOverText);
        window.draw(restartRect);
        window.draw(surrenderRect);

        window.display();
    }

    return 0;
}