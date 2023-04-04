#pragma once

class Background {
public:

    Background(Sprite backgroundSprite);

    sf::RectangleShape CreateRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight);
    std::vector<sf::RectangleShape> rectangles;
    std::vector<sf::FloatRect> hitboxs;
    void MakeRectangles();
    void MoveUp(Perso& A, RenderWindow& window,float ScaleX,float ScaleY);
    void MoveRight();
    void MoveDown();
    void MoveLeft();
    void ChangeMap(int porteTouchee, Perso& A,RenderWindow& window,float ScaleX,float ScaleY);

    Sprite backgroundSprite;
    std::vector<sf::Vector2f> borduresPoints;
    std::vector<sf::IntRect> portes;
    bool isFlipX;
    bool isFlipY;

};