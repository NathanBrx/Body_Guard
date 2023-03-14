#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;
#include "mainheader.hpp"

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard"/*,Style::Fullscreen*/);
    
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

    Perso A(window.getSize().x/2.,window.getSize().y/2.,0.,100,5,10,5,spriteMain);
    bool upFlag=false;
    bool downFlag=false;
    bool leftFlag=false;
    bool rightFlag=false;

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
                
                case Keyboard::Z : upFlag=true; A.SetRotation(270.f); break;
                case Keyboard::S : downFlag=true; A.SetRotation(90.f); break;
                case Keyboard::Q : leftFlag=true; A.SetRotation(180.f); break;
                case Keyboard::D : rightFlag=true; A.SetRotation(0.f); break;
                case Keyboard::Up : tirer(projectiles,A,projectile1,270.f); break;
                case Keyboard::Down : tirer(projectiles,A,projectile1,90.f); break;
                case Keyboard::Left : tirer(projectiles,A,projectile1,180.f); break;
                case Keyboard::Right : tirer(projectiles,A,projectile1,0.f); break;
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


        // Clear the window and apply background
        window.clear(Color::White);

        window.draw(background);

        A.isInWindow(window);
        A.update(upFlag,downFlag,leftFlag,rightFlag,window);

        window.draw(A.persoSprite);

        for (size_t i = 0; i < projectiles.size(); i++){
            projectiles[i]->update(*projectiles[i],A,window,projectiles[i]->GetDirection());
            projectiles[i]->isAlive(*projectiles[i],window);
            window.draw(projectiles[i]->projectileSprite);
        }


        RectangleShape rectangle3(Vector2f(600,25));
        rectangle3.setFillColor(Color::Transparent);
        rectangle3.setOutlineThickness(5);
        rectangle3.setOutlineColor(Color(0,0,0));
        rectangle3.setPosition(25,25);
        window.draw(rectangle3);

        int couleurs[3];
        couleurs[0]=100;
        couleurs[1]=250;
        couleurs[2]=50;

        //HUD
        int pvs=A.GetPV();
        int pvs_max=A.GetPVMax();

        if (pvs<pvs_max*0.33){
            couleurs[0]=243;
            couleurs[1]=22;
            couleurs[2]=22;
        }
        else{
            if (pvs<pvs_max*0.67){
                couleurs[0]=252;
                couleurs[1]=255;
                couleurs[2]=51;
            }
        }
        RectangleShape rectangle2(Vector2f((pvs*600)/(pvs_max),25));
        rectangle2.setFillColor(Color(couleurs[0],couleurs[1],couleurs[2]));
        rectangle2.setPosition(25,25);
        window.draw(rectangle2);

        

        window.display();
    }
}