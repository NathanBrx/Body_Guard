#pragma once


class generation_ennemis{
    private:
        tableau;
        porte;
        // 1 : haut
        // 2 : droite
        // 3 : bas
        // 4 : gauche
    public:
        generation_ennemis(int* tableau[9][8], int porte);


}

vector generation_ennemis(int* tableau[9][8], int porte);
