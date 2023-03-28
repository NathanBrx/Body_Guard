#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <cmath>
using namespace sf;
using namespace std;

class Perso : public Sprite {
    
    private :

        float  xOrigin,yOrigin ; // position d'origine de l'entité
        float rotation;
        int pvmax; // pv max du perso 
        int pv = pvmax ; // pv de l'entité
        int speed ; // vitesse de l'entité 
        int atk ;
        int atkSpeed ; // vitesse d'attaque
        int alive = 1; // booléen qui indique si le perso est mort ou vivant (1=vivant, 0=mort )
    
    public :

        Perso(float xOrigin,float yOrigin,float rotation,int pvmax,int speed,int atk,int atkSpeed,Sprite persoSprite);

        FloatRect hitbox;

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
        void update(bool upFlag,bool downFlag,bool leftFlag,bool rightFlag,RenderWindow& window);
        void isInWindow(RenderWindow& window);
        Sprite persoSprite ; //attribut sprite du personnage
        void damage(Texture& texturehit,Texture& texturebase,RenderWindow& window); // méthode pour afficher l'animation de dégats

        // Destructeur
        ~Perso();
};

class Projectile : public Sprite {
    
    private:

        float xOrigin,yOrigin;
        float direction;
        int vitesse; //déplacement pixel par seconde
    
    public:

        Projectile(float xOrigin,float yOrigin,float direction,int vitesse,Sprite projectileSprite);

        // Getters

        float GetDirection();

        // Setters

        void SetDirection(float direction);
        void SetVitesse(int vitesse);

        // Methodes

        Sprite projectileSprite; // sprite du projectile
        void update(Projectile& projectile,Perso& A,RenderWindow& window,float direction); // méthode pour déplacer le projectile
        bool isAlive(Projectile& projectile,RenderWindow& window); // méthode pour vérifier si le projectile est toujours dans la fenêtre
        bool hit(Perso& p1); // méthode pour vérifier si le projectile touche le personnage
};
void tirer(vector<Projectile*>& projectiles,Perso& A,Sprite projectile1,float direction);

//Background

class Background {
    public :

        Background(Sprite backgroundSprite, string backgroundImage, std::vector<sf::Vector2f> borduresPoints);

        sf::RectangleShape CreateRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight);
        std::vector<sf::RectangleShape> rectangles;
        std::vector<sf::FloatRect> hitboxs;
        void MakeRectangles();

        void SetBackground();
        void SetTexture(float ScaleX, float ScaleY);
        Sprite backgroundSprite ; //attribut sprite du background
        Texture backgroundTexture; //attribut texture du background
        string backgroundImage;

        // Créer des points pour définir les rectangles
        std::vector<sf::Vector2f> borduresPoints;
        std::vector<sf::Vector2f> portesPoints;

};

