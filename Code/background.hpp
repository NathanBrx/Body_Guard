#pragma once

class Background {
public:

    Background(string accueil_path,string jeu_path,string fin_path , float ScaleX, float ScaleY);

    std::vector<sf::RectangleShape> rectangles;
    std::vector<sf::FloatRect> hitboxs;
    void ChangeMap(int porteTouchee, Perso& A,RenderWindow& window, Sprite& porte_haut, Sprite& porte_bas, Sprite& porte_gauche, Sprite& porte_droite);
    void BoucheTrou(RenderWindow& window, int mat[][8], Sprite porte_haut, Sprite porte_bas, Sprite porte_gauche, Sprite porte_droite);


    Sprite backgroundSprite,accueilSprite,finSprite;
    Texture backgroundTexture,accueil_tx,fin_tx;
    string accueil_path, jeu_path, fin_path;


    float ScaleX;
    float ScaleY;
    std::vector<sf::Vector2f> borduresPoints_sansPortes_notScaled;
    std::vector<sf::Vector2f> borduresPoints_sansPortes;
    std::vector<sf::Vector2f> borduresPoints;

    std::vector<sf::Vector2f> bordures_gauche_notScaled;
    std::vector<sf::Vector2f> bordures_gauche;
    std::vector<sf::Vector2f> bordures_droite_notScaled;
    std::vector<sf::Vector2f> bordures_droite;
    std::vector<sf::Vector2f> bordures_haut_notScaled;
    std::vector<sf::Vector2f> bordures_haut;
    std::vector<sf::Vector2f> bordures_bas_notScaled;
    std::vector<sf::Vector2f> bordures_bas;
    std::vector<sf::IntRect> portes;
    bool isFlipX;
    bool isFlipY;
    bool portesActives;

    bool porte_bas;
    bool porte_droite;
    bool porte_gauche;
    bool porte_haut;

    int row;
    int col;

};