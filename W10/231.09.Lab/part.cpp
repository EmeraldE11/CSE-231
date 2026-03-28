/***********************************************************************
 * part.cpp
 ************************************************************************/

#include "part.h"
#include "fragment.h"

Part::Part(const Satellite& parent, const Direction& kickDirection)
   : Satellite(parent, kickDirection)
{
   radius = 4.0;
   angularVelocity = 0.0;
}

void Part::draw(ogstream& gout)
{
   gout.drawFragment(position, direction.getRadians());
}

void Part::destroy(std::vector<Simulatable*>& satellites)
{
   if (dead) return;
   const int n = 2;
   for (int i = 0; i < n; i++)
   {
      double angle = direction.getRadians() + (2.0 * M_PI * i / n);
      Direction kick;
      kick.setRadians(angle);
      satellites.push_back(new Fragment(*this, kick));
   }
   kill();
}
