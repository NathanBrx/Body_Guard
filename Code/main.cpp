#include "mainheader.hpp"

int main()
{

    RenderWindow window(VideoMode(/*VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height*/1920, 1080), "Body Guard"/*, Style::Fullscreen*/);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    Vector2u TextureSize, WindowSize;
    Sprite backgroundSprite, spriteMain, projectile1, spriteEnnemy1, porte_haut_sp, porte_droite_sp, porte_bas_sp, porte_gauche_sp;
    Texture backgroundTexture, textureSpriteLeft, textureSpriteRight, textureSpriteUp, textureSpriteDown, textureProjectile, textureEnnemy1, textureEnnemy1hit, porte_haut_tx, porte_droite_tx, porte_bas_tx, porte_gauche_tx;

    //string texturesPath = "../Textures/"; // Linux
    string texturesPath = "..\\Textures\\"; // Windows

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

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(ScaleX, ScaleY);

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

    Background background(backgroundSprite, ScaleX, ScaleY);

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


    int mat[9][8] = { 0 }; // Initialisation de la carte
    generation(mat);

    Color couleur(0, 0, 0);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();

            // If a key is pressed
            if (event.type == Event::KeyPressed) {
                couleur.r = 0;
                switch (event.key.code) {
                    // If escape is pressed, close the application
                case  Keyboard::Escape: window.close(); break;

                    // up, down, left and right keys
                case Keyboard::Z: upFlag = true; A.persoSprite.setTexture(textureSpriteUp); break;
                case Keyboard::S: downFlag = true; A.persoSprite.setTexture(textureSpriteDown); break;
                case Keyboard::Q: leftFlag = true; A.persoSprite.setTexture(textureSpriteLeft); break;
                case Keyboard::D: rightFlag = true; A.persoSprite.setTexture(textureSpriteRight); break;
                case Keyboard::Up: tirer(projectiles, A, projectile1, 270.f); break;
                case Keyboard::Down: tirer(projectiles, A, projectile1, 90.f); break;
                case Keyboard::Left: tirer(projectiles, A, projectile1, 180.f); break;
                case Keyboard::Right: tirer(projectiles, A, projectile1, 0.f); break;
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
                couleur.r = 255;
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
            rectangle.setOutlineThickness(1);
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
        }

        window.display();


    }
}