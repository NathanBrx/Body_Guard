#include "mainheader.hpp"
using namespace sf;

void tirer(vector<Projectile*>& projectiles, Perso& A, Sprite projectile1, float direction,Sound& tir_1, Sound& tir_2, Sound& tir_3, Sound& tir_4, Sound& tir_5, Sound& tir_6) {
    float x = A.GetX();
    float y = A.GetY();
    projectiles.push_back(new Projectile(x, y, direction, A.GetatkSpeed(), projectile1));

    int sound;
    sound = rand() % 6;
    switch (sound)
    {
    case(0):
        tir_1.play();
        break;
    case(1):
        tir_2.play();
        break;
    case(2):
        tir_3.play();
        break;
    case(3):
        tir_4.play();
        break;
    case(4):
        tir_5.play();
        break;
    case(5):
        tir_6.play();
        break;
    default:
        break;
    }
}


void loadFile(Texture &texture,String filePath) {
    if (!texture.loadFromFile(filePath)) {
        cerr << "failed to load texture" << endl;
        exit(1);
    }
}
