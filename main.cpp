#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        Texture texture;
        if (!texture.loadFromFile("dragon.png")){
            cerr << "failed to load image" << endl;
            exit(1);
        }
        texture.setRepeated(false);
        texture.setSmooth(true);

        Sprite sprite;
        sprite.setTexture(texture);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
//        window.draw(shape);
        window.draw(sprite);
        window.display();
    }

    return 0;
}