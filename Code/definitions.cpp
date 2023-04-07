#include "mainheader.hpp"
using namespace sf;

void tirer(vector<Projectile*>& projectiles, Perso& A, Sprite projectile1, float direction) {
    float x = A.GetX();
    float y = A.GetY();
    projectiles.push_back(new Projectile(x, y, direction, A.GetatkSpeed(), projectile1));
}


void loadFile(Texture &texture,String filePath) {
    if (!texture.loadFromFile(filePath)) {
        cerr << "failed to load texture" << endl;
        exit(1);
    }
}
