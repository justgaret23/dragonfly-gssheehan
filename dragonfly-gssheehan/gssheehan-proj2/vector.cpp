//
// vector.cpp
// 

//C includes
#include <math.h>

//Dragonfly includes
#include "Vector.h"
#include "LogManager.h"


//constructor with manually inputted floats
df::Vector::Vector(float init_x, float init_y) {
    m_x = init_x;
    m_y = init_y;
}

//default constructor
df::Vector::Vector() {
    m_x = 0;
    m_y = 0;
}

/*
* Set x component of vector
*/
void df::Vector::setX(float new_x) {
    m_x = new_x;
}

/*
* Get x component of vector
*/
float df::Vector::getX() const {
    return m_x;
}

/*
* Set y component of vector
*/
void df::Vector::setY(float new_y) {
    m_y = new_y;
}

/*
* Get y component of vector
*/
float df::Vector::getY() const {
    return m_y;
}

/*
* Set both x and y components of vector
*/
void df::Vector::setXY(float new_x, float new_y) {
    m_x = new_x;
    m_y = new_y;
}

/*
* Get the magnitude of the vector
*/
float df::Vector::getMagnitude() const {
    float vecMagnitude = (float)sqrtf(pow(m_x, 2) + pow(m_y, 2));
    return vecMagnitude;
}

/*
* Normalize the vector
*/
void df::Vector::normalize() {
    float vectorLength = getMagnitude();
    if (vectorLength > 0) {
        m_x = m_x / vectorLength;
        m_y = m_y / vectorLength;
    }
    else {
        LM.writeLog("Normalizing failed! The vector's magnitude is not above zero.");
    }
}

/*
* Scale the vector according to float a
*/
void df::Vector::scale(float a) {
    m_x = m_x * a;
    m_y = m_y * a;
}

/*
* Add two vectors and return the new vector
*/
df::Vector df::Vector::operator+(const Vector& other) const {
    Vector vecSum; //create new vector

    //Add x and y components to the vector and return the sum
    vecSum.m_x = m_x + other.m_x;
    vecSum.m_y = m_y + other.m_y;
    return vecSum;
}

/*
* Subtract two vectors and return the new vector
*/
df::Vector df::Vector::operator-(const Vector& other) const {
    Vector vecSubtract; //create new vector

    //Add x and y components to the vector and return the sum
    vecSubtract.m_x = m_x - other.m_x;
    vecSubtract.m_y = m_y - other.m_y;
    return vecSubtract;
}