#pragma once

class Perso : public Sprite {

private:

    float  xOrigin, yOrigin; // position d'origine de l'entit�
    float rotation;
    int pvmax; // pv max du perso 
    int pv = pvmax; // pv de l'entit�
    int speed; // vitesse de l'entit� 
    int atk;
    int atkSpeed; // vitesse d'attaque
    int alive = 1; // bool�en qui indique si le perso est mort ou vivant (1=vivant, 0=mort )

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
    sf::Time GetDelay();

    // Setters

    void Reset();
    void SetX(float x);
    void SetY(float y);
    void SetSpeed(int speed);
    void SetatkSpeed(int atkSpeed);
    void SetRotation(float rotation);
    void Setpvdamage(int diffpv);
    void SetDelay(sf::Time shoot_delay);

    // Methodes

    bool checkAlive();
    void update(bool upFlag, bool downFlag, bool leftFlag, bool rightFlag, RenderWindow& window);
    void isInWindow(RenderWindow& window);
    Sprite persoSprite; //attribut sprite du personnage
    void damage(Texture& texturehit, Texture& texturebase, RenderWindow& window); // m�thode pour afficher l'animation de d�gats

    // Destructeur
    ~Perso();
};