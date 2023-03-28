#include "mainheader.hpp"

Background::Background(Sprite backgroundSprite, string backgroundImage, std::vector<sf::Vector2f> borduresPoints) :
    backgroundSprite(backgroundSprite), backgroundImage(backgroundImage), borduresPoints(borduresPoints)
{}

RectangleShape Background::CreateRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight)
{
    // Calculer la longueur et l'angle du rectangle
    float length = sqrt(pow(bottomRight.x - bottomLeft.x, 2) + pow(bottomRight.y - bottomLeft.y, 2));
    float angle = atan2(bottomRight.y - bottomLeft.y, bottomRight.x - bottomLeft.x);

    // Créer le rectangle
    RectangleShape rectangle;
    rectangle.setSize(Vector2f(length, 1.f));
    rectangle.setRotation(angle * 180.f / 3.14159f);

    // Positionner le rectangle en utilisant le coin inférieur gauche
    rectangle.setPosition(bottomLeft.x, bottomLeft.y - rectangle.getSize().y);

    return rectangle;
}

void Background::MakeRectangles() {
    for (size_t i = 0; i < this->borduresPoints.size() - 1; i += 1) {
        Vector2f bottomLeft = this->borduresPoints[i];
        Vector2f bottomRight = this->borduresPoints[i + 1];
        RectangleShape rectangle = this->CreateRectangle(bottomLeft, bottomRight);
        this->rectangles.push_back(rectangle);
    }
}

void Background::SetBackground() { // Met l'image de background dans la texture
    if (!this->backgroundTexture.loadFromFile(this->backgroundImage)) {
        cerr << "failed to load map texture" << endl;
        exit(1);
    }
}

void Background::SetTexture(float ScaleX, float ScaleY) { //Met la texture dans le sprite
    this->backgroundSprite.setTexture(this->backgroundTexture); // Set textures
    this->backgroundSprite.setScale(ScaleX, ScaleY);    // Set scales
    this->backgroundTexture.setRepeated(false);
}