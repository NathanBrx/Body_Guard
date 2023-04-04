#pragma once

class Background {
public:

    Background(Sprite backgroundSprite,float ScaleX,float ScaleY);

    sf::RectangleShape CreateRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight);
    std::vector<sf::RectangleShape> rectangles;
    std::vector<sf::FloatRect> hitboxs;
    void MakeRectangles();
    void ChangeMap(int porteTouchee, Perso& A,RenderWindow& window);

    Sprite backgroundSprite;
    float ScaleX;
    float ScaleY;
    std::vector<sf::Vector2f> borduresPoints;
    std::vector<sf::IntRect> portes;
    bool isFlipX;
    bool isFlipY;

};