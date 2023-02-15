#include <SFML/Graphics.hpp>
using namespace sf;

class Perso : public Sprite {
    public :

        Perso(float x,float y,float rotation,int pvmax,int speed,int atk,Sprite persoSprite);

        void damage_taken(int atk); //méthode pour réduire les pv du personnage 
        void speed_modif(int speed);// modifier la vitesse du personnage 
        void SetX(float x);
        void SetY(float y);
        float GetRotation();
        float GetX();
        float GetY();
        int GetSpeed();
        void checkAlive();
        Sprite persoSprite ; //attribut sprite du personnage

    private :

        float  x,y ; // position de l'entité
        float rotation;
        int pvmax; // pv max du perso 
        int pv = pvmax ; // pv de l'entité
        int speed ; // vitesse de l'entité 
        int atk ;
        int alive = 1; // booléen qui indique si le perso est mort ou vivant (1=vivant, 0=mort )
};