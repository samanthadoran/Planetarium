#ifndef OBJECT_H
#define OBJECT_H
#include <math.h>
#include <vector>
#include <string.h>
#include "force.h"

#include <SFML/Graphics.hpp>

class Object
{
    public:

        std::vector<Object*> modifiers;

        sf::CircleShape circle;

        double calcDist(Object) const;

        void addModifier(Object*);
        void updateValues();

        double calcVelocity(const double, const double);
        long double calcVelocityTheta(const long double, const long double);
        void modVelocity(Force);

        long double calcForce(Object) const;
        long double calcForceTheta(Object) const;

        Force sumForces(std::vector<Force>) const;

        void move();

        //Getter
        double getMass() const;
        double getRadius() const;
        std::string getName() const;
        long double getX() const;
        long double getY() const;

        //Setter
        void setMass(double);
        void setRadius(double);


        Object(std::string, double, double, long double, long double);
        virtual ~Object();
    protected:
    private:
        //Time factor
        const unsigned int t            = 10000;

        //1 million kilometers per pixel, we deal in meters so 1 million * 1 thousand = scale
        const unsigned int scale        = 1000000000;

        //The number we multiply velocity by when we are moving to make sure it only moves with reference to scale
        const long double velocityScale = 0.000000001;

        //Mass of the object measured in kilograms
        float mass;
        //Radius of the object, measured in million of kilometers
        double radius;

        long double x;
        long double y;

        std::string name;

        //The angle for velocity, in DEGREES
        long double theta;
        //Velocity, measured in meters per second
        long double velocity;
};

#endif // OBJECT_H
