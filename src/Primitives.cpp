/*
 * Primitive.cpp
 *
 *  Created on: Feb 19, 2009
 *      Author: njoubert
 *      Modified: sidch
 */

#include "Primitives.hpp"

Primitive::Primitive(RGB const & c, Material const & m, Mat4 const & modelToWorld)
{
  c_ = c;
  m_ = m;
  modelToWorld_ = modelToWorld;
  worldToModel_ = modelToWorld.inverse();
}

Primitive::~Primitive()
{
}

Sphere::Sphere(double radius, RGB const & c, Material const & m, Mat4 const & modelToWorld): Primitive(c, m, modelToWorld)
{
  r_ = radius;
}

bool
Sphere::intersect(Ray & ray) const
{
  // TODO for 3a
  //IMPLEMENT_ME(__FILE__, __LINE__);
	ray.transform(worldToModel_);
	Vec3 e = ray.start();
	Vec3 d = ray.direction();
	double min_t = ray.minT();

	ray.transform(modelToWorld_);

	double discriminant = (d*e)*(d*e) - (d*d)*(e*e - r_*r_);
	if(discriminant<0.0) {return false;}

	double pos_root = (1.0/(d*d))*(-d*e + sqrt(discriminant));
	double neg_root = (1.0/(d*d))*(-d*e - sqrt(discriminant));

	if(pos_root>0.0 && pos_root<ray.minT()) {ray.setMinT(pos_root);}

	if(neg_root>0.0 && neg_root<ray.minT()) {ray.setMinT(neg_root);}

	if(min_t>ray.minT()) {return true;}
	else {return false;}
}

Vec3
Sphere::calculateNormal(Vec3 const & position) const
{
  // TODO for 3a
  //IMPLEMENT_ME(__FILE__, __LINE__);
	Ray myRay;
	Vec3 start = position;
	Vec3 dir = -position;
	myRay = myRay.fromOriginAndDirection(start,dir);
	myRay.transform(worldToModel_);
	myRay = myRay.fromOriginAndDirection(myRay.start(),myRay.start());
	myRay.transform(modelToWorld_);
	return myRay.direction();
}

//=============================================================================================================================
// Triangle and other primitives are for Assignment 3b, after the midsem. Do not do this for 3a.
//=============================================================================================================================

Triangle::Triangle(Vec3 const & v0, Vec3 const & v1, Vec3 const & v2, RGB const & c, Material const & m,
				   Mat4 const & modelToWorld)
: Primitive(c, m, modelToWorld)
{
  verts[0] = v0;
  verts[1] = v1;
  verts[2] = v2;
}

bool
Triangle::intersect(Ray & ray) const
{
  // TODO for 3b, NOT 3a
  IMPLEMENT_ME(__FILE__, __LINE__);
}

Vec3
Triangle::calculateNormal(Vec3 const & position) const
{
  // TODO for 3b, NOT 3a
  IMPLEMENT_ME(__FILE__, __LINE__);
}
