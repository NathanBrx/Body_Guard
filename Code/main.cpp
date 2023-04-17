#include "mainheader.hpp"

int main()
{

    RenderWindow window(VideoMode(/*VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height*/1920, 1080), "Body Guard"/*, Style::Fullscreen*/);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    Vector2u TextureSize, WindowSize;
    Sprite spriteMain, projectile1, projectile2, spriteEnnemy1, speed, sword, arrows, heart, porte_haut_sp, porte_droite_sp, porte_bas_sp, porte_gauche_sp, SwordSprite,HealthSprite,SpeedSprite,AtkDelaySprite;
    Texture porte_haut_tx, porte_droite_tx, porte_bas_tx, porte_gauche_tx;


    Sprite BarreVie, Vie;
    Texture BarreVie_tex, Vie_tex;
    Texture textureSpriteLeft, textureSpriteRight, textureSpriteUp, textureSpriteDown, textureSpriteDownInv, textureSpriteLeftInv, textureSpriteRightInv, textureSpriteUpInv;
    Texture textureProjectileRight, textureProjectileEnnemi;
    Texture textureEnnemy1, textureEnnemy1hit;
    Texture textureSpeed, textureSword, textureArrows, textureHeart, SwordPU,HealthPU,SpeedPU,AtkDelayPU;
    Text vitesseDeplacement, vitesseTir, attaque;
    Font policeStats;


    string texturesPath = "../Textures/"; // Linux
    //string texturesPath = "Textures\\"; // Windows

    //Musique   
    Music musique_accueil;
    if (!musique_accueil.openFromFile(texturesPath + "accueil.ogg")){
        return -1; // error
    }
    musique_accueil.setLoop(true);

    Music musique_jeu;
    if (!musique_jeu.openFromFile(texturesPath + "jeu.ogg")) {
        return -1; // error
    }
    musique_jeu.setLoop(true);

    Music musique_boss;
    if (!musique_boss.openFromFile(texturesPath + "boss.ogg")) {
        return -1; // error
    }
    musique_boss.setLoop(true);

    //Sons
    SoundBuffer tir_bf_1;
    if (!tir_bf_1.loadFromFile(texturesPath + "tir1.ogg")) {
        return -1;
    }
    Sound tir_1;
    tir_1.setBuffer(tir_bf_1);
    tir_1.setVolume(50.f);

    SoundBuffer tir_bf_2;
    if (!tir_bf_2.loadFromFile(texturesPath + "tir2.ogg")) {
        return -1;
    }
    Sound tir_2;
    tir_2.setBuffer(tir_bf_2);
    tir_2.setVolume(50.f);

    SoundBuffer tir_bf_3;
    if (!tir_bf_3.loadFromFile(texturesPath + "tir3.ogg")) {
        return -1;
    }
    Sound tir_3;
    tir_3.setBuffer(tir_bf_3);
    tir_3.setVolume(50.f);

    SoundBuffer tir_bf_4;
    if (!tir_bf_4.loadFromFile(texturesPath + "tir4.ogg")) {
        return -1;
    }
    Sound tir_4;
    tir_4.setBuffer(tir_bf_4);
    tir_4.setVolume(50.f);

    SoundBuffer tir_bf_5;
    if (!tir_bf_5.loadFromFile(texturesPath + "tir5.ogg")) {
        return -1;
    }
    Sound tir_5;
    tir_5.setBuffer(tir_bf_5);
    tir_5.setVolume(50.f);

    SoundBuffer tir_bf_6;
    if (!tir_bf_6.loadFromFile(texturesPath + "tir6.ogg")) {
        return -1;
    }
    Sound tir_6;
    tir_6.setBuffer(tir_bf_6);
    tir_6.setVolume(50.f);

    SoundBuffer select_bf;
    if (!select_bf.loadFromFile(texturesPath + "select.wav")) {
        return -1;
    }
    Sound select;
    select.setBuffer(select_bf);
    select.setVolume(100);

    // Joueur
    loadFile(textureSpriteLeft, texturesPath + "sprite_left.png");
    loadFile(textureSpriteRight, texturesPath + "sprite_right.png");
    loadFile(textureSpriteUp, texturesPath + "sprite_up.png");
    loadFile(textureSpriteDown, texturesPath + "sprite_down.png");
    loadFile(textureSpriteLeftInv, texturesPath + "sprite_left_inv.png");
    loadFile(textureSpriteRightInv, texturesPath + "sprite_right_inv.png");
    loadFile(textureSpriteUpInv, texturesPath + "sprite_up_inv.png");
    loadFile(textureSpriteDownInv, texturesPath + "sprite_down_inv.png");

    //Vie
    loadFile(BarreVie_tex,texturesPath + "Barre_vie.png");
    loadFile(Vie_tex, texturesPath + "Vie.png");

    //Powerups
    loadFile(SwordPU, texturesPath + "Atk_PU.png");
    loadFile(HealthPU, texturesPath + "Health_PU.png");
    loadFile(SpeedPU, texturesPath + "Speed_PU.png");
    loadFile(AtkDelayPU, texturesPath + "AtkDelay_PU.png");

    // Ennemies
    loadFile(textureEnnemy1, texturesPath + "ennemy1.png");
    loadFile(textureEnnemy1hit, texturesPath + "ennemy1hit.png");

    // Projectiles
    loadFile(textureProjectileEnnemi, texturesPath + "projectile_ennemi.png");
    loadFile(textureProjectileRight, texturesPath + "projectile_right.png");
    loadFile(textureSpeed, texturesPath + "speed.png");
    loadFile(textureSword, texturesPath + "sword.png");
    loadFile(textureArrows, texturesPath + "arrows.png");
    loadFile(textureHeart, texturesPath + "heart.png");

    //Police
    if (!policeStats.loadFromFile(texturesPath + "Nabla-Regular.ttf")) {
        cerr << "Failed to load font" << endl;
        exit(1);
    }

    //Portes
    loadFile(porte_haut_tx, texturesPath + "porte_haut.png");
    loadFile(porte_bas_tx, texturesPath + "porte_bas.png");
    loadFile(porte_droite_tx, texturesPath + "porte_droite.png");
    loadFile(porte_gauche_tx, texturesPath + "porte_gauche.png");

    // Taille de la fenetre
    WindowSize = window.getSize();

    // Calcul du ratio
    float ScaleX = (float)WindowSize.x / 1920;
    float ScaleY = (float)WindowSize.y / 1080;

    spriteMain.setTexture(textureSpriteRight);
    spriteMain.setScale(ScaleX, ScaleY);

    spriteEnnemy1.setTexture(textureEnnemy1);
    spriteEnnemy1.setScale(ScaleX, ScaleY);

    SwordSprite.setTexture(SwordPU);
    SwordSprite.setScale(ScaleX,ScaleY);
    SwordSprite.setPosition(WindowSize.x/2,WindowSize.y/2);

    projectile1.setTexture(textureProjectileRight);
    projectile1.setScale(ScaleX, ScaleY);

    projectile2.setTexture(textureProjectileEnnemi);
    projectile2.setScale(ScaleX,ScaleY);

    textureSpriteRight.setRepeated(false);
    textureSpriteRight.setSmooth(true);

    textureProjectileRight.setRepeated(false);
    textureProjectileRight.setSmooth(true);

    //Textures HUD

    BarreVie.setTexture(BarreVie_tex);
    BarreVie.setScale(ScaleX,ScaleY);
    BarreVie.setPosition(30* ScaleX,30* ScaleY);

    Vie.setTexture(Vie_tex);
    Vie.setScale(ScaleX, ScaleY);
    Vie.setPosition(41*ScaleX, 40*ScaleY);

    heart.setTexture(textureHeart);
    heart.setScale(Vector2f(0.08f, 0.08f));
    heart.setPosition(25, 10);

    speed.setTexture(textureSpeed);
    speed.setScale(Vector2f(0.1f, 0.1));
    speed.setPosition(30*ScaleX, 100*ScaleY);

    sword.setTexture(textureSword);
    sword.setScale(Vector2f(0.08f, 0.08f));
    sword.setPosition(30*ScaleX, 170*ScaleY);

    arrows.setTexture(textureArrows);
    arrows.setScale(Vector2f(0.08f, 0.08f));
    arrows.setPosition(30*ScaleX, 240*ScaleY);

    //-------------------

    vitesseDeplacement.setFont(policeStats);
    vitesseDeplacement.setCharacterSize(35);
    vitesseDeplacement.setFillColor(Color::White);
    vitesseDeplacement.setPosition(100*ScaleX, 110*ScaleY);

    vitesseTir.setFont(policeStats);
    vitesseTir.setCharacterSize(35);
    vitesseTir.setFillColor(Color::White);
    vitesseTir.setPosition(100*ScaleX, 240*ScaleY);

    attaque.setFont(policeStats);
    attaque.setCharacterSize(35);
    attaque.setFillColor(Color::White);
    attaque.setPosition(100*ScaleX, 170*ScaleY);

    //----------------------

    porte_haut_sp.setTexture(porte_haut_tx);
    porte_haut_sp.setScale(ScaleX, ScaleY);

    porte_bas_sp.setTexture(porte_bas_tx);
    porte_bas_sp.setScale(ScaleX, ScaleY);
    porte_bas_sp.setPosition(0, WindowSize.y - 182 * ScaleY);

    porte_droite_sp.setTexture(porte_droite_tx);
    porte_droite_sp.setScale(ScaleX, ScaleY);
    porte_droite_sp.setPosition(WindowSize.x - 65 * ScaleX, 0);

    porte_gauche_sp.setTexture(porte_gauche_tx);
    porte_gauche_sp.setScale(ScaleX, ScaleY);

    Background background(texturesPath+"Accueil.png", texturesPath + "Map1.jpg", texturesPath + "Game_over.jpg", texturesPath+"Credits.jpg", ScaleX, ScaleY);


    Perso A(window.getSize().x / 2., window.getSize().y / 2., 0., 100, 5, 10, 20, spriteMain);
    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    vector<Projectile*> projectiles;
    vector<Perso*> ennemies;
    vector<Projectile_ennemi*> projectiles_ennemi;
    vector<Clock> ennemy_shoot_time;

    /*
    RectangleShape rectangle3(Vector2f(600, 25));
    rectangle3.setFillColor(Color::Transparent);
    rectangle3.setOutlineThickness(5);
    rectangle3.setOutlineColor(Color(0, 0, 0));
    rectangle3.setPosition(80, 20);

    int couleurs[3];
    couleurs[0] = 100;
    couleurs[1] = 250;
    couleurs[2] = 50;
    */
    ennemies.push_back(new Perso(window.getSize().x / 3., window.getSize().y / 2., 0., 50, 5, 5, 5, spriteEnnemy1));
    ennemy_shoot_time.push_back(Clock());

    Color color1(225.6, 161.3, 120.8);
    Color color2(213.9, 146.1, 113.6);
    Font font1;
    Font font2;
    font1.loadFromFile(texturesPath + "Orbitron-ExtraBold.ttf");
    font2.loadFromFile(texturesPath + "Exo-SemiBoldItalic.ttf");
    Text text1("BODY GUARD", font1);
    Text text2("Jouer", font2);
    Text text3("Credits", font2);
    Text text4("Quitter", font2);
    Text text5("Recommencer", font2);
    Text text6("Retour", font2);

    text1.setCharacterSize(200);
    text1.setOrigin(text1.getGlobalBounds().width / 2., text1.getGlobalBounds().height / 2.);
    text1.setPosition(window.getSize().x / 2., window.getSize().y / 5.);
    text1.setFillColor(color1);
    text1.setOutlineThickness(5);
    text1.setOutlineColor(color2);

    text2.setCharacterSize(100);
    text2.setOrigin(text2.getGlobalBounds().width / 2., text2.getGlobalBounds().height / 2.);
    text2.setPosition(window.getSize().x / 2., window.getSize().y / 2.);
    text2.setFillColor(color2);
    text2.setOutlineThickness(3);
    text2.setOutlineColor(color1);

    text3.setCharacterSize(100);
    text3.setOrigin(text3.getGlobalBounds().width / 2., text3.getGlobalBounds().height / 2.);
    text3.setPosition(window.getSize().x / 2., 2 * (window.getSize().y / 3.));
    text3.setFillColor(color2);
    text3.setOutlineThickness(3);
    text3.setOutlineColor(color1);

    text4.setCharacterSize(100);
    text4.setOrigin(text4.getGlobalBounds().width / 2., text4.getGlobalBounds().height / 2.);
    text4.setPosition(window.getSize().x / 2., 2.55 * (window.getSize().y / 3.));
    text4.setFillColor(color2);
    text4.setOutlineThickness(3);
    text4.setOutlineColor(color1);

    text5.setCharacterSize(70);
    text5.setOrigin(text5.getGlobalBounds().width / 2., text5.getGlobalBounds().height / 2.);
    text5.setPosition(window.getSize().x / 2., 2.25 * (window.getSize().y / 3.));
    text5.setFillColor(Color::White);
    text5.setOutlineThickness(5);
    text5.setOutlineColor(Color::Black);

    text6.setCharacterSize(70);
    text6.setOrigin(text6.getGlobalBounds().width / 2., text6.getGlobalBounds().height / 2.);
    text6.setPosition(150,50);
    text6.setFillColor(Color::Black);
    text6.setOutlineThickness(3);
    text6.setOutlineColor(Color::White);

    Text* texts[3] = { &text2,&text3,&text4 };

    bool start = false;
    bool close = false;
    bool restart = false;
    bool credits = false;

    int mat[9][8] = { 0 }; // Initialisation de la carte
    generation(mat);

    bool shoot_ready = true;
    sf::Clock clock;
    sf::Clock clockiframes;
    bool invincible = false;

    Clock changeTexture;

    bool active_pu = false;

    musique_accueil.play();

    int cursorOnText = 3;

    while (window.isOpen())
    {
        while (!restart && !start && !close && !credits) {
            Event event1;
            while (window.pollEvent(event1)) {
                switch (event1.type) {
                case Event::Closed:
                    close = true;
                    break;
                case Event::KeyPressed:
                    if (event1.key.code == Keyboard::Escape) {
                        close = true;
                    }
                    break;
                case Event::MouseMoved:
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    for (int i = 0; i <= 2; i++) {
                        if (texts[i]->getGlobalBounds().contains(mousePosF)) {
                            texts[i]->setOutlineThickness(6);
                            if (cursorOnText!=i)
                            {
                                select.play();
                                cursorOnText = i;
                            }
                        }
                        else {
                            texts[i]->setOutlineThickness(3);
                            if (cursorOnText == i)
                            {
                                cursorOnText = 3;
                            }
                        }
                    }
                }break;
                case Event::MouseButtonPressed:
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    if (text2.getGlobalBounds().contains(mousePosF)) {
                        start = true;
                        musique_accueil.stop();
                        musique_jeu.play();
                    }
                    if (text3.getGlobalBounds().contains(mousePosF)){
                        credits = true;
                    }
                    if (text4.getGlobalBounds().contains(mousePosF)) {
                        close = true;
                    }
                }break;
                default: break;
                }
            }
            window.clear(Color::Black);
            window.draw(background.accueilSprite);
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
            window.draw(text4);
            window.display();
        }
        if (!restart && start && !close && !credits) {

            if (!shoot_ready) {
                sf::Time time1 = clock.getElapsedTime();
                if (time1 >= A.GetDelay()) {
                    shoot_ready = true;
                }
            }
            if (invincible) {
                sf::Time time2 = clockiframes.getElapsedTime();
                if (time2 >= sf::milliseconds(500)) {
                    invincible = false;
                    if (A.GetRotation() == 0.) { A.persoSprite.setTexture(textureSpriteRight); }
                    if (A.GetRotation() == 90.) { A.persoSprite.setTexture(textureSpriteUp); }
                    if (A.GetRotation() == 180.) { A.persoSprite.setTexture(textureSpriteLeft); }
                    if (A.GetRotation() == 270.) { A.persoSprite.setTexture(textureSpriteDown); }
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

                    case Keyboard::Z: upFlag = true; if (invincible) { A.persoSprite.setTexture(textureSpriteUpInv); }
                                    else { A.persoSprite.setTexture(textureSpriteUp); }; A.SetRotation(90.f); break;
                    case Keyboard::S: downFlag = true; if (invincible) { A.persoSprite.setTexture(textureSpriteDownInv); }
                                    else { A.persoSprite.setTexture(textureSpriteDown); }; A.SetRotation(270.f); break;
                    case Keyboard::Q: leftFlag = true; if (invincible) { A.persoSprite.setTexture(textureSpriteLeftInv); }
                                    else { A.persoSprite.setTexture(textureSpriteLeft); }; A.SetRotation(180.f); break;
                    case Keyboard::D: rightFlag = true; if (invincible) { A.persoSprite.setTexture(textureSpriteRightInv); }
                                    else { A.persoSprite.setTexture(textureSpriteRight); }; A.SetRotation(0.f); break;
                    case Keyboard::Up: if (shoot_ready) { tirer(projectiles, A, projectile1, 270.f,tir_1,tir_2,tir_3,tir_4,tir_5,tir_6); clock.restart(); shoot_ready = false; break; }
                    case Keyboard::Down: if (shoot_ready) { tirer(projectiles, A, projectile1, 90.f, tir_1, tir_2, tir_3, tir_4, tir_5, tir_6); clock.restart(); shoot_ready = false; break; }
                    case Keyboard::Left: if (shoot_ready) { tirer(projectiles, A, projectile1, 180.f, tir_1, tir_2, tir_3, tir_4, tir_5, tir_6); clock.restart(); shoot_ready = false; break; }
                    case Keyboard::Right: if (shoot_ready) { tirer(projectiles, A, projectile1, 0.f, tir_1, tir_2, tir_3, tir_4, tir_5, tir_6); clock.restart(); shoot_ready = false; break; }
                    default: break;
                    }
                }

                // If a key is released
                if (event.type == Event::KeyReleased) {
                    switch (event.key.code) {
                        // up, down, left and right keys
                    case Keyboard::Z: upFlag = false; break;
                    case Keyboard::S: downFlag = false; break;
                    case Keyboard::Q: leftFlag = false; break;
                    case Keyboard::D: rightFlag = false; break;
                    default: break;
                    }
                }

            }

            for (const auto& point : background.borduresPoints) {

                if (A.persoSprite.getGlobalBounds().contains(point)) {
                    if (upFlag) {
                        upFlag = false;
                        A.SetY(A.GetY() + 5 * ScaleY);
                    }
                    if (downFlag) {
                        downFlag = false;
                        A.SetY(A.GetY() - 5 * ScaleY);
                    }
                    if (leftFlag) {
                        leftFlag = false;
                        A.SetX(A.GetX() + 5 * ScaleX);
                    }
                    if (rightFlag) {
                        rightFlag = false;
                        A.SetX(A.GetX() - 5 * ScaleX);
                    }
                }
                while (A.persoSprite.getGlobalBounds().contains(point))
                {
                    if (A.GetY() > 540 * ScaleY) {
                        A.SetY(A.GetY() - 5 * ScaleY);
                    }
                    else {
                        A.SetY(A.GetY() + 5 * ScaleY);
                    }
                    if (A.GetX() > 960 * ScaleX) {
                        A.SetX(A.GetX() - 5 * ScaleX);
                    }
                    else {
                        A.SetX(A.GetX() + 5 * ScaleX);
                    }
                }
            }
            for (size_t i = 0; i < background.portes.size(); i += 1) {
                if (A.persoSprite.getGlobalBounds().intersects(sf::FloatRect(background.portes[i].left, background.portes[i].top, background.portes[i].width, background.portes[i].height)) && background.portesActives) {
                    background.ChangeMap(i, A, window, porte_haut_sp, porte_bas_sp, porte_gauche_sp, porte_droite_sp);
                }
            }

            // Clear the window and apply background
            window.clear(Color::White);

            window.draw(background.backgroundSprite);

            background.BoucheTrou(window, mat, porte_haut_sp, porte_bas_sp, porte_gauche_sp, porte_droite_sp);

            for (size_t j = 0; j < projectiles.size(); j++) {
                if (projectiles[j]->isAlive(*projectiles[j], window)) {

                    bool touchBorder = false;

                    for (const auto& point : background.borduresPoints) {
                        touchBorder = touchBorder || projectiles[j]->projectileSprite.getGlobalBounds().contains(point);
                    }

                    projectiles[j]->update(*projectiles[j], A, window, projectiles[j]->GetDirection());
                    window.draw(projectiles[j]->projectileSprite);
                    if (touchBorder) {
                        projectiles.erase(projectiles.begin() + j);
                    }
                }
            }
            for (size_t i = 0; i < ennemies.size(); i++) {
                if (A.persoSprite.getGlobalBounds().intersects(ennemies[i]->persoSprite.getGlobalBounds()) && !invincible) {
                    A.Setpvdamage(ennemies[i]->Getatk());
                    invincible = true;
                    clockiframes.restart();
                    if (A.GetRotation() == 0.) { A.persoSprite.setTexture(textureSpriteRightInv); }
                    if (A.GetRotation() == 90.) { A.persoSprite.setTexture(textureSpriteUpInv); }
                    if (A.GetRotation() == 180.) { A.persoSprite.setTexture(textureSpriteLeftInv); }
                    if (A.GetRotation() == 270.) { A.persoSprite.setTexture(textureSpriteDownInv); }

                }
                for (size_t j = 0; j < projectiles.size(); j++) {
                    if (projectiles[j]->isAlive(*projectiles[j], window)) {
                        if (ennemies[i]->checkAlive() && projectiles[j]->hit(*ennemies[i])) {
                            ennemies[i]->persoSprite.setTexture(textureEnnemy1hit);
                            projectiles.erase(projectiles.begin() + j);
                            ennemies[i]->Setpvdamage(A.Getatk());
                        }
                    }
                }
                if (changeTexture.getElapsedTime().asSeconds()>=0.2f){
                    ennemies[i]->persoSprite.setTexture(textureEnnemy1);
                    changeTexture.restart();
                }
                window.draw(ennemies[i]->persoSprite);
                if (ennemies[i]->checkAlive()) {
                    Time time_shoot_ennemy = (ennemy_shoot_time[i]).getElapsedTime();
                    if (time_shoot_ennemy >= ennemies[i]->GetDelay()) {
                        projectiles_ennemi.push_back((new Projectile_ennemi(ennemies[i]->GetX(), ennemies[i]->GetY(), A.GetX(), A.GetY(), ennemies[i]->GetatkSpeed(), ennemies[i]->Getatk(), projectile2)));
                        ennemy_shoot_time[i].restart();

                        int sound;
                        sound = rand() % 6;
                        switch (sound)
                        {
                        case(0):
                            tir_1.play();
                            break;
                        case(1):
                            tir_2.play();
                            break;
                        case(2):
                            tir_3.play();
                            break;
                        case(3):
                            tir_4.play();
                            break;
                        case(4):
                            tir_5.play();
                            break;
                        case(5):
                            tir_6.play();
                            break;
                        default:
                            break;
                        }
                    }
                }

                if (!ennemies[i]->checkAlive()) {
                    ennemies.erase(ennemies.begin() + i);
                    if (ennemies.size() == 0) active_pu = true;
                }

            }

            for (size_t j = 0; j < projectiles_ennemi.size(); j++) {
                if (projectiles_ennemi[j]->isAlive(window)) {
                    bool touchBorder = false;
                    for (const auto& point : background.borduresPoints) {
                        touchBorder = touchBorder || projectiles_ennemi[j]->projectileSprite.getGlobalBounds().contains(point);
                    }   

                    projectiles_ennemi[j]->update(window);
                    window.draw(projectiles_ennemi[j]->projectileSprite);
                    if (touchBorder) {
                        projectiles_ennemi.erase(projectiles_ennemi.begin() + j);
                    }else if (projectiles_ennemi[j]->hit(A)) {
                        A.Setpvdamage(projectiles_ennemi[j]->GetDamage());
                        projectiles_ennemi.erase(projectiles_ennemi.begin() + j);
                    }
                }
            } 

            if (!A.checkAlive()) {
                restart = true;
            }
            A.isInWindow(window);
            A.update(upFlag, downFlag, leftFlag, rightFlag, window);

            window.draw(A.persoSprite);
            
            //Powerups

            if (active_pu){
                window.draw(SwordSprite);
                if (A.persoSprite.getGlobalBounds().intersects(SwordSprite.getGlobalBounds())){
                    active_pu = false;
                    background.portesActives = true;
                    A.Setatk(A.Getatk() + 1);
                }
            }

            //HUD vie
            //window.draw(heart);
            Vie.setScale((A.Getpv()*ScaleX/A.Getpvmax()), ScaleY);
            window.draw(Vie);
            window.draw(BarreVie);

            //window.draw(rectangle3);
            /*
            //HUD
            int pvs = A.Getpv();
            int pvs_max = A.Getpvmax();

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
                else {
                    couleurs[0] = 100;
                    couleurs[1] = 250;
                    couleurs[2] = 50;
                }
            }
            */
            /*
            RectangleShape rectangle2(Vector2f((pvs * 600) / (pvs_max), 25));
            rectangle2.setFillColor(Color(couleurs[0], couleurs[1], couleurs[2]));
            rectangle2.setPosition(80, 20);*/

            //window.draw(rectangle2);
            
            //HUD attaque
            window.draw(sword);
            int atk = A.Getatk();
            string string_atk = to_string(atk);
            attaque.setString(string_atk);
            window.draw(attaque);

            //HUD vitesse de déplacement
            window.draw(speed);
            int spd = A.GetSpeed();
            string string_speed = to_string(spd);
            vitesseDeplacement.setString(string_speed);
            window.draw(vitesseDeplacement);

            //HUD vitesse de tir
            window.draw(arrows);
            int atkSpd = A.GetatkSpeed();
            string string_atkspeed = to_string(atkSpd);
            vitesseTir.setString(string_atkspeed);
            window.draw(vitesseTir);
            /*
            //Bordures
            RectangleShape rectangle;
            std::vector<sf::RectangleShape> bords;
            for (size_t i = 0; i < background.borduresPoints.size() - 1; i += 1) {
                Vector2f bottomLeft = background.borduresPoints[i];
                Vector2f bottomRight = background.borduresPoints[i + 1];
                // Calculer la longueur et l'angle du rectangle
                float length = sqrt(pow(bottomRight.x - bottomLeft.x, 2) + pow(bottomRight.y - bottomLeft.y, 2));
                float angle = atan2(bottomRight.y - bottomLeft.y, bottomRight.x - bottomLeft.x);

                // Cr�er le rectangle

                rectangle.setSize(Vector2f(length, 1.f));
                rectangle.setRotation(angle * 180.f / 3.14159f);
                rectangle.setOutlineThickness(2);
                rectangle.setFillColor(couleur);
                rectangle.setOutlineColor(couleur);

                // Positionner le rectangle en utilisant le coin inf�rieur gauche
                rectangle.setPosition(bottomLeft.x, bottomLeft.y - rectangle.getSize().y);

                double distance = sqrt(pow(bottomRight.x - bottomLeft.x, 2) + pow(bottomRight.y - bottomLeft.y, 2));
                if (distance < 50) {
                    bords.push_back(rectangle);
                }

            }
            for (const auto& shape : bords) {
                window.draw(shape);
            }*/

            window.display();
        }
        else if (restart && !close && !credits) {

            text4.setCharacterSize(50);
            text4.setOrigin(text4.getGlobalBounds().width / 2., text4.getGlobalBounds().height / 2.);
            text4.setPosition(window.getSize().x / 2., 2.75 * (window.getSize().y / 3.));
            text4.setFillColor(Color::Black);
            text4.setOutlineThickness(5);
            text4.setOutlineColor(Color::White);

            while (restart) {
                Event event2;
                while (window.pollEvent(event2)) {
                    switch (event2.type) {
                    case Event::Closed:
                        close = true;
                        restart = false;
                        break;
                    case Event::KeyPressed:
                        if (event2.key.code == Keyboard::Escape) {
                            close = true;
                            restart = false;
                        }
                        break;
                    case Event::MouseMoved:
                    {
                        Vector2i mousePos = Mouse::getPosition(window);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                        if (text5.getGlobalBounds().contains(mousePosF)) {
                            text5.setOutlineThickness(8);
                        }
                        else {
                            text5.setOutlineThickness(5);
                        }
                        if (text4.getGlobalBounds().contains(mousePosF)) {
                            text4.setOutlineThickness(8);
                        }
                        else {
                            text4.setOutlineThickness(5);
                        }
                    }break;
                    case Event::MouseButtonPressed:
                    {
                        Vector2i mousePos = Mouse::getPosition(window);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                        if (text5.getGlobalBounds().contains(mousePosF)) {
                            A.Reset();
                            restart = false;
                        }
                        if (text4.getGlobalBounds().contains(mousePosF)) {
                            restart = false;
                            close = true;
                        }
                    }break;
                    default: break;
                    }
                }
                window.clear(Color::Black);
                window.draw(background.finSprite);
                window.draw(text4);
                window.draw(text5);

                //***** Affichage des bordures et des portes *****//
                //Portes
                /*
                std::vector<sf::RectangleShape> rectangles;
                for (const auto& rect : background.portes) {
                    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
                    shape.setPosition(sf::Vector2f(rect.left, rect.top));
                    shape.setFillColor(sf::Color::Green);
                    rectangles.push_back(shape);
                }
                for (const auto& shape : rectangles) {
                    window.draw(shape);
                }
                */

                window.display();
            }
        }
        else if (!start && !restart && !close && credits){
            background.creditsSprite.setPosition(0, WindowSize.y);
            while (credits && background.creditsSprite.getPosition().y > 0){
                Event event3;
                while (window.pollEvent(event3)) {
                    switch (event3.type) {
                    case Event::Closed:
                        close = true;
                        credits = false;
                        break;
                    case Event::KeyPressed:
                        if (event3.key.code == Keyboard::Escape) {
                            close = true;
                            credits = false;
                        }
                        break;
                    case Event::MouseMoved:
                    {
                        Vector2i mousePos = Mouse::getPosition(window);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                        if (text6.getGlobalBounds().contains(mousePosF)) {
                            text6.setOutlineThickness(5);
                        }
                        else {
                            text6.setOutlineThickness(3);
                        }
                    }break;
                    case Event::MouseButtonPressed:
                    {
                        Vector2i mousePos = Mouse::getPosition(window);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                        if (text6.getGlobalBounds().contains(mousePosF)) {
                            credits = false;
                        }
                    }break;
                    default: break;
                    }
                }
                background.creditsSprite.move(0, -1);
                window.clear(Color::Black);
                window.draw(background.creditsSprite);
                window.draw(text6);
                window.display();
            }
        }
        else {
            window.close();
        }
    }
    return 0;
}
