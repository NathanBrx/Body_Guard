#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
using namespace std;
using namespace sf;
#include "mainheader.hpp"

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard",Style::Fullscreen);
    
    window.setVerticalSyncEnabled (true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    // background texture
    Vector2u TextureSize;
    Vector2u WindowSize;
    Sprite background, spriteMain, projectile1;
    Texture backgroundTexture, textureMain, textureProjectile;
        if (!backgroundTexture.loadFromFile("../Textures/Map1.jpg")){
                cerr << "failed to load map texture" << endl;
                exit(1);
        }
        if (!textureMain.loadFromFile("../Textures/Spritev1.png")){
            cerr << "failed to load spriteMain texture" << endl;
            exit(1);
        }
        if (!textureProjectile.loadFromFile("../Textures/projectilev1.png")){
            cerr << "failed to load projectile texture" << endl;
            exit(1);
        }
        else{
            TextureSize = backgroundTexture.getSize(); //Get size of texture.
            WindowSize = window.getSize();             //Get size of window.

            float ScaleX = (float) WindowSize.x / TextureSize.x;
            float ScaleY = (float) WindowSize.y / TextureSize.y;    // Calculate scale

            background.setTexture(backgroundTexture); // Set textures
            background.setScale(ScaleX, ScaleY);    // Set scales
            
            spriteMain.setTexture(textureMain);
            spriteMain.setScale(ScaleX,ScaleY);

            projectile1.setTexture(textureProjectile);
            projectile1.setScale(ScaleX,ScaleY);
        }
    backgroundTexture.setRepeated(false);

    textureMain.setRepeated(false);
    textureMain.setSmooth(true);
    
    textureProjectile.setRepeated(false);
    textureProjectile.setSmooth(true);

    Perso A(window.getSize().x/2.,window.getSize().y/2.,0.,100,5,10,spriteMain);
    bool upFlag=false;
    bool downFlag=false;
    bool leftFlag=false;
    bool rightFlag=false;
    float x = A.GetX(),y = A.GetY();
    float sprite1Rotation = A.GetRotation();

    vector<Projectile*> projectiles;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();

            // If a key is pressed
            if (event.type == Event::KeyPressed){
                switch (event.key.code){
                // If escape is pressed, close the application
                case  Keyboard::Escape : window.close(); break;

                // up, down, left and right keys
                
                case Keyboard::Z : upFlag=true; sprite1Rotation=270.f; break;
                case Keyboard::S : downFlag=true; sprite1Rotation=90.f; break;
                case Keyboard::Q : leftFlag=true; sprite1Rotation=180.f; break;
                case Keyboard::D : rightFlag=true; sprite1Rotation=0.f; break;
                case Keyboard::Up : tirer(projectiles,A,projectile1,270.f) ; break;
                case Keyboard::Down : tirer(projectiles,A,projectile1,90.f) ; break;
                case Keyboard::Left : tirer(projectiles,A,projectile1,180.f) ; break;
                case Keyboard::Right : tirer(projectiles,A,projectile1,0.f) ; break;
                default : break;
                }
            }

            // If a key is released
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                // up, down, left and right keys
                case Keyboard::Z : upFlag=false; break;
                case Keyboard::S : downFlag=false; break;
                case Keyboard::Q : leftFlag=false; break;
                case Keyboard::D : rightFlag=false; break;
                default : break;
                }
            }
        }
        // Update coordinates
        if (leftFlag) x-=A.GetSpeed();
        if (rightFlag) x+=A.GetSpeed();
        if (upFlag) y-=A.GetSpeed();
        if (downFlag) y+=A.GetSpeed();


        for (size_t i = 0; i < projectiles.size(); i++){
            switch ((int)projectiles[i]->getDirection()){
                case 270 : projectiles[i]->projectileSprite.move(0.f,-(float)A.GetSpeed()); break;
                case 90 : projectiles[i]->projectileSprite.move(0.f,(float)A.GetSpeed()); break;
                case 180 : projectiles[i]->projectileSprite.move(-(float)A.GetSpeed(),0.f); break;
                case 0 : projectiles[i]->projectileSprite.move((float)A.GetSpeed(),0.f); break;
                default : break;
            }
            if (projectiles[i]->projectileSprite.getPosition().y < 0 || projectiles[i]->projectileSprite.getPosition().y > window.getSize().y || projectiles[i]->projectileSprite.getPosition().x < 0 || projectiles[i]->projectileSprite.getPosition().x > window.getSize().x){
                projectiles.erase(projectiles.begin() + i);
            }
        }

        // Clear the window and apply background
        window.clear(Color::White);

        window.draw(background);

        // Rotate and draw the sprite1
        A.persoSprite.setOrigin(50.,50.);
        A.update(x,y,window);;
        A.persoSprite.setRotation(sprite1Rotation);

        for (size_t i = 0; i < projectiles.size(); i++){
            window.draw(projectiles[i]->projectileSprite);
        }

        window.draw(A.persoSprite);
        window.display();
    }
}