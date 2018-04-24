#ifndef Ammunition_hpp
#define Ammunition_hpp
#endif /* Ammunition_hpp */
#pragma once
#include <stdio.h>
#include<iostream>
#include<math.h>

#include"LTexture.h"
#include"GameObject.hpp"
#include <vector>
using namespace std;
class  Ammunition : public GameObject
{
protected:
	int harmValue;
public:
	Ammunition(LTexture* image, float, float, int, int, int, int, float);
	virtual ~Ammunition();
	void Move();
	int getHarmValue() { return harmValue; }
	void BoundaryCollision();
};
