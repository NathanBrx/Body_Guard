#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#include "mainheader.hpp"
#include "generation.hpp"

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard"/*,Style::Fullscreen*/);
    
    window.setVerticalSyncEnabled (true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    // background texture
    Vector2u TextureSize;
    Vector2u WindowSize;
    Sprite background, spriteMain, projectile1, spriteEnnemy1;
    Texture backgroundTexture, textureSpriteLeft, textureSpriteRight, textureSpriteUp, textureSpriteDown, textureProjectile, textureEnnemy1, textureEnnemy1hit;
        if (!backgroundTexture.loadFromFile("../Textures/Map1.jpg")){
                cerr << "failed to load map texture" << endl;
                exit(1);
        }
        if (!textureSpriteLeft.loadFromFile("../Textures/sprite_left.png")){
            cerr << "failed to load spriteMain texture" << endl;
            exit(1);
        }
        if (!textureSpriteRight.loadFromFile("../Textures/sprite_right.png")){
            cerr << "failed to load spriteMain texture" << endl;
            exit(1);
        }
        if (!textureSpriteUp.loadFromFile("../Textures/sprite_up.png")){
            cerr << "failed to load spriteMain texture" << endl;
            exit(1);
        }
        if (!textureSpriteDown.loadFromFile("../Textures/sprite_down.png")){
            cerr << "failed to load spriteMain texture" << endl;
            exit(1);
        }
        if (!textureEnnemy1.loadFromFile("../Textures/ennemy1.png")){
            cerr << "failed to load spriteEnnemy1 texture" << endl;
            exit(1);
        }
        if (!textureProjectile.loadFromFile("../Textures/projectilev1.png")){
            cerr << "failed to load projectile texture" << endl;
            exit(1);
        }
        if (!textureEnnemy1hit.loadFromFile("../Textures/ennemy1hit.png")){
            cerr << "failed to load ennemy hit texture" << endl;
            exit(1);
        }
        else{
            TextureSize = backgroundTexture.getSize(); //Get size of texture.
            WindowSize = window.getSize();             //Get size of window.

            float ScaleX = (float) WindowSize.x / TextureSize.x;
            float ScaleY = (float) WindowSize.y / TextureSize.y;    // Calculate scale

            background.setTexture(backgroundTexture); // Set textures
            background.setScale(ScaleX, ScaleY);    // Set scales
            
            spriteMain.setTexture(textureSpriteRight);
            spriteMain.setScale(ScaleX,ScaleY);

            spriteEnnemy1.setTexture(textureEnnemy1);
            spriteEnnemy1.setScale(ScaleX,ScaleY);

            projectile1.setTexture(textureProjectile);
            projectile1.setScale(ScaleX,ScaleY);
        }
    backgroundTexture.setRepeated(false);

    textureSpriteRight.setRepeated(false);
    textureSpriteRight.setSmooth(true);
    
    textureProjectile.setRepeated(false);
    textureProjectile.setSmooth(true);

    Perso A(window.getSize().x/2.,window.getSize().y/2.,0.,100,5,10,5,spriteMain);
    bool upFlag=false;
    bool downFlag=false;
    bool leftFlag=false;
    bool rightFlag=false;
    bool shoot_ready = true;
    sf::Clock clock;
    vector<Projectile*> projectiles;
    vector<Perso*> ennemies;

    ennemies.push_back(new Perso(window.getSize().x/3.,window.getSize().y/2.,0.,50,5,5,5,spriteEnnemy1));

    int mat[9][8] = {0}; // Initialisation de la carte à 0
    generation(mat);

    while (window.isOpen())
    {
        if(!shoot_ready){
            sf::Time time1 = clock.getElapsedTime();
            if(time1 >= A.GetDelay()){
                shoot_ready = true;
            }
        }
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
                
                case Keyboard::Z : upFlag=true; A.persoSprite.setTexture(textureSpriteUp); break;
                case Keyboard::S : downFlag=true; A.persoSprite.setTexture(textureSpriteDown); break;
                case Keyboard::Q : leftFlag=true; A.persoSprite.setTexture(textureSpriteLeft); break;
                case Keyboard::D : rightFlag=true; A.persoSprite.setTexture(textureSpriteRight);break;
                case Keyboard::Up : if(shoot_ready){tirer(projectiles,A,projectile1,270.f);clock.restart();shoot_ready = false; break;}
                case Keyboard::Down : if(shoot_ready){tirer(projectiles,A,projectile1,90.f);clock.restart();shoot_ready = false; break;}
                case Keyboard::Left : if(shoot_ready){tirer(projectiles,A,projectile1,180.f);clock.restart();shoot_ready = false; break;}
                case Keyboard::Right : if(shoot_ready){tirer(projectiles,A,projectile1,0.f);clock.restart();shoot_ready = false; break;}
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

        for (size_t i = 0; i < ennemies.size(); i++){
            if (A.persoSprite.getGlobalBounds().intersects(ennemies[i]->persoSprite.getGlobalBounds())){
            A.Setpv(ennemies[i]->Getatk());
            }
            for (size_t j = 0; j < projectiles.size(); j++){
                if (projectiles[j]->isAlive(*projectiles[j],window)){
                    projectiles[j]->update(*projectiles[j],A,window,projectiles[j]->GetDirection());
                    window.draw(projectiles[j]->projectileSprite);
                    if (ennemies[i]->checkAlive() && projectiles[j]->hit(*ennemies[i])){
                        ennemies[i]->damage(textureEnnemy1hit,textureEnnemy1,window);
                        projectiles.erase(projectiles.begin()+j);
                        ennemies[i]->Setpv(A.Getatk());
                    }
                }
            }
            if (ennemies[i]->checkAlive()){
                window.draw(ennemies[i]->persoSprite);
            }
            else{
                ennemies.erase(ennemies.begin()+i);
            }
        }

        A.isInWindow(window);
        A.update(upFlag,downFlag,leftFlag,rightFlag,window);

        window.draw(A.persoSprite);

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
        int pvs=A.Getpv();
        int pvs_max=A.Getpvmax();

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