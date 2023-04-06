#include "mainheader.hpp"

Background::Background(Sprite backgroundSprite,float ScaleX,float ScaleY) :
    backgroundSprite(backgroundSprite),ScaleX(ScaleX),ScaleY(ScaleY)
{
    this->portes =
    {
    sf::IntRect(0, 0, 1920*this->ScaleX, 20*this->ScaleY),
    sf::IntRect(1900*this->ScaleX, 0, 20*this->ScaleX, 1080*this->ScaleY),
    sf::IntRect(0, 1070*this->ScaleY, 1920*this->ScaleX, 10*this->ScaleY),
    sf::IntRect(0, 0, 20*this->ScaleX, 1080*this->ScaleY)
    };

    this->borduresPoints_notScaled = 
    {{0, 390}, {78, 415}, {276, 279}, {400, 234},{730, 195},{815, 160}, {882, 66}, {890, 0}, {1070, 0}, {1280, 220},{1720, 148},{1840,400},{1920, 480},{1920, 660},{1136, 1080},{886, 1080},{0, 678}};

    for (const auto& point : this->borduresPoints_notScaled) {
        this->borduresPoints.push_back({point.x*this->ScaleX, point.y * this->ScaleY});
    }

    this->isFlipX = false;
    this->isFlipY = false;
    this->portesActives = true;

    this->row = 3;
    this->col = 5;

}

void Background::ChangeMap(int porteTouchee, Perso& A,RenderWindow& window, Sprite& porte_haut, Sprite& porte_bas, Sprite& porte_gauche, Sprite& porte_droite){

    this->portesActives = false;

    float moveXPerso;
    float moveYPerso;

    float newScaleX;
    float newScaleY;

    float newOriginX;
    float newOriginY;

    switch (porteTouchee)
    {
        case 0: // Haut

            if (!(this->isFlipY)) {
                newScaleY = -(this->ScaleY);
                newOriginY = this->backgroundSprite.getLocalBounds().height;
            }
            else {
                newScaleY = this->ScaleY;
                newOriginY = 0;
            }

            if (this->isFlipX) {
                newScaleX = -(this->ScaleX);
            }
            else {
                newScaleX = this->ScaleX;
            }
            newOriginX = this->backgroundSprite.getOrigin().x;


            moveYPerso = ((1025*this->ScaleY)-A.GetY())/36;

            for(int i=0; i<36;i+=1){
                window.clear();
                this->backgroundSprite.move(sf::Vector2f(0, 30*this->ScaleY));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(newScaleX,newScaleY);
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(newScaleX,-newScaleY);
                A.persoSprite.move(sf::Vector2f(0,moveYPerso));
                window.draw(A.persoSprite);
                window.display();
                std::this_thread::sleep_for(std::chrono::microseconds(1));
                //usleep(1);
            }

            this->backgroundSprite.setScale(newScaleX, newScaleY);
            this->backgroundSprite.setOrigin({ newOriginX, newOriginY });
            this->backgroundSprite.setPosition(0, 0);

            porte_haut.setScale(newScaleX, newScaleY);
            porte_haut.setOrigin({newOriginX, newOriginY});
            porte_haut.setPosition(0, 0);

            porte_bas.setScale(newScaleX, newScaleY);
            porte_bas.setOrigin({ newOriginX, newOriginY });
            if (this->isFlipY) {
                porte_bas.setPosition(0, 898 * ScaleY);
            }
            else {
                porte_bas.setPosition(0, -898 * ScaleY);
            }

            porte_droite.setScale(newScaleX, newScaleY);
            porte_droite.setOrigin({ newOriginX, newOriginY });
            porte_droite.setPosition(1855 * ScaleX, 0);
            if (this->isFlipX) {
                porte_droite.setPosition(-1855 * ScaleX, 0);
            }
            else {
                porte_droite.setPosition(1855 * ScaleX, 0);
            }

            porte_gauche.setScale(newScaleX, newScaleY);
            porte_gauche.setOrigin({ newOriginX, newOriginY });
            porte_gauche.setPosition(0, 0);

            this->isFlipY = !(this->isFlipY);
            this->row -= 1;

            break;

        case 1: // Droite
            
            if (this->isFlipY) {
                newScaleY = -(this->ScaleY);
            }
            else {
                newScaleY = this->ScaleY;
            }
            newOriginY = this->backgroundSprite.getOrigin().y;

            if (!(this->isFlipX)) {
                newScaleX = -(this->ScaleX);
                newOriginX = this->backgroundSprite.getLocalBounds().width;
            }
            else {
                newScaleX = this->ScaleX;
                newOriginX = 0;
            }

            moveXPerso = ((this->portes[3].left + 55 * this->ScaleX) - A.GetX()) / 64;

            for (int i = 0; i < 64; i += 1) {
                window.clear();
                this->backgroundSprite.move(sf::Vector2f(-30 * this->ScaleX, 0));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.move(sf::Vector2f(3840 * this->ScaleX, 0));
                this->backgroundSprite.setScale(newScaleX, newScaleY);
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(-newScaleX, newScaleY);
                this->backgroundSprite.move(sf::Vector2f(-3840 * this->ScaleX, 0));
                A.persoSprite.move(sf::Vector2f(moveXPerso, 0));
                window.draw(A.persoSprite);
                window.display();
                std::this_thread::sleep_for(std::chrono::microseconds(1));
                //usleep(1);
            }

            this->backgroundSprite.setScale(newScaleX, newScaleY);
            this->backgroundSprite.setOrigin({ newOriginX, newOriginY });
            this->backgroundSprite.setPosition(0, 0);

            porte_haut.setScale(newScaleX, newScaleY);
            porte_haut.setOrigin({ newOriginX, newOriginY });
            porte_haut.setPosition(0, 0);

            porte_bas.setScale(newScaleX, newScaleY);
            porte_bas.setOrigin({ newOriginX, newOriginY });
            if (this->isFlipY) {
                porte_bas.setPosition(0, -898 * ScaleY);
            }
            else {
                porte_bas.setPosition(0, 898 * ScaleY);
            }

            porte_droite.setScale(newScaleX, newScaleY);
            porte_droite.setOrigin({ newOriginX, newOriginY });
            porte_droite.setPosition(1855 * ScaleX, 0);
            if (this->isFlipX) {
                porte_droite.setPosition(1855 * ScaleX, 0);
            }
            else {
                porte_droite.setPosition(-1855 * ScaleX, 0);
            }

            porte_gauche.setScale(newScaleX, newScaleY);
            porte_gauche.setOrigin({ newOriginX, newOriginY });
            porte_gauche.setPosition(0, 0);

            this->isFlipX = !(this->isFlipX);
            this->col += 1;

            break;

        case 2: // Bas
            cerr << "bas";
            if (!(this->isFlipY)) {
                newScaleY = -(this->ScaleY);
                newOriginY = this->backgroundSprite.getLocalBounds().height;
            }
            else {
                newScaleY = this->ScaleY;
                newOriginY = 0;
            }

            if (this->isFlipX) {
                newScaleX = -(this->ScaleX);
            }
            else {
                newScaleX = this->ScaleX;
            }
            newOriginX = this->backgroundSprite.getOrigin().x;


            moveYPerso = ((55 * this->ScaleY) - A.GetY()) / 36;

            for (int i = 0; i < 36; i += 1) {
                window.clear();
                this->backgroundSprite.move(sf::Vector2f(0, -30 * this->ScaleY));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.move(sf::Vector2f(0, 2160 * this->ScaleY));
                this->backgroundSprite.setScale(newScaleX, newScaleY);
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(newScaleX, -newScaleY);
                this->backgroundSprite.move(sf::Vector2f(0, -2160 * this->ScaleY));
                A.persoSprite.move(sf::Vector2f(0, moveYPerso));
                window.draw(A.persoSprite);
                window.display();
                std::this_thread::sleep_for(std::chrono::microseconds(1));
                //usleep(1);
            }

            this->backgroundSprite.setScale(newScaleX, newScaleY);
            this->backgroundSprite.setOrigin({ newOriginX, newOriginY });
            this->backgroundSprite.setPosition(0, 0);

            porte_haut.setScale(newScaleX, newScaleY);
            porte_haut.setOrigin({ newOriginX, newOriginY });
            porte_haut.setPosition(0, 0);

            porte_bas.setScale(newScaleX, newScaleY);
            porte_bas.setOrigin({ newOriginX, newOriginY });
            if (this->isFlipY) {
                porte_bas.setPosition(0, 898 * ScaleY);
            }
            else {
                porte_bas.setPosition(0, -898 * ScaleY);
            }

            porte_droite.setScale(newScaleX, newScaleY);
            porte_droite.setOrigin({ newOriginX, newOriginY });
            porte_droite.setPosition(1855 * ScaleX, 0);
            if (this->isFlipX) {
                porte_droite.setPosition(-1855 * ScaleX, 0);
            }
            else {
                porte_droite.setPosition(1855 * ScaleX, 0);
            }

            porte_gauche.setScale(newScaleX, newScaleY);
            porte_gauche.setOrigin({ newOriginX, newOriginY });
            porte_gauche.setPosition(0, 0);

            this->isFlipY = !(this->isFlipY);
            this->row += 1;

            break;

        case 3: // Gauche
           
            if (this->isFlipY) {
                newScaleY = -(this->ScaleY);
            }
            else {
                newScaleY = this->ScaleY;
            }
            newOriginY = this->backgroundSprite.getOrigin().y;

            if (!(this->isFlipX)) {
                newScaleX = -(this->ScaleX);
                newOriginX = this->backgroundSprite.getLocalBounds().width;
            }
            else {
                newScaleX = this->ScaleX;
                newOriginX = 0;
            }

            moveXPerso = ((this->portes[1].left - 35 * this->ScaleX) - A.GetX()) / 64;

            for (int i = 0; i < 64; i += 1) {
                window.clear();
                this->backgroundSprite.move(sf::Vector2f(30 * this->ScaleX, 0));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(newScaleX, newScaleY);
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(-newScaleX, newScaleY);
                A.persoSprite.move(sf::Vector2f(moveXPerso, 0));
                window.draw(A.persoSprite);
                window.display();
                std::this_thread::sleep_for(std::chrono::microseconds(1));
                //usleep(1);
            }

            this->backgroundSprite.setScale(newScaleX, newScaleY);
            this->backgroundSprite.setOrigin({ newOriginX, newOriginY });
            this->backgroundSprite.setPosition(0, 0);

            porte_haut.setScale(newScaleX, newScaleY);
            porte_haut.setOrigin({ newOriginX, newOriginY });
            porte_haut.setPosition(0, 0);

            porte_bas.setScale(newScaleX, newScaleY);
            porte_bas.setOrigin({ newOriginX, newOriginY });
            if (this->isFlipY) {
                porte_bas.setPosition(0, -898 * ScaleY);
            }
            else {
                porte_bas.setPosition(0, 898 * ScaleY);
            }

            porte_droite.setScale(newScaleX, newScaleY);
            porte_droite.setOrigin({ newOriginX, newOriginY });
            porte_droite.setPosition(1855 * ScaleX, 0);
            if (this->isFlipX) {
                porte_droite.setPosition(1855 * ScaleX, 0);
            }
            else {
                porte_droite.setPosition(-1855 * ScaleX, 0);
            }

            porte_gauche.setScale(newScaleX, newScaleY);
            porte_gauche.setOrigin({ newOriginX, newOriginY });
            porte_gauche.setPosition(0, 0);

            this->isFlipX = !(this->isFlipX);
            this->col -= 1;

            break;

        default:
            cerr << "Porte inexistante";
            break;
    }
    this->portesActives = true;
}

void Background::BoucheTrou(RenderWindow& window, int mat[][8], Sprite porte_haut, Sprite porte_bas, Sprite porte_gauche, Sprite porte_droite) {

    const int ROWS = 8; // nombre de rangées dans le tableau
    const int COLS = 7; // nombre de colonnes dans le tableau

    // Vérifier s'il y a une case vide adjacente en haut
    if (this->row == 0 || mat[this->row - 1][this->col] == 0) {
        if (!(this->isFlipY)) {
            window.draw(porte_haut);
        }
        else {
            window.draw(porte_bas);
        }
    }

    // Vérifier s'il y a une case vide adjacente en bas
    if (this->row == ROWS || mat[this->row + 1][this->col] == 0) {
        if (this->isFlipY) {
            window.draw(porte_haut);
        }
        else {
            window.draw(porte_bas);
        }
    }

    // Vérifier s'il y a une case vide adjacente à gauche
    if (this->col == 0 || mat[this->row][this->col - 1] == 0) {
        if (!(this->isFlipX)) {
            window.draw(porte_gauche);
        }
        else {
            window.draw(porte_droite);
        }
        
    }

    // Vérifier s'il y a une case vide adjacente à droite
    if (this->col == COLS || mat[row][this->col + 1] == 0) {
        if (this->isFlipX) {
            window.draw(porte_gauche);
        }
        else {
            window.draw(porte_droite);
        }
    }
}