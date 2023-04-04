#pragma once

class Projectile : public Sprite {

private:

    float xOrigin, yOrigin;
    float direction;
    int vitesse; //d�placement pixel par seconde

public:

    Projectile(float xOrigin, float yOrigin, float direction, int vitesse, Sprite projectileSprite);

    // Getters

    float GetDirection();

    // Setters

    void SetDirection(float direction);
    void SetVitesse(int vitesse);

    // Methodes

    Sprite projectileSprite; // sprite du projectile
    void update(Projectile& projectile, Perso& A, RenderWindow& window, float direction); // m�thode pour d�placer le projectile
    bool isAlive(Projectile& projectile, RenderWindow& window); // m�thode pour v�rifier si le projectile est toujours dans la fen�tre
    bool hit(Perso& p1); // m�thode pour v�rifier si le projectile touche le personnage
};