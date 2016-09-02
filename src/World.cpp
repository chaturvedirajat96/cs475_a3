/*
 * World.cpp
 *
 *  Created on: Feb 19, 2009
 *      Author: njoubert
 *      Modified: sidch
 */

#include "World.hpp"

World::World()
{
}

World::~World()
{
  // TODO Auto-generated destructor stub
}

Primitive *
World::intersect(Ray & r) const
{
  //IMPLEMENT_ME(__FILE__, __LINE__);
	Primitive* intersection_primitive;
	double min_t = r.minT();
	int i, flag=0;

	for(i=0; i<primitives_.size(); i++)
	{
		if(primitives_[i]->intersect(r))
		{
			if(min_t>r.minT())
			{
				flag=1;
				intersection_primitive = primitives_[i];
				min_t = r.minT();
			}
		}
	}
	if(flag)
		return intersection_primitive;
	else return NULL;
}

void
World::addPrimitive(Primitive * p)
{
  primitives_.push_back(p);
}

void
World::addLight(Light * l)
{
  lights_.push_back(l);
}

void
World::setAmbientLightColor(RGB ambientColor)
{
  ambientLight_.setColor(ambientColor);
}

RGB
World::getAmbientLightColor() const
{
  return ambientLight_.getColor();
}

void
World::printStats() const
{
  std::cout << "World data:" << std::endl;
  std::cout << " primitives: " << primitives_.size() << std::endl;
  std::cout << " lights: " << lights_.size() << std::endl;
}
