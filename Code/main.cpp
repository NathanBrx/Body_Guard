#include "mainheader.hpp"

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard"/*,Style::Fullscreen*/);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    Vector2u TextureSize;
    Vector2u WindowSize;
    Sprite backgroundSprite, spriteMain, projectile1, spriteEnnemy1, speed, sword, arrows, heart;
    Texture backgroundTexture, textureSpriteLeft, textureSpriteRight, textureSpriteUp, textureSpriteDown, textureProjectile, textureEnnemy1, textureEnnemy1hit, textureSpeed, textureSword, textureArrows, textureHeart;
    Text vitesseDeplacement, vitesseTir, attaque;
    Font policeStats;

    string texturesPath = "../Textures/"; // Linux
    //string texturesPath = "Textures\\"; // Windows

    // Arri�re-plan
    loadFile(backgroundTexture, texturesPath + "Map1.jpg");

    // Joueur
    loadFile(textureSpriteLeft, texturesPath + "sprite_left.png");
    loadFile(textureSpriteRight, texturesPath + "sprite_right.png");
    loadFile(textureSpriteUp, texturesPath + "sprite_up.png");
    loadFile(textureSpriteDown, texturesPath + "sprite_down.png");

    // Ennemies
    loadFile(textureEnnemy1, texturesPath + "ennemy1.png");
    loadFile(textureEnnemy1hit, texturesPath + "ennemy1hit.png");

    // Projectiles
    loadFile(textureProjectile, texturesPath + "projectilev1.png");

    //Icônes HUD
    loadFile(textureSpeed, texturesPath + "speed.png");
    loadFile(textureSword, texturesPath + "sword.png");
    loadFile(textureArrows, texturesPath + "arrows.png");
    loadFile(textureHeart, texturesPath + "heart.png");

    //Police
    if (!policeStats.loadFromFile("../Textures/Nabla-Regular.ttf")) {
        cerr << "Failed to load font" << endl;
        exit(1);
    }
    
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

    //Textures HUD
    heart.setTexture(textureHeart);
    heart.setScale(Vector2f(0.08f,0.08f));
    heart.setPosition(25, 10);

    speed.setTexture(textureSpeed);
    speed.setScale(Vector2f(0.1f,0.1));            
    speed.setPosition(25,70); 

    sword.setTexture(textureSword);
    sword.setScale(Vector2f(0.08f,0.08f));
    sword.setPosition(25,130);

    arrows.setTexture(textureArrows);
    arrows.setScale(Vector2f(0.08f,0.08f));
    arrows.setPosition(25,190);



    vitesseDeplacement.setFont(policeStats);
    vitesseDeplacement.setCharacterSize(35);
    vitesseDeplacement.setFillColor(Color::White);
    vitesseDeplacement.setPosition(80,70);

    vitesseTir.setFont(policeStats);
    vitesseTir.setCharacterSize(35);
    vitesseTir.setFillColor(Color::White);
    vitesseTir.setPosition(80,190);

    attaque.setFont(policeStats);
    attaque.setCharacterSize(35);
    attaque.setFillColor(Color::White);
    attaque.setPosition(80,130);

    Background background(backgroundSprite, "../Textures/Map1.jpg", { {0, 390}, {78, 415}, {276, 279}, {400, 234},{730, 195},{815, 160}, {882, 66}, {890, 0}, {1070, 0}, {1280, 220},{1720, 148},{1840,400},{1920, 480},{1920, 660},{1136, 1080},{886, 1080},{0, 678} });

    background.SetBackground();

    Perso A(window.getSize().x / 2., window.getSize().y / 2., 0., 100, 5, 10, 5, spriteMain);
    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    vector<Projectile*> projectiles;
    vector<Perso*> ennemies;
    vector<Projectile_ennemi*> projectiles_ennemi;
    vector<Clock> ennemy_shoot_time;

    RectangleShape rectangle3(Vector2f(600,25));
    rectangle3.setFillColor(Color::Transparent);
    rectangle3.setOutlineThickness(5);
    rectangle3.setOutlineColor(Color(0,0,0));
    rectangle3.setPosition(80,20);
    window.draw(rectangle3);

    int couleurs[3];
    couleurs[0] = 100;
    couleurs[1] = 250;
    couleurs[2] = 50;

    ennemies.push_back(new Perso(window.getSize().x / 3., window.getSize().y / 2., 0., 50, 5, 5, 5, spriteEnnemy1));
    ennemy_shoot_time.push_back(Clock());


    int mat[9][8] = { 0 }; // Initialisation de la carte � 0
    generation(mat);
    bool shoot_ready = true;
    sf::Clock clock;
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
            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    // If escape is pressed, close the application
                case  Keyboard::Escape: window.close(); break;

                    // up, down, left and right keys

                case Keyboard::Z: upFlag = true; A.persoSprite.setTexture(textureSpriteUp); break;
                case Keyboard::S: downFlag = true; A.persoSprite.setTexture(textureSpriteDown); break;
                case Keyboard::Q: leftFlag = true; A.persoSprite.setTexture(textureSpriteLeft); break;
                case Keyboard::D: rightFlag = true; A.persoSprite.setTexture(textureSpriteRight); break;
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
            if (A.persoSprite.getGlobalBounds().intersects(ennemies[i]->persoSprite.getGlobalBounds())) {
                A.Setpv(ennemies[i]->Getatk());
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
                ennemy_shoot_time.erase(ennemy_shoot_time.begin() + i);
            }

            if(!shoot_ready){
            sf::Time time1 = clock.getElapsedTime();
            if(time1 >= A.GetDelay()){
                shoot_ready = true;
            }
        }
            Time time2 = (ennemy_shoot_time[i]).getElapsedTime();
            if(time2>=ennemies[i]->GetDelay()){
                projectiles_ennemi.push_back((new Projectile_ennemi(ennemies[i]->GetX(),ennemies[i]->GetY(), A.GetX(), A.GetY(), ennemies[i]->GetatkSpeed(), projectile1)));
                ennemy_shoot_time[i].restart();
            }

            for (size_t j = 0; j < projectiles_ennemi.size(); j++) {
                if (projectiles_ennemi[j]->isAlive(window)) {
                    projectiles_ennemi[j]->update(window);
                    window.draw(projectiles_ennemi[j]->projectileSprite);
                    if (projectiles_ennemi[j]->hit(A)) {
                        A.Setpv(ennemies[i]->Getatk());
                        projectiles_ennemi.erase(projectiles_ennemi.begin() + j);
                    }
                }
            }

        }  

        A.isInWindow(window);
        A.update(upFlag, downFlag, leftFlag, rightFlag, window);

        window.draw(A.persoSprite);
        
        

       //HUD vie
        window.draw(heart);
        window.draw(rectangle3);

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
        rectangle2.setPosition(80,20);
        window.draw(rectangle2);

        //HUD attaque
        window.draw(sword);
        int atk=A.Getatk();
        string string_atk=to_string(atk);
        attaque.setString(string_atk);
        window.draw(attaque);

        

        //HUD vitesse de déplacement
        window.draw(speed);
        int spd=A.GetSpeed();
        string string_speed=to_string(spd);
        vitesseDeplacement.setString(string_speed);
        window.draw(vitesseDeplacement);

        //HUD vitesse de tir
        window.draw(arrows);
        int atkSpd=A.GetatkSpeed();
        string string_atkspeed=to_string(atkSpd);
        vitesseTir.setString(string_atkspeed);
        window.draw(vitesseTir);

        window.display();
        
    }
}