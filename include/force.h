#ifndef FORCE_H
#define FORCE_H
#include <math.h>
#define PI 3.14159265359l


class Force
{
    public:
        long double getXComponent() const;
        long double getYComponent() const;

        long double getTheta() const;
        long double getMagnitude() const ;

        Force(long double, long double);
        virtual ~Force();

        Force operator+(const Force&);

    protected:
    private:
        long double theta;
        long double magnitude;
};

#endif // FORCE_H
