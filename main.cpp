#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Body Guard");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Texture texture;
        if (!texture.loadFromFile("dragon.png")){
            cerr << "failed to load image" << endl;
            exit(1);
        }
        texture.setRepeated(false);
        texture.setSmooth(true);
        
        sf::Sprite sprite;
        sprite.setTexture(texture);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
//        window.draw(shape);
        window.draw(sprite);
        window.display();
    }

    return 0;
}