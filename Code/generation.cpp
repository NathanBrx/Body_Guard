#include "generation.hpp"
using namespace std;

// Fonction récursive pour remplir la carte
// Prend en entrée les coordonnées x et y de départ, et le nombre de salles restant à placer
void fill_map(int x, int y, int* nb_salles, int mat[][8]){
    // Cas de base : si on a placé toutes les salles ou si on sort de la carte
    if(*nb_salles <= 0 || x < 0 || x >= 9 || y < 0 || y >= 8){
        return;
    }
    // On place une salle dans la case actuelle
    if(rand()%2 == 1){
        mat[x][y] = 1 ;
        (*nb_salles)-- ;
        // On appelle récursivement fill_map pour chaque case voisine non explorée
        if(x+1 < 9 && mat[x+1][y] == 0){
            fill_map(x+1, y, nb_salles, mat);
        }
        if(y+1 < 8 && mat[x][y+1] == 0){
            fill_map(x, y+1, nb_salles, mat);
        }
        if(x-1 >= 0 && mat[x-1][y] == 0){
            fill_map(x-1, y, nb_salles, mat);
        }
        if(y-1 >= 0 && mat[x][y-1] == 0){
            fill_map(x, y-1, nb_salles, mat);
        }
    }
}

void bossRoom(int mat[][8]){
    //trouve la salle la plus éloignée de la salle de départ et y place la salle de boss
    int maxx = 0;
    int maxy = 0;
    float max_dist = 0;
    for(int x = 0;x<9;x++){
        for(int y = 0;y<8;y++){ 
            float dist = sqrt(pow(x-3,2)+pow(y-5,2));
            if(dist > max_dist && mat[x][y]== 1){
                max_dist = dist;
                maxx = x;
                maxy = y;
            }  
        }
    }
    mat[maxx][maxy] = 2;
}

int generation(){
    int nb_salles = 6;
    int mat[9][8] = {0}; // Initialisation de la carte à 0
    srand(time(0));
    mat[3][5] = 1 ; // Position de départ
    while(nb_salles>0){
        mat[9][8] = {0};
        nb_salles = 6;
        fill_map(3, 5, &nb_salles, mat);
    }
    bossRoom(mat);
    // Affichage de la carte
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 8; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    return mat;
}