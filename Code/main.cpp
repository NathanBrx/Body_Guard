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
    Texture backgroundTexture, textureEnd;
    Texture textureSpriteLeft, textureSpriteRight, textureSpriteUp, textureSpriteDown, textureSpriteDownInv, textureSpriteLeftInv, textureSpriteRightInv, textureSpriteUpInv;
    Texture textureProjectileLeft, textureProjectileRight, textureProjectileUp, textureProjectileDown;
    Texture textureEnnemy1, textureEnnemy1hit;
    Text vitesseDeplacement, vitesseTir, attaque;
    Font policeStats;

    string texturesPath = "../Textures/"; // Linux
    //string texturesPath = "Textures\\"; // Windows

    // Arri�re-plan
    loadFile(backgroundTexture, texturesPath + "Map1.jpg");
    loadFile(textureEnd, texturesPath + "Game_over.jpg");

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
    loadFile(textureProjectileUp, texturesPath + "projectile_up.png");
    loadFile(textureProjectileDown, texturesPath + "projectile_down.png");
    loadFile(textureProjectileLeft, texturesPath + "projectile_left.png");
    loadFile(textureProjectileRight, texturesPath + "projectile_right.png");
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

    spriteMain.setTexture(textureSpriteRight);
    spriteMain.setScale(ScaleX, ScaleY);

    spriteEnnemy1.setTexture(textureEnnemy1);
    spriteEnnemy1.setScale(ScaleX, ScaleY);

    projectile1.setTexture(textureProjectileRight);
    projectile1.setScale(ScaleX, ScaleY);

    textureSpriteRight.setRepeated(false);
    textureSpriteRight.setSmooth(true);

    textureProjectileRight.setRepeated(false);
    textureProjectileRight.setSmooth(true);

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

    //-------------------

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

    //----------------------

    Background background(backgroundSprite, texturesPath + "Accueil.jpeg", { {0, 390}, {78, 415}, {276, 279}, {400, 234},{730, 195},{815, 160}, {882, 66}, {890, 0}, {1070, 0}, {1280, 220},{1720, 148},{1840,400},{1920, 480},{1920, 660},{1136, 1080},{886, 1080},{0, 678} });
    background.SetBackground();
    background.SetTexture(ScaleX,ScaleY);

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

    Color color1(225.6,161.3,120.8);
    Color color2(213.9,146.1,113.6);
    Font font1;
    Font font2;
    font1.loadFromFile("../Textures/Orbitron-ExtraBold.ttf");
    font2.loadFromFile("../Textures/Exo-SemiBoldItalic.ttf");
    Text text1("BODY GUARD",font1);
    Text text2("Jouer",font2);
    Text text3("Credits",font2);
    Text text4("Quitter",font2);
    Text text5("Recommencer",font2);

    text1.setCharacterSize(200);
    text1.setOrigin(text1.getGlobalBounds().width/2.,text1.getGlobalBounds().height/2.);
    text1.setPosition(window.getSize().x / 2., window.getSize().y / 5.);
    text1.setFillColor(color1);
    text1.setOutlineThickness(5);
    text1.setOutlineColor(color2);

    text2.setCharacterSize(100);
    text2.setOrigin(text2.getGlobalBounds().width/2.,text2.getGlobalBounds().height/2.);
    text2.setPosition(window.getSize().x / 2., window.getSize().y / 2.);
    text2.setFillColor(color2);
    text2.setOutlineThickness(3);
    text2.setOutlineColor(color1);

    text3.setCharacterSize(100);
    text3.setOrigin(text3.getGlobalBounds().width/2.,text3.getGlobalBounds().height/2.);
    text3.setPosition(window.getSize().x / 2., 2*(window.getSize().y / 3.));
    text3.setFillColor(color2);
    text3.setOutlineThickness(3);
    text3.setOutlineColor(color1);

    text4.setCharacterSize(100);
    text4.setOrigin(text4.getGlobalBounds().width/2.,text4.getGlobalBounds().height/2.);
    text4.setPosition(window.getSize().x / 2., 2.55*(window.getSize().y / 3.));
    text4.setFillColor(color2);
    text4.setOutlineThickness(3);
    text4.setOutlineColor(color1);

    text5.setCharacterSize(70);
    text5.setOrigin(text5.getGlobalBounds().width/2.,text5.getGlobalBounds().height/2.);
    text5.setPosition(window.getSize().x / 2., 2.25*(window.getSize().y / 3.));
    text5.setFillColor(Color::White);
    text5.setOutlineThickness(5);
    text5.setOutlineColor(Color::Black);

    Text* texts[3] = {&text2,&text3,&text4};

    bool start = false;
    bool close = false;
    bool restart = false;

    int mat[9][8] = { 0 }; // Initialisation de la carte � 0
    generation(mat);

    bool shoot_ready = true;
    sf::Clock clock;
    sf::Clock clockiframes;
    bool invincible = false;

    while (window.isOpen())
    {
        while (!restart && !start && !close){

            Event event1;
            while(window.pollEvent(event1)){
                switch (event1.type){
                    case Event::Closed:
                        close = true;
                        break;
                    case Event::KeyPressed:
                        if (event1.key.code == Keyboard::Escape){
                            close = true;
                        }
                        break;
                    case Event::MouseMoved:
                        {
                        Vector2i mousePos = Mouse::getPosition(window);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                        for (int i = 0;i <= 2;i++){
                            if (texts[i]->getGlobalBounds().contains(mousePosF)){
                                texts[i]->setOutlineThickness(6);
                            }else{
                                texts[i]->setOutlineThickness(3);
                            }
                        }
                        }break;
                    case Event::MouseButtonPressed:
                        {
                        Vector2i mousePos = Mouse::getPosition(window);
                        Vector2f mousePosF( static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                        if (text2.getGlobalBounds().contains(mousePosF)){
                            start = true;
                        }
                        if (text4.getGlobalBounds().contains(mousePosF)){
                            close = true;
                        }
                        }break;
                    default: break;
                }
            }
            window.clear(Color::Black);
            window.draw(background.backgroundSprite);
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
            window.draw(text4);
            window.display();
        }
        if (!restart && start && !close){

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
                if (event.type == Event::Closed) close = true;

                // If a key is pressed
                if (event.type == Event::KeyPressed) {
                    switch (event.key.code) {
                        // If escape is pressed, close the application
                    case  Keyboard::Escape: close = true; break;

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

            background.backgroundTexture = backgroundTexture;
            background.SetTexture(ScaleX,ScaleY);
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
                    A.Setpvdamage(ennemies[i]->Getatk());
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
                            ennemies[i]->Setpvdamage(A.Getatk());
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

            if (!A.checkAlive()){
                restart = true;
            }
            A.isInWindow(window);
            A.update(upFlag, downFlag, leftFlag, rightFlag, window);

            window.draw(A.persoSprite);

            //HUD vie
            window.draw(heart);
            window.draw(rectangle3);

            //HUD
            int pvs=A.Getpv();
            int pvs_max=A.Getpvmax();

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
                else{
                    couleurs[0] = 100;
                    couleurs[1] = 250;
                    couleurs[2] = 50;
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

        }else if (restart && !close){
            
            background.backgroundTexture = textureEnd;
            background.SetTexture(ScaleX,ScaleY);
            text4.setCharacterSize(50);
            text4.setOrigin(text4.getGlobalBounds().width/2.,text4.getGlobalBounds().height/2.);
            text4.setPosition(window.getSize().x / 2., 2.75*(window.getSize().y / 3.));
            text4.setFillColor(Color::Black);
            text4.setOutlineThickness(5);
            text4.setOutlineColor(Color::White);

            while (restart){
                Event event2;
                while(window.pollEvent(event2)){
                    switch (event2.type){
                        case Event::Closed:
                            close = true;
                            restart = false;
                            break;
                        case Event::KeyPressed:
                            if (event2.key.code == Keyboard::Escape){
                                close = true;
                                restart = false;
                            }
                            break;
                        case Event::MouseMoved:
                            {
                            Vector2i mousePos = Mouse::getPosition(window);
                            Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                            if (text5.getGlobalBounds().contains(mousePosF)){
                                text5.setOutlineThickness(8);
                            }else{
                                text5.setOutlineThickness(5);
                            }
                            if (text4.getGlobalBounds().contains(mousePosF)){
                                text4.setOutlineThickness(8);
                            }else{
                                text4.setOutlineThickness(5);
                            }
                            }break;
                        case Event::MouseButtonPressed:
                            {
                            Vector2i mousePos = Mouse::getPosition(window);
                            Vector2f mousePosF( static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                            if (text5.getGlobalBounds().contains(mousePosF)){
                                A.Reset();
                                restart = false;
                            }
                            if (text4.getGlobalBounds().contains(mousePosF)){
                                restart = false;
                                close = true;
                            }
                            }break;
                        default: break;
                    }
                }
                window.clear(Color::Black);
                window.draw(background.backgroundSprite);
                window.draw(text4);
                window.draw(text5);
                window.display();
            }
        }else{
            window.close();
        }
    }
    return 0;
}