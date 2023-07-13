//
//animation.cpp
// 

//Dragonfly includes
#include "Animation.h"
#include "Box.h"
#include "LogManager.h"


/// Animation constructor
df::Animation::Animation() {
    m_index = 0;
    m_p_sprite = NULL;
    m_slowdown_count = 0;
}

/*
* Set associated Sprite to new one.
* Note, Sprite is managed by ResourceManager.
* Set Sprite index to 0 (first frame).
*/
void df::Animation::setSprite(Sprite* p_new_sprite) {
    m_p_sprite = p_new_sprite;
    setSlowdownCount(p_new_sprite->getSlowdown());
    setName(p_new_sprite->getLabel());
}

/*
* Return pointer to associated Sprite.
*/
df::Sprite* df::Animation::getSprite() const {
    return m_p_sprite;
}

/*
* Set Sprite name (in ResourceManager).
*/
void df::Animation::setName(std::string new_name) {
    m_name = new_name;
}

/*
* Get Sprite name (in ResourceManager).
*/
std::string df::Animation::getName() const {
    return m_name;
}

/*
* Set index of current Sprite frame to be displayed.
*/
void df::Animation::setIndex(int new_index) {
    m_index = new_index;
}

/*
* Get index of current Sprite frame to be displayed.
*/
int df::Animation::getIndex() const {
    return m_index;
}

/*
* Set animation slowdown count (-1 means stop animation).
*/
void df::Animation::setSlowdownCount(int new_slowdown_count) {
    m_slowdown_count = new_slowdown_count;
}

/*
* Set animation slowdown count (-1 means stop animation).
*/
int df::Animation::getSlowdownCount() const {
    return m_slowdown_count;
}

/*
* Draw single frame centered at position (x,y).
* Drawing accounts for slowdown, and advances Sprite frame.
* Return 0 if ok, else -1.
*/
int df::Animation::draw(df::Vector position) {

    //check to see if sprite is defined
    if (m_p_sprite == NULL) {
        LM.writeLog("Animation::draw ERROR: the sprite is not defined");
        return -1;
    }


    //Now, we ask the sprite to draw the current frame
    int index = getIndex();
    m_p_sprite[0].draw(index, position);


    //if slowdown count is -1, animation is frozen and return here
    if (getSlowdownCount() == -1) {
        return 0;
    }

    //increment the animation counter
    int count = getSlowdownCount();
    count++;

    //advance sprite index, if appropriate
    if (count >= getSprite()->getSlowdown()) {
        count = 0;

        index++;

        //if at last frame, loop to beginning
        if (index >= m_p_sprite->getMaxFrameCount()) {
            index = 0;
        }

        setIndex(index);
    }

    setSlowdownCount(count);

    return 0;
}

/*
* Get bounding box of appropriate sprite
*/
df::Box df::Animation::getBox() const {

    //if no sprite can be found, return the unit box centered at (0,0)
    //TODO: this assignment is unleashing plagues upon my home
    if (m_p_sprite == NULL) {
        LM.writeLog("WARNING: there is no sprite found. Is this intentional?");
        Box box(Vector(-0.5, -0.5), 0.99, 0.99);
        return box;
    }


    //Create box around centered sprite
    Vector corner(-1 * m_p_sprite->getWidth() / 2.0,
        -1 * m_p_sprite->getHeight() / 2.0);

    Box box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());

    //return box
    return box;
}