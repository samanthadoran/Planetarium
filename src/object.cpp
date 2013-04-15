#include "../include/object.h"
#include <iostream>

Object::Object(std::string name,double mass, double radius, long double x, long double y)
{
    this->name   = name;
    this->mass   = mass;
    this->radius = radius;
    this->x      = x;
    this->y      = y;
    circle.setRadius(this->radius);
    circle.setPosition(x-radius, y-radius);
}
//Getter setters
double Object::getMass() const
{
    return mass;
}

double Object::getRadius() const
{
    return radius;
}

std::string Object::getName() const
{
    return name;
}

void Object::setMass(double mass)
{
    if(mass > 0.0)
    {
        this->mass = mass;
    }
}

long double Object::getX() const
{
    return x;
}

long double Object::getY() const
{
    return y;
}

void Object::setRadius(double radius)
{
    this->radius = radius;
    circle.setRadius(radius);
}
//Calculate the theta at which velocity is going
long double Object::calcVelocityTheta(const long double diffX, const long double diffY)
{
    theta = (atan2(y,x)*(180.0/PI));

    return  (atan2(diffY,diffX)*(180.0/PI));
}

//Calculate our new velocity
double Object::calcVelocity(const double diffX, const double diffY)
{
    velocity = (sqrt(pow(diffY,2) + pow(diffX,2)));
    calcVelocityTheta(diffX,diffY);

    return (sqrt(pow(diffY,2) + pow(diffX,2)));
}

//Get the distance between two objects
double Object::calcDist(Object other) const
{
    return sqrt(pow((this->getY()*scale-other.getY()*scale),2)+pow((this->getX()*scale-other.getX()*scale),2));
}

//Add a planetary modifier to the vector
void Object::addModifier(Object * obj)
{
    modifiers.push_back(obj);
}

long double Object::calcForceTheta(Object other) const
{
    //Difference in x and y to use in atan2
    long double diffY = other.getY()*scale-this->getY()*scale;
    long double diffX = other.getX()*scale-this->getX()*scale;
    return (atan2(diffY, diffX)*(180.0l/PI));
}

long double Object::calcForce(Object obj) const
{
    //Get the distance for use in the force equation
    long double distance = calcDist(obj);

    //FG = G*(M1*M2)/(r^2)
    return ((6.674*pow(10,-11)*(this->getMass()*obj.getMass()))/pow(distance,2));
}

Force Object::sumForces(std::vector<Force> forces) const
{
    //Make an empty force to add to
    Force tempForce(0.0,0.0l);

    for(Force force: forces)
    {
        tempForce = tempForce + force;
    }

    return tempForce;
}

void Object::modVelocity(Force accel)
{
    //Get the components of our accel, make sure to multiply by 1000 for the scale.
    long double accel_x    = 1.0l*accel.getXComponent()/(this->getMass()*1.0l);
    long double accel_y    = 1.0l*accel.getYComponent()/(this->getMass()*1.0l);

    //Get the components of our velocity so as to modify them by our accel
    long double velocity_x = velocity*cos(theta*(PI/180.0l));
    long double velocity_y = velocity*sin(theta*(PI/180.0l));

    //Velocity final=Velocity initial + acceleration*t
    velocity_x             = velocity_x + accel_x*t;
    velocity_y             = velocity_y + accel_y*t;

    velocity               = calcVelocity(velocity_x,velocity_y);

    theta                  = calcVelocityTheta(velocity_x,velocity_y);
}
void Object::updateValues()
{
    //Make a vector to store our forces to be summed later
    std::vector<Force> forces;

    //Get a vector of forces for every body our object might be modified by
    for(Object *x : modifiers)
    {
        long double magnitude = calcForce(*x);
        long double theta = calcForceTheta(*x);

        Force newForce(magnitude, theta);

        forces.push_back(newForce);
    }
    //Add them up!
    Force force = sumForces(forces);

    //Modify our velocity by our force
    modVelocity(force);
}

void Object::move()
{
    //Translate the object based upon our new velocity vector
    x += velocityScale*velocity*cos(theta*(PI/180.0l))*t;
    y += velocityScale*velocity*sin(theta*(PI/180.0l))*t;

    circle.setPosition(x-radius, y-radius);
}

Object::~Object()
{
    //dtor
}
