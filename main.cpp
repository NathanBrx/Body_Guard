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
        bool movespriteleft = false;
        bool movespriteright = false;
        while (window.pollEvent(event))
        {
            if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Left))
                movespriteleft = true;
            if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Right))
                movespriteright = true;
            if (event.type == Event::Closed)
                window.close();
        }

        if (movespriteleft){
            sprite.move(-10.f,-10.f);
        }
        if (movespriteright){
            sprite.move(10.f,10.f);
        }
        // en gros c'est a peu près ça mais plus compliqué.
        // voir https://lucidar.me/en/sfml/sfml-part-4-moving-a-sprite-with-the-keyboard/

        window.clear();
//        window.draw(shape);
        window.draw(sprite);
        window.display();
    }

    return 0;
}