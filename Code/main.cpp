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
    Sprite backgroundSprite, spriteMain, projectile1;
    Texture backgroundTexture, textureMain, textureProjectile;

    Background background(backgroundSprite,"../Textures/Map1.jpg",{{0, 414}, {78, 429},{276, 279}, {400, 234},{730, 195}, {882, 66}});

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
        TextureSize = backgroundTexture.getSize(); //Get size of texture.
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

        


        // Créer des points pour définir les rectangles
        std::vector<sf::Vector2f> points = {
            {0, 414}, {78, 429},{276, 279}, {400, 234},{730, 195}, {882, 66}
        };

        // Créer un tableau de rectangles
        std::vector<sf::RectangleShape> rectangles;

        // Itérer sur les points deux par deux et créer un rectangle à chaque itération
        for (std::size_t i = 0; i < points.size() - 1; i += 1)
        {
            sf::Vector2f bottomLeft = points[i];
            sf::Vector2f bottomRight = points[i + 1];
            sf::RectangleShape rectangle = background.CreateRectangle(bottomLeft, bottomRight, sf::Color::Red);
            rectangles.push_back(rectangle);
        }

        window.clear(Color::White);
        
        window.draw(background.backgroundSprite);

        // Dessiner les rectangles
        for (const auto& rectangle : rectangles)
        {
            window.draw(rectangle);
        }

        A.isInWindow(window);
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