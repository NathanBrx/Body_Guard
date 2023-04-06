#pragma once

class Background {
public:

    Background(Sprite backgroundSprite,float ScaleX,float ScaleY);

    std::vector<sf::RectangleShape> rectangles;
    std::vector<sf::FloatRect> hitboxs;
    void ChangeMap(int porteTouchee, Perso& A,RenderWindow& window, Sprite& porte_haut, Sprite& porte_bas, Sprite& porte_gauche, Sprite& porte_droite);
    void BoucheTrou(RenderWindow& window, int mat[][8], Sprite porte_haut, Sprite porte_bas, Sprite porte_gauche, Sprite porte_droite);

    Sprite backgroundSprite;
    float ScaleX;
    float ScaleY;
    std::vector<sf::Vector2f> borduresPoints_notScaled;
    std::vector<sf::Vector2f> borduresPoints;
    std::vector<sf::IntRect> portes;
    bool isFlipX;
    bool isFlipY;
    bool portesActives;

    int row;
    int col;

};