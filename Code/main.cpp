#include "mainheader.hpp"

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height/*1920, 1080*/), "Body Guard", Style::Fullscreen);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    start:
    Vector2u TextureSize, WindowSize;

    Sprite spriteMain, projectile1, projectile2, spriteEnnemy1, spriteEnnemy2, spriteEnnemy3, spriteBoss, speed, sword, arrows, heart, porte_haut_sp, porte_droite_sp, porte_bas_sp, porte_gauche_sp, PowerUpSprite;
    Texture porte_haut_tx, porte_droite_tx, porte_bas_tx, porte_gauche_tx;
    Sprite spriteADN;
    Texture textureADN;


    Sprite BarreVie, Vie;
    Texture BarreVie_tex, Vie_tex;
    Texture textureSpriteLeft, textureSpriteRight, textureSpriteUp, textureSpriteDown, textureSpriteDownInv, textureSpriteLeftInv, textureSpriteRightInv, textureSpriteUpInv;
    Texture textureProjectileRight, textureProjectileEnnemi;

    Texture textureEnnemy1, textureEnnemy1hit, textureEnnemy2, textureEnnemy2hit, textureEnnemy3, textureEnnemy3hit, textureBoss;
    Texture textureSpeed, textureSword, textureArrows, textureHeart, SwordPU,HealthPU,SpeedPU,AtkDelayPU;
    Texture finjeu;
    Sprite spritefin;

    Text vitesseDeplacement, vitesseTir, attaque;
    Font policeStats;
    
    Texture PersoTex_h_b, PersoTex_h_h, PersoTex_h_g, PersoTex_h_d;
    Texture PersoTex_b_0, PersoTex_b_1, PersoTex_b_2, PersoTex_b_3, PersoTex_b_4, PersoTex_b_5, PersoTex_b_6, PersoTex_b_7, PersoTex_b_8;
    Texture PersoTex_b_0_h, PersoTex_b_1_h, PersoTex_b_2_h, PersoTex_b_3_h, PersoTex_b_4_h, PersoTex_b_5_h, PersoTex_b_6_h, PersoTex_b_7_h, PersoTex_b_8_h;
    Texture PersoTex_b_1_d, PersoTex_b_2_d, PersoTex_b_3_d, PersoTex_b_4_d, PersoTex_b_5_d, PersoTex_b_6_d, PersoTex_b_7_d, PersoTex_b_8_d, PersoTex_b_9_d;
    Texture PersoTex_b_1_g, PersoTex_b_2_g, PersoTex_b_3_g, PersoTex_b_4_g, PersoTex_b_5_g, PersoTex_b_6_g, PersoTex_b_7_g, PersoTex_b_8_g, PersoTex_b_9_g;

    Sprite PersoSprite_h, PersoSprite_b;

    string texturesPath = "../Textures/"; // Linux
    //string texturesPath = "..\\Textures\\"; // Windows

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

    SoundBuffer power_up_bf;
    if (!power_up_bf.loadFromFile(texturesPath + "power_up.wav")) {
        return -1;
    }
    Sound power_up;
    power_up.setBuffer(power_up_bf);

    // Joueur

    loadFile(PersoTex_h_b,texturesPath + "Perso_h_b.png");
    loadFile(PersoTex_h_h, texturesPath + "Perso_h_h.png");
    loadFile(PersoTex_h_d, texturesPath + "Perso_h_d.png");
    loadFile(PersoTex_h_g, texturesPath + "Perso_h_g.png");

    loadFile(PersoTex_b_0, texturesPath + "Perso_b_0.png");
    loadFile(PersoTex_b_1, texturesPath + "Perso_b_1.png");
    loadFile(PersoTex_b_2, texturesPath + "Perso_b_2.png");
    loadFile(PersoTex_b_3, texturesPath + "Perso_b_3.png");
    loadFile(PersoTex_b_4, texturesPath + "Perso_b_4.png");
    loadFile(PersoTex_b_5, texturesPath + "Perso_b_5.png");
    loadFile(PersoTex_b_6, texturesPath + "Perso_b_6.png");
    loadFile(PersoTex_b_7, texturesPath + "Perso_b_7.png");
    loadFile(PersoTex_b_8, texturesPath + "Perso_b_8.png");

    loadFile(PersoTex_b_0_h, texturesPath + "Perso_b_0_h.png");
    loadFile(PersoTex_b_1_h, texturesPath + "Perso_b_1_h.png");
    loadFile(PersoTex_b_2_h, texturesPath + "Perso_b_2_h.png");
    loadFile(PersoTex_b_3_h, texturesPath + "Perso_b_3_h.png");
    loadFile(PersoTex_b_4_h, texturesPath + "Perso_b_4_h.png");
    loadFile(PersoTex_b_5_h, texturesPath + "Perso_b_5_h.png");
    loadFile(PersoTex_b_6_h, texturesPath + "Perso_b_6_h.png");
    loadFile(PersoTex_b_7_h, texturesPath + "Perso_b_7_h.png");
    loadFile(PersoTex_b_8_h, texturesPath + "Perso_b_8_h.png");

    loadFile(PersoTex_b_1_d, texturesPath + "Perso_b_1_d.png");
    loadFile(PersoTex_b_2_d, texturesPath + "Perso_b_2_d.png");
    loadFile(PersoTex_b_3_d, texturesPath + "Perso_b_3_d.png");
    loadFile(PersoTex_b_4_d, texturesPath + "Perso_b_4_d.png");
    loadFile(PersoTex_b_5_d, texturesPath + "Perso_b_5_d.png");
    loadFile(PersoTex_b_6_d, texturesPath + "Perso_b_6_d.png");
    loadFile(PersoTex_b_7_d, texturesPath + "Perso_b_7_d.png");
    loadFile(PersoTex_b_8_d, texturesPath + "Perso_b_8_d.png");
    loadFile(PersoTex_b_9_d, texturesPath + "Perso_b_9_d.png");

    loadFile(PersoTex_b_1_g, texturesPath + "Perso_b_1_g.png");
    loadFile(PersoTex_b_2_g, texturesPath + "Perso_b_2_g.png");
    loadFile(PersoTex_b_3_g, texturesPath + "Perso_b_3_g.png");
    loadFile(PersoTex_b_4_g, texturesPath + "Perso_b_4_g.png");
    loadFile(PersoTex_b_5_g, texturesPath + "Perso_b_5_g.png");
    loadFile(PersoTex_b_6_g, texturesPath + "Perso_b_6_g.png");
    loadFile(PersoTex_b_7_g, texturesPath + "Perso_b_7_g.png");
    loadFile(PersoTex_b_8_g, texturesPath + "Perso_b_8_g.png");
    loadFile(PersoTex_b_9_g, texturesPath + "Perso_b_9_g.png");

    //Vie
    loadFile(BarreVie_tex,texturesPath + "Barre_vie.png");
    loadFile(Vie_tex, texturesPath + "Vie.png");
    loadFile(textureADN, texturesPath + "ADN.png");

    //Powerups
    loadFile(SwordPU, texturesPath + "Atk_PU.png");
    loadFile(HealthPU, texturesPath + "Health_PU.png");
    loadFile(SpeedPU, texturesPath + "Speed_PU.png");
    loadFile(AtkDelayPU, texturesPath + "AtkDelay_PU.png");

    // Ennemies
    loadFile(textureEnnemy1, texturesPath + "ennemy1.png");
    loadFile(textureEnnemy1hit, texturesPath + "ennemy1hit.png");

    loadFile(textureEnnemy2, texturesPath + "ennemy2.png");
    loadFile(textureEnnemy2hit, texturesPath + "ennemy2hit.png");
    loadFile(textureEnnemy3, texturesPath + "ennemy3.png");
    loadFile(textureEnnemy3hit, texturesPath + "ennemy3hit.png");
    loadFile(textureBoss, texturesPath + "Boss.png");

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

    //écran de fin
    loadFile(finjeu, texturesPath + "image_fin.png");


    // Taille de la fenetre
    WindowSize = window.getSize();

    // Calcul du ratio
    float ScaleX = (float)WindowSize.x / 1920;
    float ScaleY = (float)WindowSize.y / 1080;

    spritefin.setTexture(finjeu);
    spritefin.setScale(1920,1080);

    PersoSprite_h.setTexture(PersoTex_h_d);
    PersoSprite_h.setScale(ScaleX*0.1, ScaleY * 0.1);

    PersoSprite_b.setTexture(PersoTex_b_0);
    PersoSprite_b.setScale(ScaleX * 0.1, ScaleY * 0.1);

    float ScaleEnnemies = 0.2;

    spriteEnnemy1.setTexture(textureEnnemy1);
    spriteEnnemy1.setScale(ScaleX* ScaleEnnemies, ScaleY * ScaleEnnemies);

    spriteEnnemy2.setTexture(textureEnnemy2);
    spriteEnnemy2.setScale(ScaleX * 0.1, ScaleY * 0.1);

    spriteEnnemy3.setTexture(textureEnnemy3);
    spriteEnnemy3.setScale(ScaleX * ScaleEnnemies, ScaleY * ScaleEnnemies);

    spriteBoss.setTexture(textureBoss);
    spriteBoss.setScale(ScaleX/3, ScaleY/3);

    PowerUpSprite.setScale(ScaleX,ScaleY);
    PowerUpSprite.setPosition(WindowSize.x/2,WindowSize.y/2);

    projectile1.setTexture(textureProjectileRight);
    projectile1.setScale(ScaleX, ScaleY);

    projectile2.setTexture(textureProjectileEnnemi);
    projectile2.setScale(ScaleX,ScaleY);

    spriteADN.setTexture(textureADN);
    spriteADN.setScale(ScaleX*0.05,ScaleY*0.05);

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

    Background background(texturesPath+"Accueil.png", texturesPath + "Map1.jpg", texturesPath + "Game_over.jpg", texturesPath + "Credits.jpg", ScaleX, ScaleY);


    Perso A(window.getSize().x / 2., window.getSize().y / 2., 0., 100, 5, 100, 20, PersoSprite_h,PersoSprite_b);

    A.SetDelay(sf::milliseconds(500));

    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    vector<Projectile*> projectiles;
    vector<Perso*> ennemies;
    vector<Projectile_ennemi*> projectiles_ennemi;
    vector<Clock> ennemy_shoot_time;
    vector<Clock> changeTexture;

    ennemies.push_back(new Perso(window.getSize().x / 3., window.getSize().y / 2., 0., 50, 5, 5, 5, spriteEnnemy1,PersoSprite_b));
    
    ennemy_shoot_time.push_back(Clock());
    changeTexture.push_back(Clock());

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
    text6.setPosition(150, 50);
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
    bool active_rando = true;
    int rando;

    cout << "Generation de la carte" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 8; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    bool shoot_ready = true;
    sf::Clock clock;
    sf::Clock clockiframes;
    bool invincible = false;


    bool active_pu = false;

    musique_accueil.play();

    int cursorOnText = 3;

    vector<Vector2f> ADNs= {};
    vector<FloatRect> ADNs_boundingbox= {};

    int numTexSpriteAnim = 0;
    int numTexSpriteAnim_h = 0;
    int numTexSpriteAnim_d = 0;
    int numTexSpriteAnim_g = 0;

    bool isBackSide = false;

    int waitForNextFrame = 0;
    const int timeToWait = 3;
    int waitForNextRotation = 0;

    int pvBonusAnim = 0;

    vector<int> ennemisQuiBougent = {};

    while (window.isOpen())
    {
        srand(time(0));
        if(active_rando){rando = rand()%4;}
        
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
                    if (text3.getGlobalBounds().contains(mousePosF)) {
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
                    A.persoSprite.setColor(Color(255, 255, 255));
                    A.persoSpriteBas.setColor(Color(255, 255, 255));
                }
                else {
                    A.persoSprite.setColor(Color(255, 200, 200));
                    A.persoSpriteBas.setColor(Color(255, 200, 200));
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

                    case Keyboard::Z: upFlag = true; A.SetRotation(90.f); break;
                    case Keyboard::S: downFlag = true; A.SetRotation(270.f); break;
                    case Keyboard::Q: leftFlag = true; A.SetRotation(180.f); break;
                    case Keyboard::D: rightFlag = true; A.SetRotation(0.f); break;
                    case Keyboard::Up: A.persoSprite.setTexture(PersoTex_h_h); waitForNextRotation = 30; isBackSide = true; if (shoot_ready) { tirer(projectiles, A, projectile1, 270.f, tir_1, tir_2, tir_3, tir_4, tir_5, tir_6); clock.restart() ; shoot_ready = false;  }break;
                    case Keyboard::Down:A.persoSprite.setTexture(PersoTex_h_b); waitForNextRotation = 30; isBackSide = false; if (shoot_ready) { tirer(projectiles, A, projectile1, 90.f, tir_1, tir_2, tir_3, tir_4, tir_5, tir_6);  clock.restart(); shoot_ready = false;  }break;
                    case Keyboard::Left:A.persoSprite.setTexture(PersoTex_h_g); waitForNextRotation = 30; isBackSide = false; if (shoot_ready) { tirer(projectiles, A, projectile1, 180.f, tir_1, tir_2, tir_3, tir_4, tir_5, tir_6); clock.restart(); shoot_ready = false; }break;
                    case Keyboard::Right:A.persoSprite.setTexture(PersoTex_h_d); waitForNextRotation = 30; isBackSide = false; if (shoot_ready) { tirer(projectiles, A, projectile1, 0.f, tir_1, tir_2, tir_3, tir_4, tir_5, tir_6); clock.restart(); shoot_ready = false;  }break;
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

                if (A.GetHitbox().contains(point)) {
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
                while (A.GetHitbox().contains(point))
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

                if (A.GetHitbox().intersects(sf::FloatRect(background.portes[i].left, background.portes[i].top, background.portes[i].width, background.portes[i].height)) && background.portesActives) {
                    mat[background.row][background.col]=3;
                    ADNs.clear();
                    ADNs_boundingbox.clear();
                    ennemisQuiBougent.clear();
                    background.ChangeMap(i, A, window, porte_haut_sp, porte_bas_sp, porte_gauche_sp, porte_droite_sp);
                    
                    if (mat[background.row][background.col]==1){
                        vector<vector<int>> nouveaux_ennemis= generation_ennemis(i, 3);
                        active_rando=true;
                        srand(time(0));
                        for (size_t i = 0; i < nouveaux_ennemis.size(); i ++) {
                            int sprite_choisi = rand() % 3 + 1;
                            switch (sprite_choisi){
                            case 1:
                                ennemies.push_back(new Perso((nouveaux_ennemis[i][0])*WindowSize.x/1920, (nouveaux_ennemis[i][1])*WindowSize.y/1080, 0., 50, 5, 5, 5, spriteEnnemy1, spriteEnnemy1));
                                break;
                            case 2:
                                ennemies.push_back(new Perso((nouveaux_ennemis[i][0])*WindowSize.x/1920, (nouveaux_ennemis[i][1])*WindowSize.y/1080, 0., 50, 5, 5, 5, spriteEnnemy2, spriteEnnemy1));
                                ennemisQuiBougent.push_back(ennemies.size() - 1);
                                break;
                            case 3:
                                ennemies.push_back(new Perso((nouveaux_ennemis[i][0]*WindowSize.x)/1920, (nouveaux_ennemis[i][1]*WindowSize.y)/1080, 0., 50, 5, 5, 5, spriteEnnemy3, spriteEnnemy1));
                                
                                break;
                            }
                            ennemy_shoot_time.push_back(Clock());
                            changeTexture.push_back(Clock());
                        }
                    }
                    if (mat[background.row][background.col]==2){
                        ennemies.push_back(new Perso(1000*WindowSize.x/1920, 500*WindowSize.y/1080 ,0.,200,5,10,7, spriteBoss, spriteBoss));
                        ennemy_shoot_time.push_back(Clock());
                        changeTexture.push_back(Clock());
                        musique_jeu.stop();
                        musique_boss.play();
                }
                }
            }

            // Clear the window and apply background
            window.clear(Color::White);

            window.draw(background.backgroundSprite);

            background.BoucheTrou(window, mat, porte_haut_sp, porte_bas_sp, porte_gauche_sp, porte_droite_sp);

            for (size_t j = 0; j < projectiles.size(); j++) {
                if (projectiles[j]->isAlive(window)) {

                    bool touchBorder = false;

                    for (const auto& point : background.borduresPoints) {
                        touchBorder = touchBorder || projectiles[j]->projectileSprite.getGlobalBounds().contains(point);
                    }

                    projectiles[j]->update(window);
                    window.draw(projectiles[j]->projectileSprite);
                    if (touchBorder) {
                        projectiles.erase(projectiles.begin() + j);
                    }
                }
            }
            for (size_t i = 0; i < ennemies.size(); i++) {
                if (A.GetHitbox().intersects(ennemies[i]->persoSprite.getGlobalBounds()) && !invincible) {
                    A.Setpvdamage(ennemies[i]->Getatk());
                    invincible = true;
                    clockiframes.restart();

                }
                for (size_t j = 0; j < projectiles.size(); j++) {
                    if (projectiles[j]->isAlive(window)) {
                        if (ennemies[i]->checkAlive() && projectiles[j]->hit(*ennemies[i])) {

                            ennemies[i]->persoSprite.setColor(Color(255,200,200));
                            projectiles.erase(projectiles.begin() + j);
                            ennemies[i]->Setpvdamage(A.Getatk());
                        }
                    }
                }
                if (changeTexture[i].getElapsedTime().asSeconds()>=0.2f){
                    ennemies[i]->persoSprite.setColor(Color(255, 255, 255));
                    changeTexture[i].restart();
                }
                window.draw(ennemies[i]->persoSprite);
                if (ennemies[i]->checkAlive()) {
                    if (count(ennemisQuiBougent.begin(), ennemisQuiBougent.end(), i))
                    {

                        Vector2f direction = A.persoSprite.getPosition() - ennemies[i]->persoSprite.getPosition();

                        float angle = (atan2(direction.y, direction.x) * 180 / 3.14)+45;
                        ennemies[i]->persoSprite.setRotation(angle);

                        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                        if (distance > 50.0f) {
                            direction /= distance;
                            float speed = 2;
                            ennemies[i]->persoSprite.move(direction* speed);
                        }
                    }
                    else {
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
                }

                if (!ennemies[i]->checkAlive()) {
                    
                    for (size_t n = 0; n < ennemisQuiBougent.size(); n++)
                    {
                        if ((int)i<=ennemisQuiBougent[n])
                        {
                            ennemisQuiBougent[n]--;
                            if ((int)i == ennemisQuiBougent[n])
                            {
                                ennemisQuiBougent[n]=10;
                            }
                        }
                    }
                    ADNs.push_back(ennemies[i]->persoSprite.getPosition());
                    spriteADN.setPosition(ennemies[i]->persoSprite.getPosition());
                    ADNs_boundingbox.push_back(spriteADN.getGlobalBounds());
                    ennemies.erase(ennemies.begin() + i);
                    window.draw(spriteADN);
                    ennemy_shoot_time.erase(ennemy_shoot_time.begin() + i);
                    changeTexture.erase(changeTexture.begin() + i);
                    if (ennemies.size() == 0){ 
                        active_pu = true;
                        active_rando = false;
                    }
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
                        invincible = true;
                        clockiframes.restart();
                        projectiles_ennemi.erase(projectiles_ennemi.begin() + j);
                    }
                }
            } 

            if (!A.checkAlive()) {
                restart = true;
            }
            A.isInWindow(window);
            A.update(upFlag, downFlag, leftFlag, rightFlag, window);

            if ((rightFlag&&!leftFlag)) {
                numTexSpriteAnim_h = 0;
                numTexSpriteAnim = 0;
                numTexSpriteAnim_g = 0;
                if (waitForNextFrame == 0)
                {
                    switch (numTexSpriteAnim_d)
                    {
                    case 0:
                        A.persoSpriteBas.setTexture(PersoTex_b_1_d);
                        numTexSpriteAnim_d++;
                        break;
                    case 1:
                        A.persoSpriteBas.setTexture(PersoTex_b_2_d);
                        numTexSpriteAnim_d++;
                        break;
                    case 2:
                        A.persoSpriteBas.setTexture(PersoTex_b_3_d);
                        numTexSpriteAnim_d++;
                        break;
                    case 3:
                        A.persoSpriteBas.setTexture(PersoTex_b_4_d);
                        numTexSpriteAnim_d++;
                        break;
                    case 4:
                        A.persoSpriteBas.setTexture(PersoTex_b_5_d);
                        numTexSpriteAnim_d++;
                        break;
                    case 5:
                        A.persoSpriteBas.setTexture(PersoTex_b_6_d);
                        numTexSpriteAnim_d++;
                        break;
                    case 6:
                        A.persoSpriteBas.setTexture(PersoTex_b_7_d);
                        numTexSpriteAnim_d++;
                        break;
                    case 7:
                        A.persoSpriteBas.setTexture(PersoTex_b_8_d);
                        numTexSpriteAnim_d++;
                        break;
                    case 8:
                        A.persoSpriteBas.setTexture(PersoTex_b_9_d);
                        numTexSpriteAnim_d++;
                        break;
                    default:
                        A.persoSpriteBas.setTexture(PersoTex_b_0);
                        numTexSpriteAnim_d = 0;
                        break;
                    }
                    waitForNextFrame = timeToWait;
                }
                else {
                    waitForNextFrame--;
                }

            }

            else if ((leftFlag && !rightFlag)) {
                numTexSpriteAnim_h = 0;
                numTexSpriteAnim = 0;
                numTexSpriteAnim_d = 0;
                if (waitForNextFrame == 0)
                {
                    switch (numTexSpriteAnim_g)
                    {
                    case 0:
                        A.persoSpriteBas.setTexture(PersoTex_b_1_g);
                        numTexSpriteAnim_g++;
                        break;
                    case 1:
                        A.persoSpriteBas.setTexture(PersoTex_b_2_g);
                        numTexSpriteAnim_g++;
                        break;
                    case 2:
                        A.persoSpriteBas.setTexture(PersoTex_b_3_g);
                        numTexSpriteAnim_g++;
                        break;
                    case 3:
                        A.persoSpriteBas.setTexture(PersoTex_b_4_g);
                        numTexSpriteAnim_g++;
                        break;
                    case 4:
                        A.persoSpriteBas.setTexture(PersoTex_b_5_g);
                        numTexSpriteAnim_g++;
                        break;
                    case 5:
                        A.persoSpriteBas.setTexture(PersoTex_b_6_g);
                        numTexSpriteAnim_g++;
                        break;
                    case 6:
                        A.persoSpriteBas.setTexture(PersoTex_b_7_g);
                        numTexSpriteAnim_g++;
                        break;
                    case 7:
                        A.persoSpriteBas.setTexture(PersoTex_b_8_g);
                        numTexSpriteAnim_g++;
                        break;
                    case 8:
                        A.persoSpriteBas.setTexture(PersoTex_b_9_g);
                        numTexSpriteAnim_g++;
                        break;
                    default:
                        A.persoSpriteBas.setTexture(PersoTex_b_0);
                        numTexSpriteAnim_g = 0;
                        break;
                    }
                    waitForNextFrame = timeToWait;
                }
                else {
                    waitForNextFrame--;
                }

            }

            else if (downFlag&&!upFlag) {
                numTexSpriteAnim_h = 0;
                numTexSpriteAnim_d = 0;
                numTexSpriteAnim_g = 0;
                if (waitForNextFrame == 0)
                {
                    switch (numTexSpriteAnim)
                    {
                    case 0:
                        A.persoSpriteBas.setTexture(PersoTex_b_1);
                        numTexSpriteAnim++;
                        break;
                    case 1:
                        A.persoSpriteBas.setTexture(PersoTex_b_2);
                        numTexSpriteAnim++;
                        break;
                    case 2:
                        A.persoSpriteBas.setTexture(PersoTex_b_3);
                        numTexSpriteAnim++;
                        break;
                    case 3:
                        A.persoSpriteBas.setTexture(PersoTex_b_4);
                        numTexSpriteAnim++;
                        break;
                    case 4:
                        A.persoSpriteBas.setTexture(PersoTex_b_0);
                        numTexSpriteAnim++;
                        break;
                    case 5:
                        A.persoSpriteBas.setTexture(PersoTex_b_5);
                        numTexSpriteAnim++;
                        break;
                    case 6:
                        A.persoSpriteBas.setTexture(PersoTex_b_6);
                        numTexSpriteAnim++;
                        break;
                    case 7:
                        A.persoSpriteBas.setTexture(PersoTex_b_7);
                        numTexSpriteAnim++;
                        break;
                    case 8:
                        A.persoSpriteBas.setTexture(PersoTex_b_8);
                        numTexSpriteAnim++;
                        break;
                    default:
                        A.persoSpriteBas.setTexture(PersoTex_b_0);
                        numTexSpriteAnim = 0;
                        break;
                    }
                    waitForNextFrame = timeToWait;
                }
                else {
                    waitForNextFrame--;
                }

            }

            else if (upFlag&&!downFlag) {
                numTexSpriteAnim = 0;
                numTexSpriteAnim_d = 0;
                numTexSpriteAnim_g = 0;
                if (waitForNextFrame == 0)
                {
                    switch (numTexSpriteAnim_h)
                    {
                    case 0:
                        A.persoSpriteBas.setTexture(PersoTex_b_1_h);
                        numTexSpriteAnim_h++;
                        break;
                    case 1:
                        A.persoSpriteBas.setTexture(PersoTex_b_2_h);
                        numTexSpriteAnim_h++;
                        break;
                    case 2:
                        A.persoSpriteBas.setTexture(PersoTex_b_3_h);
                        numTexSpriteAnim_h++;
                        break;
                    case 3:
                        A.persoSpriteBas.setTexture(PersoTex_b_4_h);
                        numTexSpriteAnim_h++;
                        break;
                    case 4:
                        A.persoSpriteBas.setTexture(PersoTex_b_0_h);
                        numTexSpriteAnim_h++;
                        break;
                    case 5:
                        A.persoSpriteBas.setTexture(PersoTex_b_5_h);
                        numTexSpriteAnim_h++;
                        break;
                    case 6:
                        A.persoSpriteBas.setTexture(PersoTex_b_6_h);
                        numTexSpriteAnim_h++;
                        break;
                    case 7:
                        A.persoSpriteBas.setTexture(PersoTex_b_7_h);
                        numTexSpriteAnim_h++;
                        break;
                    case 8:
                        A.persoSpriteBas.setTexture(PersoTex_b_8_h);
                        numTexSpriteAnim_h++;
                        break;
                    default:
                        A.persoSpriteBas.setTexture(PersoTex_b_0_h);
                        numTexSpriteAnim_h = 0;
                        break;
                    }
                    waitForNextFrame = timeToWait;
                }
                else {
                    waitForNextFrame--;
                }
            }
            
            else{
                if (isBackSide){
                    A.persoSpriteBas.setTexture(PersoTex_b_0_h);
                }
                else {
                    A.persoSpriteBas.setTexture(PersoTex_b_0);
                }
            }
            

            if (waitForNextRotation == 0)
            {
                if (upFlag) { A.persoSprite.setTexture(PersoTex_h_h); isBackSide = true;}
                if (downFlag) { A.persoSprite.setTexture(PersoTex_h_b); isBackSide = false;}
                if (leftFlag) { A.persoSprite.setTexture(PersoTex_h_g); isBackSide = false;}
                if (rightFlag) { A.persoSprite.setTexture(PersoTex_h_d); isBackSide = false;}
            }
            else {
                waitForNextRotation--;
            }

            window.draw(A.persoSpriteBas);
            window.draw(A.persoSprite);
            
            if(ADNs.size()!=0){
                for(const auto& adn : ADNs){
                    spriteADN.setPosition(adn);
                    window.draw(spriteADN);
                }
            }

            for(size_t i=0;i<ADNs.size();i++){
                if(A.GetHitbox().intersects(ADNs_boundingbox[i])){
                    pvBonusAnim += 20;
                    power_up.play();
                    ADNs_boundingbox.erase(ADNs_boundingbox.begin()+i);
                    ADNs.erase(ADNs.begin()+i);
                }
            }

            //Powerups
            
            if (active_pu){

                switch(rando){
                    case 0: PowerUpSprite.setTexture(SwordPU);break;
                    case 1: PowerUpSprite.setTexture(SpeedPU);break;
                    case 2: PowerUpSprite.setTexture(HealthPU);break;
                    case 3: PowerUpSprite.setTexture(AtkDelayPU);break;


                }

                window.draw(PowerUpSprite);
                if (A.GetHitbox().intersects(PowerUpSprite.getGlobalBounds())){
                    power_up.play();
                    active_pu = false;
                    
                    switch(rando){
                    case 0: A.Setatk(A.Getatk() + 1);break;
                    case 1: A.SetSpeed(A.GetSpeed()+1);break;
                    case 2: {int ratio = ((float)A.Getpv()/(float)A.Getpvmax())*10;  A.SetPvMax(A.Getpvmax() + 10); A.Setpvdamage(-ratio); break;}
                    case 3: A.SetDelay(A.GetDelay()-sf::milliseconds(50));break; 
                }
            }
            }

            if (ennemies.size()==0 && !active_pu && ADNs.size()==0){
                background.portesActives = true;
            }
            //HUD vie

            Vie.setScale((A.Getpv()*ScaleX/A.Getpvmax()), ScaleY);
            if (pvBonusAnim!=0)
            {
                A.AddPV(1);
                pvBonusAnim--;
            }
            window.draw(Vie);
            window.draw(BarreVie);

            
            //HUD attaque
            window.draw(sword);
            attaque.setString(to_string(A.Getatk()));
            window.draw(attaque);

            //HUD vitesse de déplacement
            window.draw(speed);
            vitesseDeplacement.setString(to_string(A.GetSpeed()));
            window.draw(vitesseDeplacement);

            //HUD vitesse de tir
            window.draw(arrows);
            vitesseTir.setString(to_string(A.GetDelay().asMilliseconds()));
            window.draw(vitesseTir);
            window.display();

            if ((mat[background.row][background.col]==2) && ennemies.size()==0){
                window.clear(Color::Black);
                window.draw(spritefin);
            }
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
                            goto start;
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

                window.display();
            }
        }

        else if (!start && !restart && !close && credits) {
            background.creditsSprite.setPosition(0, WindowSize.y);
            while (credits && background.creditsSprite.getPosition().y > 0) {
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