/*
 * Lights.cpp
 *
 *  Created on: Feb 19, 2009
 *      Author: njoubert
 *      Modified: sidch
 */

#include "Lights.hpp"

Light::Light()
{
  RGB black(0, 0, 0);
  illumination_ = black;
  falloff_ = 0;
  angular_falloff_ = 0;
  dead_distance_ = 1;
}

Light::Light(RGB const & illumination)
{
  illumination_ = illumination;
}

Light::Light(RGB const & illumination, double falloff, double dead_distance)
{
  illumination_ = illumination;
  falloff_ = falloff;
  dead_distance_ = dead_distance;
}

Light::~Light()
{}

RGB Light::getColor() const
{
  return illumination_;
}

RGB Light::getColor(Vec3 const & p) const
{
  return illumination_;
}

void
Light::setColor(RGB const & c)
{
  illumination_ = c;
}

AmbientLight::AmbientLight()
{
  // intentionally empty
}

AmbientLight::AmbientLight(RGB const & illumination) : Light(illumination)
{
  // intentionally empty
}

Vec3
AmbientLight::getIncidenceVector(Vec3 const & position) const
{
  throw "AMBIENT LIGHTS DO NOT HAVE A SENSE OF DIRECTION OR POSITION`";
}

Ray AmbientLight::getShadowRay(Vec3 const & position, bool & use_dist) const
{
  throw "AMBIENT LIGHTS DO NOT HAVE A SENSE OF DIRECTION OR POSITION";
}

PointLight::PointLight(RGB const & illumination) : Light(illumination)
{
  // intentionally empty
}

PointLight::PointLight(RGB const & illumination, double falloff, double dead_distance)
: Light(illumination, falloff, dead_distance)
{
  // intentionally empty
}

RGB
PointLight::getColor(Vec3 const & p) const
{
  // TODO for 3a
  //IMPLEMENT_ME(__FILE__, __LINE__);
 	double dist = (p-pos_).length();                                             	// calculate distance of point at which color is required
 	double scaling_factor = 1.0/pow((dist+dead_distance_),falloff_);			// calculate the scaling factor
 	return illumination_*scaling_factor;
}

void
PointLight::setPosition(Vec3 const & pos)
{
  pos_ = pos;
}

Vec3
PointLight::getIncidenceVector(Vec3 const & position) const
{
  // TODO for 3a
  //IMPLEMENT_ME(__FILE__, __LINE__);
	return (pos_-position).normalize();			// return normalized vector from point to source
}

Ray
PointLight::getShadowRay(Vec3 const & position, bool & use_dist) const
{
  // TODO for 3a
  //IMPLEMENT_ME(__FILE__, __LINE__);
	Vec3 e = position;											// set origin of ray
	Vec3 d = (pos_ - position);									// set direction of ray
	use_dist = true;											// use_dist = true
	Ray myRay;
	return myRay.fromOriginAndDirection(e,d);
}

DirectionalLight::DirectionalLight(RGB const & illumination) : Light(illumination)
{
  // intentionally empty
}

void
DirectionalLight::setDirection(Vec3 const & dir)
{
  dir_ = dir;
  dir_.normalize();
}

Vec3
DirectionalLight::getIncidenceVector(Vec3 const & position) const
{
  // TODO for 3a
  //IMPLEMENT_ME(__FILE__, __LINE__);
	return -dir_;
}

Ray
DirectionalLight::getShadowRay(Vec3 const & position, bool & use_dist) const
{
  // TODO for 3a
  //IMPLEMENT_ME(__FILE__, __LINE__);
	Vec3 e = position;											// set origin of ray
	Vec3 d = -dir_;									// set direction of ray
	use_dist = false;											// use_dist = true
	Ray myRay;
	return myRay.fromOriginAndDirection(e,d);
}
