#pragma once
//
// vector.h
// 

//conditional compilation
#ifndef VECTOR_H_SEEN
#define VECTOR_H_SEEN


namespace df {
    class Vector {
    private:
        float m_x; //vertical vector component
        float m_y; //horizontal vector component

    public:
        //Create vector with (x,y)
        Vector(float init_x, float init_y);

        //default 2d (x, y) is (0,0)
        Vector();

        //Get/set horizontal component
        void setX(float new_x);
        float getX() const;

        //Get/set vertical component
        void setY(float new_y);
        float getY() const;

        //Set horizontal AND vertical components
        void setXY(float new_x, float new_y);

        //get magnitude of vector
        float getMagnitude() const;

        //Normalize vector
        void normalize();

        //Scale vector by float a
        void scale(float a);

        //Add two vectors, return new vector
        Vector operator+(const Vector& other) const;

        //Subtract two vectors, return new vector
        Vector operator-(const Vector& other) const;

    };
}

#endif