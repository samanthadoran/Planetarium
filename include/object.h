#ifndef OBJECT_H
#define OBJECT_H
#include <math.h>
#include <vector>
#include <string.h>
#include <iostream>
#include "vector.h"

#include <SFML/Graphics.hpp>

class Object
{
    public:

        sf::CircleShape circle;

        double calcDist(Object) const;

        void addModifier(Object*);
        void updateValues();

        void calcMomentum(const long double, const long double);
        void modMomentum(Vector);

        Vector calcForce(Object) const;
        long double calcForceTheta(Object) const;

        Vector sumForces(std::vector<Vector>) const;

        void move();

        //Getter
        long double getMass() const;
        long double getRadius() const;
        std::string getName() const;
        long double getX() const;
        long double getY() const;
        Vector getMomentum() const;

        //Setter
        void setMass(long double);
        void setRadius(long double);

        bool operator==(const Object&);

        Object(std::string, long double, long double, long double, long double);
        virtual ~Object();
    protected:
    private:
        //Time factor
        const unsigned int t            = 100;

        //1 million kilometers per pixel, we deal in meters so 1 million * 1 thousand = scale
        const unsigned int scale        = 1000000000;

        //The number we multiply velocity by when we are moving to make sure it only moves with reference to scale
        const long double velocityScale = 0.000000001l;

        //Mass of the object measured in kilograms
        long double mass;

        //Radius of the object, measured in millions of kilometers
        long double radius;

        //X,y of the object, represented in millions of kilometers
        long double x;
        long double y;

        //Used for displaying object selected and differentiating two objects
        std::string name;

        std::vector<Object*> modifiers;

        //Momentum, measured in kg*(m/s)
        Vector momentum;
};

#endif // OBJECT_H
