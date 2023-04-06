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
    {{0,403},{24,420},{53,427},{83,426},{112,417},{137,401},{159,381},{181,360},{202,339},{225,319},{249,301},{274,285},{300,271},{328,259},{356,249},{385,241},{414,235},{444,231},{474,228},{504,224},{534,222},{564,220},{594,217},{623,215},{653,211},{683,207},{712,201},{741,194},{770,186},{797,171},{822,155},{843,133},{859,108},{871,81},{879,52},{886,23},{889,1},{918,0},{948,0},{978,0},{1008,0},{1038,0},{1068,0},{1091,20},{1112,42},{1131,65},{1149,89},{1165,114},{1183,138},{1200,163},{1219,186},{1242,205},{1269,219},{1299,222},{1329,220},{1358,212},{1386,203},{1414,192},{1442,182},{1471,172},{1500,164},{1528,155},{1558,148},{1587,141},{1616,136},{1646,135},{1676,137},{1706,140},{1735,146},{1762,159},{1786,178},{1804,202},{1813,231},{1820,260},{1822,290},{1825,320},{1831,349},{1840,378},{1852,405},{1870,429},{1890,452},{1913,470},{1916,500},{1917,530},{1917,560},{1918,590},{1918,620},{1918,650},{1916,662},{1886,666},{1858,676},{1831,691},{1807,708},{1783,727},{1761,747},{1739,767},{1718,788},{1694,807},{1671,826},{1649,846},{1624,863},{1598,877},{1570,889},{1542,899},{1513,907},{1483,913},{1454,917},{1424,919},{1394,920},{1364,918},{1334,916},{1304,912},{1274,911},{1244,907},{1215,904},{1185,901},{1155,902},{1127,913},{1104,932},{1096,961},{1101,991},{1110,1020},{1122,1047},{1138,1072},{1109,1078},{1079,1078},{1049,1078},{1019,1078},{989,1078},{959,1078},{929,1078},{899,1078},{877,1057},{865,1030},{851,1003},{834,978},{818,953},{798,930},{776,910},{752,892},{726,877},{699,865},{670,856},{641,849},{611,844},{581,841},{551,840},{521,839},{491,838},{461,839},{431,839},{401,838},{371,835},{342,832},{312,827},{283,819},{255,808},{227,798},{199,786},{172,773},{146,759},{119,744},{93,730},{68,715},{41,701},{15,685},{0,675},{0,645},{0,615},{0,585},{0,555},{0,525},{0,495},{0,465},{0,435}};

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

    const int ROWS = 8; // nombre de rang�es dans le tableau
    const int COLS = 7; // nombre de colonnes dans le tableau

    // V�rifier s'il y a une case vide adjacente en haut
    if (this->row == 0 || mat[this->row - 1][this->col] == 0) {
        if (!(this->isFlipY)) {
            window.draw(porte_haut);
        }
        else {
            window.draw(porte_bas);
        }
    }

    // V�rifier s'il y a une case vide adjacente en bas
    if (this->row == ROWS || mat[this->row + 1][this->col] == 0) {
        if (this->isFlipY) {
            window.draw(porte_haut);
        }
        else {
            window.draw(porte_bas);
        }
    }

    // V�rifier s'il y a une case vide adjacente � gauche
    if (this->col == 0 || mat[this->row][this->col - 1] == 0) {
        if (!(this->isFlipX)) {
            window.draw(porte_gauche);
        }
        else {
            window.draw(porte_droite);
        }
        
    }

    // V�rifier s'il y a une case vide adjacente � droite
    if (this->col == COLS || mat[row][this->col + 1] == 0) {
        if (this->isFlipX) {
            window.draw(porte_gauche);
        }
        else {
            window.draw(porte_droite);
        }
    }
}