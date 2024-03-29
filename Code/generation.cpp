#include "generation.hpp"
using namespace std;

// Fonction r�cursive pour remplir la carte
// Prend en entr�e les coordonn�es x et y de d�part, et le nombre de salles restant � placer
void fill_map(int x, int y, int* nb_salles, int mat[][8]) {
    // Cas de base : si on a plac� toutes les salles ou si on sort de la carte
    if (*nb_salles <= 0 || x < 0 || x >= 9 || y < 0 || y >= 8) {
        return;
    }
    // On place une salle dans la case actuelle
    if (rand() % 2 == 1) {
        mat[x][y] = 1;
        (*nb_salles)--;
        // On appelle r�cursivement fill_map pour chaque case voisine non explor�e
        if (x + 1 < 9 && mat[x + 1][y] == 0) {
            fill_map(x + 1, y, nb_salles, mat);
        }
        if (y + 1 < 8 && mat[x][y + 1] == 0) {
            fill_map(x, y + 1, nb_salles, mat);
        }
        if (x - 1 >= 0 && mat[x - 1][y] == 0) {
            fill_map(x - 1, y, nb_salles, mat);
        }
        if (y - 1 >= 0 && mat[x][y - 1] == 0) {
            fill_map(x, y - 1, nb_salles, mat);
        }
    }
}

void bossRoom(int mat[][8]) {
    //trouve la salle la plus �loign�e de la salle de d�part et y place la salle de boss
    int maxx = 0;
    int maxy = 0;
    float max_dist = 0;
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 8; y++) {
            float dist = sqrt(pow(x - 3, 2) + pow(y - 5, 2));
            if (dist > max_dist && mat[x][y] == 1) {
                max_dist = dist;
                maxx = x;
                maxy = y;
            }
        }
    }
    mat[maxx][maxy] = 2;
}

void generation(int mat[][8]) {
    int nb_salles = 6;
    srand(time(0));
    mat[3][5] = 1; // Position de d�part
    while (nb_salles > 0) {
        mat[9][8] = { 0 };
        nb_salles = 6;
        fill_map(3, 5, &nb_salles, mat);
    }
    bossRoom(mat);
}