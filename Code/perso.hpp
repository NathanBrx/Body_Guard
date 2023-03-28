#pragma once

class Perso : public Sprite {

private:

    float  xOrigin, yOrigin; // position d'origine de l'entité
    float rotation;
    int pvmax; // pv max du perso 
    int pv = pvmax; // pv de l'entité
    int speed; // vitesse de l'entité 
    int atk;
    int atkSpeed; // vitesse d'attaque
    int alive = 1; // booléen qui indique si le perso est mort ou vivant (1=vivant, 0=mort )

public:

    Perso(float xOrigin, float yOrigin, float rotation, int pvmax, int speed, int atk, int atkSpeed, Sprite persoSprite);

    // Getters

    float GetX();
    float GetY();
    int GetSpeed();
    int Getatk();
    int Getpv();
    int Getpvmax();
    int GetatkSpeed();
    float GetRotation();

    // Setters

    void SetX(float x);
    void SetY(float y);
    void SetSpeed(int speed);
    void SetatkSpeed(int atkSpeed);
    void SetRotation(float rotation);
    void Setpv(int diffpv);

    // Methodes

    bool checkAlive();
    void update(bool upFlag, bool downFlag, bool leftFlag, bool rightFlag, RenderWindow& window);
    void isInWindow(RenderWindow& window);
    Sprite persoSprite; //attribut sprite du personnage
    void damage(Texture& texturehit, Texture& texturebase, RenderWindow& window); // méthode pour afficher l'animation de dégats

    // Destructeur
    ~Perso();
};