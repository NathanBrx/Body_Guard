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

vector generation_ennemis(int* tableau[9][8], int porte){
    // 1 : haut {987,265} {740, 340} {1364,324}
    // 2 : droite {1724, 328} {1800, 555} {1560, 755}
    // 3 : bas {1200, 766} {970, 825} {710, 725}
    // 4 : gauche {330, 705} {160, 585} {300, 405}

    // {680, 530} {1210, 540}

    void haut(vector<vector<int>>& tab){
        tab.push_back({987, 265});
        tab.push_back({987, 265});

    }

    vector<vector<int>> coordonnees;

    switch(porte){
        case 1 : 
        case 2 :
        case 3 :
        case 4 :
    }
}
