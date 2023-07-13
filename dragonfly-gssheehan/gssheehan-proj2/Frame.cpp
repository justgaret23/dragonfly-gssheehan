//
//frame.cpp
//

//Dragonfly includes
#include "DisplayManager.h"
#include "Frame.h"
#include "LogManager.h"
#include "Vector.h"


//empty frame constructor
df::Frame::Frame() {
    m_width = 0;
    m_height = 0;
    m_frame_str = "";
}

//constructor for frame of indicated width and height with string
df::Frame::Frame(int new_width, int new_height, std::string frame_str) {
    m_width = new_width;
    m_height = new_height;
    m_frame_str = frame_str;
}

/*
* set width of frame
*/
void df::Frame::setWidth(int new_width) {
    m_width = new_width;
}

/*
* get width of frame
*/
int df::Frame::getWidth() const {
    return m_width;
}

/*
* set height of frame
*/
void df::Frame::setHeight(int new_height) {
    m_height = new_height;
}

/*
* get height of frame
*/
int df::Frame::getHeight() const {
    return m_height;
}

/*
* set frame characters (Stored as string)
*/
void df::Frame::setString(std::string new_frame_str) {
    m_frame_str = new_frame_str;
}

/*
* get frame characters (stored as string)
*/
std::string df::Frame::getString() const {
    return m_frame_str;
}

/*
* Draw self, centered at position (x,y) with color
* Return 0 if successful
* Return -1 if failure
* NOTE: top-left coordinate is (0, 0). Keep this in mind when drawing
*/
int df::Frame::draw(df::Vector position, df::Color color) const {
    //Error check empty string
    //TODO: this could be bad and dumb?
    if (m_width == 0 && m_height == 0) {
        LM.writeLog("ERROR: The current frame is empty, you can't draw!");
        return -1;
    }

    //Determine offset of sprite, as it is centered at the position
    //TODO: ask if this is fine idk I might be overthinking
    int x_offset = getWidth() / 2;
    int y_offset = getHeight() / 2;

    //Draw the frame character by character

    for (int y_coord = 0; y_coord < m_height; y_coord++) {
        for (int x_coord = 0; x_coord < m_width; x_coord++) {

            //Get character position, and then draw!
            Vector temp_pos(position.getX() + x_coord - x_offset,
                position.getY() + y_coord - y_offset);

            //use getter, not direct
            DM.drawCh(temp_pos, m_frame_str[(y_coord * m_width) + x_coord], color);
        }
    }
}