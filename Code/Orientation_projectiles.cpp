#include <iostream>
#include <cmath>
A="nom du perso";
B="nom de l'objet ennemi";

float X_ennemi=B.GetX();
float Y_ennemi=B.GetY();
float X_perso=A.GetX();
float Y_perso=A.GetY();

float oppose=X_ennemi-X_perso;
float hypothenuse=((X_ennemi-X_perso)**2+(Y_ennemi-Y_perso)**2)**(1/2);
float cos=adjacent/hypothenuse;
float sin=oppose/hypothenuse;


float orientation(float X_ennemi,float Y_ennemi,float X_perso, float Y_perso){
    float oppose=X_ennemi-X_perso;
    float hypothenuse=((X_ennemi-X_perso)**2+(Y_ennemi-Y_perso)**2)**(1/2);
    float cos=adjacent/hypothenuse;
    float sin=oppose/hypothenuse;

    if (cos>0 && sin>0) return acos(cos);
    if (cos>0 && sin<0) return -asin(sin);
    if (cos<0 && sin>0) return acos(cos);
    if (cos<0 && sin<0) return -acos(cos);
} 

projectile.move(Vector2f vecteur(X_perso-X_ennemi,Y_perso-Y_ennemi),)