#include "../include/vector.h"
#include <iostream>

Vector::Vector(long double magnitude, long double theta)
{
    this->magnitude = magnitude;
    this->theta     = theta;
    //ctor
}

/*Returns the x component of the vector, marked const so
 *that the operator overload will not complain*/
long double Vector::getXComponent() const
{
    return cos(theta*(PI/180.0l))*magnitude;
}

/*Returns the y component of the vector, marked const so
 *that the operator overload will not complain*/
long double Vector::getYComponent() const
{
    return sin(theta*(PI/180.0l))*magnitude;
}

/*Returns the angle of vector being applied relative to the
 *horizontal, marked const so overload doesn't complain.*/
long double Vector::getTheta() const
{
    return theta;
}

/*Returns the magnitude of vector being applied relative to the
 *horizontal, marked const so overload doesn't complain.*/
long double Vector::getMagnitude() const
{
    return magnitude;
}

/*A vector plus a vector is simply equal to the sum of their components
 *and the new angle*/
Vector Vector::operator+ (const Vector &other)
{
    long double xComp    = this->getXComponent()+other.getXComponent();
    long double yComp    = this->getYComponent()+other.getYComponent();

    long double newTheta = atan2(yComp,xComp)*(180.0/PI);

    long double newMag   = sqrt(pow(xComp,2)+pow(yComp,2));

    return Vector(newMag,newTheta);
}

Vector::~Vector()
{
    //dtor
}
