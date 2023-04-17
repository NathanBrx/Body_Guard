#include "mainheader.hpp"
using namespace std;
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

void haut(vector<vector<int>>& tab){
    tab.push_back({1600, 400}); tab.push_back({1800, 555}); tab.push_back({1560, 755});
    tab.push_back({1200, 766}); tab.push_back({970, 825}); tab.push_back({710, 725});
    tab.push_back({330, 705}); tab.push_back({160, 585}); tab.push_back({300, 405});
    tab.push_back({680, 530}); tab.push_back({1210, 540});
}

void droite(vector<vector<int>>& tab){
    tab.push_back({987, 265}); tab.push_back({740, 340}); tab.push_back({1364, 324});
    tab.push_back({1200, 766}); tab.push_back({970, 825}); tab.push_back({710, 725});
    tab.push_back({330, 705}); tab.push_back({160, 585}); tab.push_back({300, 405});
    tab.push_back({680, 530}); tab.push_back({1210, 540});
}

void bas(vector<vector<int>>& tab){
    tab.push_back({987, 265}); tab.push_back({740, 340}); tab.push_back({1364, 324});
    tab.push_back({1600, 400}); tab.push_back({1800, 555}); tab.push_back({1560, 755});
    tab.push_back({330, 705}); tab.push_back({160, 585}); tab.push_back({300, 405});
    tab.push_back({680, 530}); tab.push_back({1210, 540});
}

void gauche(vector<vector<int>>& tab){
    tab.push_back({987, 265}); tab.push_back({740, 340}); tab.push_back({1364, 324});
    tab.push_back({1600, 400}); tab.push_back({1800, 555}); tab.push_back({1560, 755});
    tab.push_back({1200, 766}); tab.push_back({970, 825}); tab.push_back({710, 725});
    tab.push_back({680, 530}); tab.push_back({1210, 540});
}


