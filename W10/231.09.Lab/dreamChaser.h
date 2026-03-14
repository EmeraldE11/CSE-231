/***********************************************************************
 * ship.h
 * Dream Chaser:
 ************************************************************************/

#pragma once

#include "position.h"
#include "velocity.h"
#include "direction.h"
#include "acceleration.h"
#include "uiDraw.h"
#include <cmath>
#include <vector>

class Ship : public Satellite
{
public:
   Ship();
   void draw(ogstream& gout) override;
};
