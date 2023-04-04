#include "mainheader.hpp"

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard"/*,Style::Fullscreen*/);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    Vector2u TextureSize;
    Vector2u WindowSize;
    Sprite backgroundSprite, spriteMain, projectile1, spriteEnnemy1;
    Texture backgroundTexture, textureSpriteLeft, textureSpriteRight, textureSpriteUp, textureSpriteDown, textureSpriteDownInv,textureSpriteLeftInv,textureSpriteRightInv,textureSpriteUpInv,textureProjectile, textureEnnemy1, textureEnnemy1hit;

    string texturesPath = "../Textures/"; // Linux
    //string texturesPath = "Textures\\"; // Windows

    // Arri�re-plan
    loadFile(backgroundTexture, texturesPath + "Map1.jpg");

    // Joueur
    loadFile(textureSpriteLeft, texturesPath + "sprite_left.png");
    loadFile(textureSpriteRight, texturesPath + "sprite_right.png");
    loadFile(textureSpriteUp, texturesPath + "sprite_up.png");
    loadFile(textureSpriteDown, texturesPath + "sprite_down.png");
    loadFile(textureSpriteLeftInv, texturesPath + "sprite_left_inv.png");
    loadFile(textureSpriteRightInv, texturesPath + "sprite_right_inv.png");
    loadFile(textureSpriteUpInv, texturesPath + "sprite_up_inv.png");
    loadFile(textureSpriteDownInv, texturesPath + "sprite_down_inv.png");
    // Ennemies
    loadFile(textureEnnemy1, texturesPath + "ennemy1.png");
    loadFile(textureEnnemy1hit, texturesPath + "ennemy1hit.png");

    // Projectiles
    loadFile(textureProjectile, texturesPath + "projectilev1.png");

    WindowSize = window.getSize();             //Get size of window.

    float ScaleX = (float)WindowSize.x / 1920;
    float ScaleY = (float)WindowSize.y / 1080;    // Calculate scale

    backgroundSprite.setTexture(backgroundTexture); // Set textures
    backgroundSprite.setScale(ScaleX, ScaleY);    // Set scales

    spriteMain.setTexture(textureSpriteRight);
    spriteMain.setScale(ScaleX, ScaleY);

    spriteEnnemy1.setTexture(textureEnnemy1);
    spriteEnnemy1.setScale(ScaleX, ScaleY);

    projectile1.setTexture(textureProjectile);
    projectile1.setScale(ScaleX, ScaleY);

    backgroundTexture.setRepeated(false);

    textureSpriteRight.setRepeated(false);
    textureSpriteRight.setSmooth(true);

    textureProjectile.setRepeated(false);
    textureProjectile.setSmooth(true);

    Background background(backgroundSprite, "../Textures/Map1.jpg", { {0, 390}, {78, 415}, {276, 279}, {400, 234},{730, 195},{815, 160}, {882, 66}, {890, 0}, {1070, 0}, {1280, 220},{1720, 148},{1840,400},{1920, 480},{1920, 660},{1136, 1080},{886, 1080},{0, 678} });

    background.SetBackground();

    Perso A(window.getSize().x / 2., window.getSize().y / 2., 0., 100, 5, 10, 5, spriteMain);
    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    vector<Projectile*> projectiles;
    vector<Perso*> ennemies;

    RectangleShape rectangle3(Vector2f(600, 25));
    rectangle3.setFillColor(Color::Transparent);
    rectangle3.setOutlineThickness(5);
    rectangle3.setOutlineColor(Color(0, 0, 0));
    rectangle3.setPosition(25, 25);

    int couleurs[3];
    couleurs[0] = 100;
    couleurs[1] = 250;
    couleurs[2] = 50;

    ennemies.push_back(new Perso(window.getSize().x / 3., window.getSize().y / 2., 0., 50, 5, 5, 5, spriteEnnemy1));


    int mat[9][8] = { 0 }; // Initialisation de la carte � 0
    generation(mat);
    bool shoot_ready = true;
    sf::Clock clock;
    sf::Clock clockiframes;
    bool invincible = false;
    while (window.isOpen())
    {
        if(!shoot_ready){
            sf::Time time1 = clock.getElapsedTime();
            if(time1 >= A.GetDelay()){
                shoot_ready = true;
            }
        }
        if(invincible){
            sf::Time time2 = clockiframes.getElapsedTime();
            if(time2 >=sf::milliseconds(500)){
                invincible = false;
                if(A.GetRotation() == 0.){A.persoSprite.setTexture(textureSpriteRight);}
                if(A.GetRotation() == 90.){A.persoSprite.setTexture(textureSpriteUp);}
                if(A.GetRotation() == 180.){A.persoSprite.setTexture(textureSpriteLeft);}
                if(A.GetRotation() == 270.){A.persoSprite.setTexture(textureSpriteDown);}
            }
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();

            // If a key is pressed
            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    // If escape is pressed, close the application
                case  Keyboard::Escape: window.close(); break;

                    // up, down, left and right keys

                case Keyboard::Z: upFlag = true; if(invincible){A.persoSprite.setTexture(textureSpriteUpInv);}else {A.persoSprite.setTexture(textureSpriteUp);};A.SetRotation(90.f) ;break;
                case Keyboard::S: downFlag = true; if(invincible){A.persoSprite.setTexture(textureSpriteDownInv);}else {A.persoSprite.setTexture(textureSpriteDown);};A.SetRotation(270.f) ;break;
                case Keyboard::Q: leftFlag = true; if(invincible){A.persoSprite.setTexture(textureSpriteLeftInv);}else{A.persoSprite.setTexture(textureSpriteLeft);};A.SetRotation(180.f) ;break;
                case Keyboard::D: rightFlag = true; if(invincible){A.persoSprite.setTexture(textureSpriteRightInv);}else{A.persoSprite.setTexture(textureSpriteRight);};A.SetRotation(0.f) ;break;
                case Keyboard::Up : if(shoot_ready){tirer(projectiles,A,projectile1,270.f);clock.restart();shoot_ready = false; break;}
                case Keyboard::Down : if(shoot_ready){tirer(projectiles,A,projectile1,90.f);clock.restart();shoot_ready = false; break;}
                case Keyboard::Left : if(shoot_ready){tirer(projectiles,A,projectile1,180.f);clock.restart();shoot_ready = false; break;}
                case Keyboard::Right : if(shoot_ready){tirer(projectiles,A,projectile1,0.f);clock.restart();shoot_ready = false; break;}
                default: break;
                }
            }

            // If a key is released
            if (event.type == Event::KeyReleased)
            {
                switch (event.key.code)
                {
                    // up, down, left and right keys
                    case Keyboard::Z: upFlag = false; break;
                    case Keyboard::S: downFlag = false; break;
                    case Keyboard::Q: leftFlag = false; break;
                    case Keyboard::D: rightFlag = false; break;
                    default: break;
                }
            }
        }

        // Clear the window and apply background
        window.clear(Color::White);

        for (size_t i = 0; i < background.borduresPoints.size() - 1; i += 1) {
            Vector2f point_A = background.borduresPoints[i];
            Vector2f point_B = background.borduresPoints[i + 1];

            double a = sqrt(pow(point_B.x - A.GetX(), 2) + pow(point_B.y - A.GetY(), 2));
            double b = sqrt(pow(A.GetX() - point_A.x, 2) + pow(A.GetY() - point_A.y, 2));
            double c = sqrt(pow(point_B.x - point_A.x, 2) + pow(point_B.y - point_A.y, 2));

            double angle = acos((a * a + b * b - c * c) / (2 * a * b));

            bool touchBorder = b < 30 || a < 30 || (3 < angle && 3.3 > angle);

            if (touchBorder) {
                if (upFlag) {
                    upFlag = false;
                    A.SetY(A.GetY() + 5);
                }
                if (downFlag) {
                    downFlag = false;
                    A.SetY(A.GetY() - 5);
                }
                if (leftFlag) {
                    leftFlag = false;
                    A.SetX(A.GetX() + 5);
                }
                if (rightFlag) {
                    rightFlag = false;
                    A.SetX(A.GetX() - 5);
                }
            }
        }

        window.draw(background.backgroundSprite);

        for (size_t j = 0; j < projectiles.size(); j++) {
            if (projectiles[j]->isAlive(*projectiles[j], window)) {

                bool touchBorder = false;
                for (size_t i = 0; i < background.borduresPoints.size() - 1; i += 1) {
                    Vector2f point_A = background.borduresPoints[i];
                    Vector2f point_B = background.borduresPoints[i + 1];

                    float a = sqrt(pow(point_B.x - projectiles[j]->projectileSprite.getPosition().x, 2) + pow(point_B.y - projectiles[j]->projectileSprite.getPosition().y, 2));
                    float b = sqrt(pow(projectiles[j]->projectileSprite.getPosition().x - point_A.x, 2) + pow(projectiles[j]->projectileSprite.getPosition().y - point_A.y, 2));
                    float c = sqrt(pow(point_B.x - point_A.x, 2) + pow(point_B.y - point_A.y, 2));

                    float angle = acos((a * a + b * b - c * c) / (2 * a * b));
                    touchBorder = touchBorder || (3 < angle && 3.3 > angle);
                    
                }

                projectiles[j]->update(*projectiles[j], A, window, projectiles[j]->GetDirection());
                window.draw(projectiles[j]->projectileSprite);
                if (touchBorder) {
                    projectiles.erase(projectiles.begin() + j);
                }
            }
        }
        for (size_t i = 0; i < ennemies.size(); i++) {
            if (A.persoSprite.getGlobalBounds().intersects(ennemies[i]->persoSprite.getGlobalBounds())&& !invincible) {
                A.Setpv(ennemies[i]->Getatk());
                invincible = true;
                clockiframes.restart();
                if(A.GetRotation() == 0.){A.persoSprite.setTexture(textureSpriteRightInv);}
                if(A.GetRotation() == 90.){A.persoSprite.setTexture(textureSpriteUpInv);}
                if(A.GetRotation() == 180.){A.persoSprite.setTexture(textureSpriteLeftInv);}
                if(A.GetRotation() == 270.){A.persoSprite.setTexture(textureSpriteDownInv);}

            }
            for (size_t j = 0; j < projectiles.size(); j++) {
                if (projectiles[j]->isAlive(*projectiles[j], window)) {
                    if (ennemies[i]->checkAlive() && projectiles[j]->hit(*ennemies[i])) {
                        ennemies[i]->damage(textureEnnemy1hit, textureEnnemy1, window);
                        projectiles.erase(projectiles.begin() + j);
                        ennemies[i]->Setpv(A.Getatk());
                    }
                }
            }
            if (ennemies[i]->checkAlive()) {
                window.draw(ennemies[i]->persoSprite);
            }
            else {
                ennemies.erase(ennemies.begin() + i);
            }
        }

        A.isInWindow(window);
        A.update(upFlag, downFlag, leftFlag, rightFlag, window);

        window.draw(A.persoSprite);

        window.draw(rectangle3);

        //HUD

        if (A.Getpv() < A.Getpvmax() * 0.33) {
            couleurs[0] = 243;
            couleurs[1] = 22;
            couleurs[2] = 22;
        }
        else {
            if (A.Getpv() < A.Getpvmax() * 0.67) {
                couleurs[0] = 252;
                couleurs[1] = 255;
                couleurs[2] = 51;
            }
        }

        RectangleShape rectangle2(Vector2f((A.Getpv() * 600) / (A.Getpvmax()), 25));

        rectangle2.setFillColor(Color(couleurs[0], couleurs[1], couleurs[2]));
        rectangle2.setPosition(25, 25);

        window.draw(rectangle2);

        window.display();
    }
}