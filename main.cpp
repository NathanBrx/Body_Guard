#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
using namespace std;
using namespace sf;

#define SPRITE_SPEED 5

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard",Style::Fullscreen);
    
    window.setVerticalSyncEnabled (true);
    window.setKeyRepeatEnabled(false);

    // background texture
    Vector2u TextureSize;
    Vector2u WindowSize;
    Sprite background;
    Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("Map1.jpg")){
                cerr << "failed to load image" << endl;
                exit(1);
        }
        else{
            TextureSize = backgroundTexture.getSize(); //Get size of texture.
            WindowSize = window.getSize();             //Get size of window.

            float ScaleX = (float) WindowSize.x / TextureSize.x;
            float ScaleY = (float) WindowSize.y / TextureSize.y;    // Calculate scale

            background.setTexture(backgroundTexture);
            background.setScale(ScaleX, ScaleY);    // Set scale
        }
    backgroundTexture.setRepeated(false);
    background.setTexture(backgroundTexture);

    // Create sprite1 and apply texture1
    Texture texture1;
        if (!texture1.loadFromFile("Spritev1.png")){
            cerr << "failed to load image" << endl;
            exit(1);
        }
    texture1.setRepeated(false);
    texture1.setSmooth(true);
    Sprite sprite1;
    sprite1.setTexture(texture1);
    
    // Sprite coordinates
    int x=window.getSize().x/2.;
    int y=window.getSize().y/2.;

    // Flags for key pressed
    bool upFlag=false;
    bool downFlag=false;
    bool leftFlag=false;
    bool rightFlag=false;

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
                case  sf::Keyboard::Escape : window.close(); break;

                // up, down, left and right keys
                case sf::Keyboard::Up :     upFlag=true; break;
                case sf::Keyboard::Down:    downFlag=true; break;
                case sf::Keyboard::Left:    leftFlag=true; break;
                case sf::Keyboard::Right:   rightFlag=true; break;
                default : break;
                }
            }

            // If a key is released
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                // up, down, left and right keys
                case sf::Keyboard::Up :     upFlag=false; break;
                case sf::Keyboard::Down:    downFlag=false; break;
                case sf::Keyboard::Left:    leftFlag=false; break;
                case sf::Keyboard::Right:   rightFlag=false; break;
                default : break;
                }
            }
        }

        // Update coordinates
        if (leftFlag) x-=SPRITE_SPEED;
        if (rightFlag) x+=SPRITE_SPEED;
        if (upFlag) y-=SPRITE_SPEED;
        if (downFlag) y+=SPRITE_SPEED;

        // Check screen boundaries
        if (x<0) x=0;
        if (x>(int)window.getSize().x) x=window.getSize().x;
        if (y<0) y=0;
        if (y>(int)window.getSize().y) y=window.getSize().y;

        // Clear the window and apply grey background
        window.clear(Color::White);

        window.draw(background);

        // Rotate and draw the sprite1
        sprite1.setPosition(x,y);
        window.draw(sprite1);

        window.display();
    }
    return 0;
}