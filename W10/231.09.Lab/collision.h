/***********************************************************************
 * collision.h
 ************************************************************************/

#pragma once

#include <vector>

class Satellite;
class Simulatable;

bool collide(const Satellite& a, const Satellite& b);
bool collideEarth(const Satellite& s, double earthRadius);
void resolveCollision(Satellite* a, Satellite* b, std::vector<Simulatable*>& bodies);
