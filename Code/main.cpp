#include <iostream>
#include <cmath>
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
    Sprite backgroundSprite, spriteMain, projectile1;
    Texture backgroundTexture, textureMain, textureProjectile;

    Background background(backgroundSprite,"../Textures/Map1.jpg",{{0, 390}, {78, 415}, {276, 279}, {400, 234},{730, 195},{815, 160}, {882, 66}, {890, 0}, {1070, 0}, {1280, 220},{1720, 148},{1840,400},{1920, 480},{1920, 660},{1136, 1080},{886, 1080},{0, 678}});

    background.SetBackground();

    if (!textureMain.loadFromFile("../Textures/Spritev1.png")){
        cerr << "failed to load spriteMain texture" << endl;
        exit(1);
    }
    if (!textureProjectile.loadFromFile("../Textures/projectilev1.png")){
        cerr << "failed to load projectile texture" << endl;
        exit(1);
    }
    else{
        TextureSize = background.backgroundTexture.getSize(); //Get size of texture.
        WindowSize = window.getSize();             //Get size of window.

        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float) WindowSize.y / TextureSize.y;    // Calculate scale
        
        background.SetTexture(ScaleX,ScaleY);

        spriteMain.setTexture(textureMain);
        spriteMain.setScale(ScaleX,ScaleY);

        projectile1.setTexture(textureProjectile);
        projectile1.setScale(ScaleX,ScaleY);
    }

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
    background.MakeRectangles();

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
        window.clear(Color::White);
        
        window.draw(background.backgroundSprite);

        // Dessiner les rectangles
        for (const auto& rectangle : background.rectangles)
        {
            //window.draw(rectangle);
        }

        A.isInWindow(window);

        for(std::size_t i = 0; i < background.borduresPoints.size() - 1; i += 1){
            sf::Vector2f point_A = background.borduresPoints[i];
            sf::Vector2f point_B = background.borduresPoints[i + 1];

            float a = sqrt(pow(point_B.x-A.GetX(),2)+pow(point_B.y-A.GetY(),2));
            float b = sqrt(pow(A.GetX()-point_A.x,2)+pow(A.GetY()-point_A.y,2));
            float c = sqrt(pow(point_B.x-point_A.x,2)+pow(point_B.y-point_A.y,2));

            float angle = acos((a*a+b*b-c*c)/(2*a*b));

            bool touchBorder = b<30 || a<30 || (3<angle && 3.3>angle);

            if (touchBorder) {
                if(upFlag){
                    upFlag=false;
                    A.SetY(A.GetY()+5);
                }
                if(downFlag){
                    downFlag=false;
                    A.SetY(A.GetY()-5);
                }
                if(leftFlag){
                    leftFlag=false;
                    A.SetX(A.GetX()+5);
                }
                if(rightFlag){
                    rightFlag=false;
                    A.SetX(A.GetX()-5);
                }
            }
        }

        A.update(upFlag,downFlag,leftFlag,rightFlag,window);

        for (size_t i = 0; i < projectiles.size(); i++){
            projectiles[i]->update(*projectiles[i],A,window,projectiles[i]->GetDirection());
            projectiles[i]->isAlive(*projectiles[i],window);
            window.draw(projectiles[i]->projectileSprite);
        }

        window.draw(A.persoSprite);

        window.display();
    }
}