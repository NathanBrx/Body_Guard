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

vector<vector<int>> generation_ennemis(int porte, int nbennemis){
    // 1 : haut {987,265} {740, 340} {1364,324}
    // 2 : droite {1600, 400} {1800, 555} {1560, 755}
    // 3 : bas {1200, 766} {970, 825} {710, 725}
    // 4 : gauche {330, 705} {160, 585} {300, 405}

    // {680, 530} {1210, 540}

    vector<vector<int>> coordonnees;

    switch(porte){
        case 0 : bas(coordonnees); break;
        case 1 : gauche(coordonnees); break;
        case 2 : haut(coordonnees); break; 
        case 3 : droite(coordonnees); break;
    }

    srand(time(0));
    for (int i = 0; i<(11-nbennemis); i++){
        int index = rand() % (11-i);
        coordonnees.erase(coordonnees.begin()+index);
    }


    return coordonnees;

}


Perso boss(int porte, Sprite spriteboss, Texture textureboss, Texture texturebosshit, Vector2u WindowSize){
    int xOrigin=0;
    int yOrigin=0;

    switch(porte){
        case 0 : xOrigin = 740; yOrigin = 340; break;
        case 1 : xOrigin = 1800; yOrigin = 555; break;
        case 2 : xOrigin = 970; yOrigin = 825; break;
        case 3 : xOrigin = 160; yOrigin = 585; break;
    }
    Perso boss = Perso(xOrigin*WindowSize.x/1920, yOrigin*WindowSize.y/1080, 0., 200, 10, 5, 8, spriteboss, spriteboss);
    return boss;
}