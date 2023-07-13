//
//sprite.cpp
//

//C includes

//Dragonfly includes
#include "Color.h"
#include "Frame.h"
#include "LogManager.h"
#include "Sprite.h"

//default constructor
df::Sprite::Sprite() {
    m_width = 0;
    m_height = 0;
    m_label = "";
    m_frame_count = 0;
    m_frame = new Frame[5];
    m_max_frame_count = 0;
    m_color = COLOR_DEFAULT;
    m_slowdown = 1;
}

//special constructor - create sprite with indicated max frames
df::Sprite::Sprite(int max_frames) {
    m_width = 0;
    m_height = 0;
    m_label = "";
    m_frame_count = 0;
    m_frame = new Frame[max_frames];
    m_max_frame_count = max_frames;
    m_color = COLOR_DEFAULT;
    m_slowdown = 1;
}

//Destroy sprite, deleting any allocated frames
df::Sprite::~Sprite() {
    if (m_frame != NULL) {
        delete[]m_frame;
    }
}

/*
* Set width of sprite
*/
void df::Sprite::setWidth(int new_width) {
    m_width = new_width;
}

/*
* Get width of sprite
*/
int df::Sprite::getWidth() const {
    return m_width;
}

/*
* Set height of sprite
*/
void df::Sprite::setHeight(int new_height) {
    m_height = new_height;
}

/*
* Get height of sprite
*/
int df::Sprite::getHeight() const {
    return m_height;
}

/*
* Set color of sprite
*/
void df::Sprite::setColor(df::Color new_color) {
    m_color = new_color;
}

/*
* Get color of sprite
*/
df::Color df::Sprite::getColor() const {
    return m_color;
}

/*
* Get sprite frame count
*/
int df::Sprite::getFrameCount() const {
    return m_frame_count;
}

/*
* Get max frame count
*/
int df::Sprite::getMaxFrameCount() const {
    return m_max_frame_count;
}

/*
* Add frame to sprite
* Return 0 on a successful add
* Return -1 if frame array is full
*/
int df::Sprite::addFrame(df::Frame new_frame) {
    //Check to ensure the add won't go over the max frame count
    //If we won't exceed, add the frame
    LM.writeLog("draw plz");
    if (m_frame_count == m_max_frame_count) {
        LM.writeLog("ERROR: the sprite has reached its max frame count! Adding frames is impossible...");
        return -1;
    }
    else {
        LM.writeLog("frame count: %d", m_frame_count);
        LM.writeLog("m_frame_str: %s", new_frame.getString().c_str());
        m_frame[m_frame_count] = new_frame;
        m_frame_count++;
        
        return 0;
    }
}

/*
* Get next sprite frame indicated by number
* Return empty frame if our of range [0, m_frame_count - 1]
*/
df::Frame df::Sprite::getFrame(int frame_number) const {

    //Quickly check to make sure the frame is within the range of the frame number
    if ((frame_number < 0 || frame_number >= m_frame_count)) {
        Frame empty;
        return empty;
    }
    //LM.writeLog("frame number on error: %d", frame_number);
    //LM.writeLog("frame string on error: %s", m_frame[frame_number].getString().c_str());
    return m_frame[frame_number];
}

/*
* Set label associated with sprite
*/
void df::Sprite::setLabel(std::string new_label) {
    m_label = new_label;
}

/*
* Get label associated with sprite
*/
std::string df::Sprite::getLabel() const {
    return m_label;
}

/*
* Set animation slowdown value
* Valued in multiples of GameManager frame time
*/
void df::Sprite::setSlowdown(int new_sprite_slowdown) {
    m_slowdown = new_sprite_slowdown;
}

/*
* Get animation slowdown value
* Valued in multiples of GameManager frame time
*/
int df::Sprite::getSlowdown() const {
    return m_slowdown;
}

/*
* Draw indicated frame centered at position(x, y)
* Return 0 if ok, return -1 on fail
* NOTE: top-left coordinate is (0, 0)
*/
int df::Sprite::draw(int frame_number, df::Vector position) const {
    //LM.writeLog("frame number: %d", frame_number);
    //LM.writeLog("frame count: %d", m_frame_count);
    //check to see if frame_number is within sprite bounds
    if ((frame_number < 0 || frame_number >= m_frame_count)) {
        LM.writeLog("ERROR: the frame attempting to be drawn is out of bounds!");
        return -1;
    }

    //Call to Frame.draw for frame and position
    getFrame(frame_number).draw(position, m_color);
    return 0;
}