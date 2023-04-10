#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

//Windows
//#include <chrono>
//#include <thread>

//Linux
#include<unistd.h>

using namespace sf;
using namespace std;

#include "generation.hpp"
#include "perso.hpp"
#include "projectile.hpp"
#include "background.hpp"
#include "projectile_ennemi.hpp"


void tirer(vector<Projectile*>& projectiles, Perso& A, Sprite projectile1, float direction,Sound& tir_1, Sound& tir_2, Sound& tir_3, Sound& tir_4, Sound& tir_5, Sound& tir_6);

void loadFile(Texture& texture, String filePath);