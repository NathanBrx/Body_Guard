#pragma once

class Projectile : public Sprite {

private:

    float xOrigin, yOrigin;
    float direction;
    int vitesse; //déplacement pixel par seconde

public:

    Projectile(float xOrigin, float yOrigin, float direction, int vitesse, Sprite projectileSprite);

    // Getters

    float GetDirection();

    // Setters

    void SetDirection(float direction);
    void SetVitesse(int vitesse);

    // Methodes

    Sprite projectileSprite; // sprite du projectile
    void update(Projectile& projectile, Perso& A, RenderWindow& window, float direction); // méthode pour déplacer le projectile
    bool isAlive(Projectile& projectile, RenderWindow& window); // méthode pour vérifier si le projectile est toujours dans la fenêtre
    bool hit(Perso& p1); // méthode pour vérifier si le projectile touche le personnage
};