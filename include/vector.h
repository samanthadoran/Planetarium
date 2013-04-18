#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#define PI acos(-1.0l)

class Vector
{
    public:
        long double getXComponent() const;
        long double getYComponent() const;

        long double getTheta() const;
        long double getMagnitude() const ;

        Vector(long double, long double);
        Vector();
        virtual ~Vector();

        Vector operator+(const Vector&);

    protected:
    private:
        //Angle, measured in DEGREES
        long double theta;
        long double magnitude;
};

#endif // VECTOR_H
