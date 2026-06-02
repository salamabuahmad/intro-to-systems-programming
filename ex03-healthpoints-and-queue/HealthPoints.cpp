#include <iostream>
#include "HealthPoints.h"

HealthPoints ::HealthPoints(int healthPoints)
{
    if (healthPoints <= 0) {
        throw InvalidArgument();
    }

    this -> m_maxHealthPoints = healthPoints;
    this -> m_healthPoints = healthPoints;
}

HealthPoints& HealthPoints :: operator+=(int healthAdded)
{
    if((healthAdded + m_healthPoints) >= m_maxHealthPoints)
    {
        m_healthPoints = m_maxHealthPoints;
    }

    else
    {
        m_healthPoints = m_healthPoints + healthAdded;
    }

    return *this;
}

HealthPoints& HealthPoints :: operator-=(int healthTaken)
{
    if((m_healthPoints - healthTaken) <= 0)
    {
        m_healthPoints = 0;
    }

    else
    {
        m_healthPoints = m_healthPoints - healthTaken;
    }

    return *this;
}


HealthPoints operator+(const HealthPoints& h1 ,int healthAdded)
{
    HealthPoints result = h1;
    result += healthAdded;
    return result;
}

HealthPoints operator+(int healthAdded , const HealthPoints& h1)
{
    return (h1 + healthAdded);
}

HealthPoints operator-(const HealthPoints& h1 ,int healthTaken)
{
    HealthPoints result = h1;
    result -= healthTaken;
    return result;
}

HealthPoints operator-(int healthTaken , const HealthPoints& h1)
{
    HealthPoints result =  HealthPoints(h1);
    result . m_healthPoints = healthTaken;
    return (result - h1.m_healthPoints);
}

bool operator ==(const HealthPoints& h1, const HealthPoints& h2)
{
    return h1.m_healthPoints == h2.m_healthPoints;
}

bool operator<(const HealthPoints& h1 , const HealthPoints& h2)
{
    return h1.m_healthPoints < h2.m_healthPoints;
}

bool operator>(const HealthPoints& h1 , const HealthPoints& h2)
{
    return (h1.m_healthPoints > h2.m_healthPoints);
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& h1)
{
    os << h1.m_healthPoints << "(" << h1.m_maxHealthPoints << ")";
    return os;
}


bool operator!=(const HealthPoints& h1 ,const HealthPoints& h2)
{
    return (!(h1 == h2));
}

bool operator<=(const HealthPoints& h1 ,const HealthPoints& h2)
{
    return (h1 < h2 || h1 == h2);
}

bool operator>=(const HealthPoints& h1 ,const HealthPoints& h2)
{
    return (h1 > h2 || h1 == h2);
}