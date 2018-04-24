#pragma once
#include <stdlib.h>          //For random numbers
#include <time.h>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "GameObject.hpp"
#include "Asteroid.h"
#include "Enemy.hpp"
#include "Planet.h"
#include "SpaceShip.hpp"
#include "HealthBar.hpp"
#include "Star.h"
#include "BlackHole.h"
#include <string>
#include <sstream>
#include <stdexcept>

class GameManager
{
public:
    GameManager()
    {
        printf("GameManager created /n");
    }
    void Save(std::vector<GameObject*>, GameObject*, GameObject*, HealthBar*);
    std::vector<GameObject*> Load(LTexture*, LTexture*,LTexture*,LTexture*, LTexture*, LTexture*, LTexture*);
};
