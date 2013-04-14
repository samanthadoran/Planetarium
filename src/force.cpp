#include "../include/force.h"
#include <iostream>
Force::Force(long double magnitude, long double theta)
{
    this->magnitude = magnitude;
    this->theta     = theta;
    //ctor
}

/*Returns the x component of the force, marked const so
 *that the operator overload will not complain*/
long double Force::getXComponent() const
{
    return cos(theta*(PI/180.0l))*magnitude;
}

/*Returns the y component of the force, marked const so
 *that the operator overload will not complain*/
long double Force::getYComponent() const
{
    return sin(theta*(PI/180.0l))*magnitude;
}

long double Force::getTheta() const
{
    return theta;
}

long double Force::getMagnitude() const
{
    return magnitude;
}

Force Force::operator+ (const Force &other)
{
    long double xComp    = this->getXComponent()+other.getXComponent();
    long double yComp    = this->getYComponent()+other.getYComponent();

    long double newTheta = atan2(yComp,xComp)*(180.0/PI);

    long double newMag   = sqrt(pow(xComp,2)+pow(yComp,2));

    return Force(newMag,newTheta);
}

Force::~Force()
{
    //dtor
}
