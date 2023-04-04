#pragma once

class Background {
public:

    Background(Sprite backgroundSprite, string backgroundImage, std::vector<sf::Vector2f> borduresPoints, std::vector<sf::IntRect> portes);

    sf::RectangleShape CreateRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight);
    std::vector<sf::RectangleShape> rectangles;
    std::vector<sf::FloatRect> hitboxs;
    void MakeRectangles();

    void SetBackground();
    void SetTexture(float ScaleX, float ScaleY);
    Sprite backgroundSprite; //attribut sprite du background
    Texture backgroundTexture; //attribut texture du background
    string backgroundImage;

    // Cr�er des points pour d�finir les rectangles
    std::vector<sf::Vector2f> borduresPoints;
    std::vector<sf::IntRect> portes;

};