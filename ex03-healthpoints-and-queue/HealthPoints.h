#ifndef HW4_HEALTHPOINTS_H
#define HW4_HEALTHPOINTS_H
#include <iostream>

class HealthPoints{
private:
    int m_healthPoints;
    int m_maxHealthPoints;

    friend bool operator==(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator<(const HealthPoints& h1 , const HealthPoints& h2);
    friend bool operator>(const HealthPoints& h1 , const HealthPoints& h2);
    friend HealthPoints operator-(int healthTaken , const HealthPoints& h1);
    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& h1);


public:
    HealthPoints(int healthPoints = 100);

    HealthPoints& operator+=(int healthAdded);
    HealthPoints& operator-=(int healthTaken);
    HealthPoints& operator=(const HealthPoints&) = default;

    class InvalidArgument {};

};

HealthPoints operator+(const HealthPoints& h1 , int healthAdded);
HealthPoints operator+(int healthAdded , const HealthPoints& h1);
HealthPoints operator-(const HealthPoints& h1 , int healthTaken);
HealthPoints operator-(int healthTaken , const HealthPoints& h1);
bool operator!=(const HealthPoints& h1 ,const HealthPoints& h2);
bool operator<=(const HealthPoints& h1 ,const HealthPoints& h2);
bool operator>=(const HealthPoints& h1 ,const HealthPoints& h2);

#endif //HW4_HEALTHPOINTS_H