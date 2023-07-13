#pragma once
//
//sprite.h
//

//C includes
#include <string>

//Dragonfly includes
#include "Frame.h"

namespace df {
    class Sprite {
    private:
        int m_width;           //Sprite width
        int m_height;          //Sprite height
        int m_max_frame_count; //Max number of frames a sprite can have
        int m_frame_count;     //The actual number of frames a sprite has
        Color m_color;         //Optional color for entire sprite
        int m_slowdown;        //Animation slowdown (1 = no slowdown, 0 = stop!)
        Frame* m_frame;        //Array of frames
        std::string m_label;   //Text label to identify sprite
        Sprite();              //sprite always has one argument, the frame count
    public:
        //Destroy sprite, deleting any allocated frames
        ~Sprite();

        //Create sprite with indicated max frames
        Sprite(int max_frames);

        //Set width of sprite
        void setWidth(int new_width);

        //Get width of sprite
        int getWidth() const;

        //Set height of sprite
        void setHeight(int new_height);

        //Get height of sprite
        int getHeight() const;

        //Set color of sprite
        void setColor(Color new_color);

        //Get color of sprite
        Color getColor() const;

        //Get sprite frame count
        int getFrameCount() const;

        int getMaxFrameCount() const;

        //Add frame to sprite
        //Return 0 on a successful add
        //Return -1 if frame array is full
        int addFrame(Frame new_frame);

        //Get next sprite frame indicated by number
        //Return empty frame if our of range [0, m_frame_count - 1]
        Frame getFrame(int frame_number) const;

        //Set label associated with sprite
        void setLabel(std::string new_label);

        //Get label associated with sprite
        std::string getLabel() const;

        //Set animation slowdown value
        //Valued in multiples of GameManager frame time
        void setSlowdown(int new_sprite_slowdown);

        //Get animation slowdown value
        //Valued in multiples of GameManager frame time
        int getSlowdown() const;

        //Draw indicated frame centered at position(x, y)
        //Return 0 if ok, return -1 on fail
        //NOTE: top-left coordinate is (0, 0)
        int draw(int frame_number, Vector position) const;

    };
}
