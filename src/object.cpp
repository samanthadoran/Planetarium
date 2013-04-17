#include "../include/object.h"
#include <iostream>

Object::Object(std::string name, double mass, double radius, long double x, long double y)
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

void Object::calcMomentum(const long double diffX, const long double diffY)
{
    long double mTheta = (atan2(diffY,diffX))*(180.0l/PI);
    long double magnitude = this->getMass()*sqrt(diffX*diffX + diffY*diffY);
    momentum = Vector(magnitude, mTheta);
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

Vector Object::calcForce(Object obj) const
{
    //Get the distance for use in the force equation
    long double distance = calcDist(obj);

    //FG = G*(M1*M2)/(r^2)
    long double magnitude = ((6.674*pow(10,-11)*(this->getMass()*obj.getMass()))/pow(distance,2));
    long double forceTheta = calcForceTheta(obj);

    return Vector(magnitude, forceTheta);
}

Vector Object::sumForces(std::vector<Vector> forces) const
{
    //Make an empty force to add to
    Vector tempForce(0.0,0.0l);

    for(Vector force: forces)
    {
        tempForce = tempForce + force;
    }

    return tempForce;
}

void Object::modMomentum(Vector force)
{
    //Get the components of our accel, make sure to multiply by 1000 for the scale.
    long double accel_x    = 1.0l*force.getXComponent()/(this->getMass()*1.0l);
    long double accel_y    = 1.0l*force.getYComponent()/(this->getMass()*1.0l);

    //Get the components of our velocity so as to modify them by our accel
    long double velocity_x = momentum.getXComponent()/(this->getMass()*1.0l);
    long double velocity_y = momentum.getYComponent()/(this->getMass()*1.0l);

    velocity_x             = velocity_x + accel_x*t;
    velocity_y             = velocity_y + accel_y*t;

    calcMomentum(velocity_x,velocity_y);
}

void Object::updateValues()
{
    //Make a vector to store our forces to be summed later
    std::vector<Vector> forces;

    //Get a vector of forces for every body our object might be modified by
    for(Object *x : modifiers)
    {
        forces.push_back(calcForce(*x));
    }

    //Add them up!
    Vector force = sumForces(forces);

    //Modify our momentum by our force
    modMomentum(force);
}

void Object::move()
{
    //Translate the object based upon our new momentum vector
    x += velocityScale*(momentum.getXComponent()/(this->getMass()*1.0l))*t;
    y += velocityScale*(momentum.getYComponent()/(this->getMass()*1.0l))*t;

    //Put our circle's center at (x,y)
    circle.setPosition(x-radius, y-radius);
}

bool Object::operator== (const Object &other)
{
    return (other.getName().compare(this->getName()) == 0);
}

Object::~Object()
{
    //dtor
}
