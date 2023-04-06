#include "mainheader.hpp"

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard"/*, Style::Fullscreen*/);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    Vector2u TextureSize;
    Vector2u WindowSize;
    Sprite backgroundSprite, spriteMain, projectile1, spriteEnnemy1;
    Texture backgroundTexture, textureSpriteLeft, textureSpriteRight, textureSpriteUp, textureSpriteDown, textureProjectile, textureEnnemy1, textureEnnemy1hit;

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


    int mat[9][8] = { 0 }; // Initialisation de la carte � 0
    generation(mat);

    while (window.isOpen())
    {
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

        for (size_t i = 0; i < background.portes.size(); i += 1) {
            if (A.persoSprite.getGlobalBounds().intersects(sf::FloatRect(background.portes[i].left, background.portes[i].top, background.portes[i].width, background.portes[i].height)) && background.portesActives){
                background.ChangeMap(i,A,window);
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

        // Code Temporaire affichage des bordures et des portes
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