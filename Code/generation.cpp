#include <iostream>
#include<cstdlib>
using namespace std;

// Fonction récursive pour remplir la carte
// Prend en entrée les coordonnées x et y de départ, et le nombre de salles restant à placer
void fill_map(int x, int y, int nb_salles, int mat[][8]){
    // Cas de base : si on a placé toutes les salles ou si on sort de la carte
    if(nb_salles <= 0 || x < 0 || x >= 9 || y < 0 || y >= 8){
        return;
    }
    // On place une salle dans la case actuelle
    if(rand()%2 == 1){
        mat[x][y] = 1;
        nb_salles--;
        
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
int main(){
    int nb_salles = 6;
    int mat[9][8] = {0}; // Initialisation de la carte à 0
    srand(time(0));
    fill_map(3, 5, nb_salles, mat);
    mat[3][5] = 1 ; // Position de départ
    // Affichage de la carte
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 8; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}