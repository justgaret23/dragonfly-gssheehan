#pragma once
//
//frame.h
//

//C includes
#include <string>

//Dragonfly includes
#include "Vector.h"
#include "Color.h"


namespace df {
    class Frame {
    private:
        int m_width;             //width of frame
        int m_height;            //height of frame
        std::string m_frame_str; //all frame characters stored as string

    public:

        //empty frame constructor
        Frame();

        //constructor for frame of indicated width and height with string
        Frame(int new_width, int new_height, std::string frame_str);

        //set width of frame
        void setWidth(int new_width);

        //get width of frame
        int getWidth() const;

        //set height of frame
        void setHeight(int new_height);

        //get height of frame
        int getHeight() const;

        //set frame characters (Stored as string)
        void setString(std::string new_frame_str);

        //get frame characters (stored as string)
        std::string getString() const;

        //Draw self, centered at position (x,y) with color
        //Return 0 if successful
        //Return -1 if failure
        //NOTE: top-left coordinate is (0, 0). Keep this in mind when drawing
        int draw(df::Vector position, df::Color color) const;

    };
}