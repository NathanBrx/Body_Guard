#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

#include "generation.hpp"
#include "perso.hpp"
#include "projectile.hpp"
#include "background.hpp"
#include "projectile_ennemi.hpp"

void tirer(vector<Projectile*>& projectiles, Perso& A, Sprite projectile1, float direction);

void loadFile(Texture& texture, String filePath);