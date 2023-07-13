///
///viewobject.cpp
///

//C includes
#include <string>

//Dragonfly includes
#include "DisplayManager.h"
#include "EventView.h"
#include "LogManager.h"
#include "ViewObject.h"
#include "WorldManager.h"
#include "utility.h"

/// Construct ViewObject. 
/// Object settings: SPECTRAL, max altitude.
/// ViewObject defaults: border, top_center, default color, draw_value.
df::ViewObject::ViewObject(){
    //initialize object attributes
    setSolidness(SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);
    setType("ViewObject");

    //init viewobject attributes
    setValue(0);
    getDrawValue();
    setBorder(true);
    setLocation(TOP_CENTER);
    setColor(COLOR_DEFAULT);

    //TODO: registerinterest
}

/*
* Draw view string (and value).
* Return 0 if ok, negative if not.
*/
int df::ViewObject::draw() {
    std::string temp_str;
    if (m_border) {
        temp_str = "| " + getViewString() + " " + toString(m_value) + " |";
    }
    else {
        temp_str = getViewString() + " " + toString(m_value);
    }
    

    //draw centered at position
    Vector pos = viewToWorld(getPosition());
    //LM.writeLog("viewobject pos x: %f", pos.getX());
    //LM.writeLog("viewobject pos y: %f", pos.getY());
    DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());
    //Draw horizontal box components

    //Draw horizontal box lines
    std::string dash_str = "";
    for (int i = 1; i < temp_str.length() - 1; i++) {
        dash_str.append("-");
    }
    if (m_border) {
        DM.drawString(Vector(pos.getX(), pos.getY() - 1), dash_str, CENTER_JUSTIFIED, getColor());
        DM.drawString(Vector(pos.getX(), pos.getY() + 1), dash_str, CENTER_JUSTIFIED, getColor());
    }
    

    //DM.drawCh(Vector(pos.getX() - pos.getX() / 10, pos.getY()), '|', getColor());
    //DM.drawCh(Vector(pos.getX() + pos.getX() / 10, pos.getY()), '|', getColor());

    if (m_border) {

    }

    return 0;
}

/*
* Handle "view" event if tag matches view_string (others ignored).
* Return 0 if ignored, else 1.
*/
int df::ViewObject::eventHandler(const Event* p_e){
    if (p_e->getType() == df::VIEW_EVENT) {
        const EventView* p_ve = static_cast<const EventView*>(p_e);
        
        //Check to see if the event is meant for this object
        if (p_ve->getTag() == getViewString()) {
            if (p_ve->getDelta()) {
                setValue(getValue() + p_ve->getValue());
            }
            else {
                setValue(p_ve->getValue());
            }

            //If we reached here, the event was handled successfully
            return 0;
        }
        return 0;
    }
    //If we reached here, something went wrong...
    LM.writeLog("VO::eventHandler ERROR: EventView was not handled properly");
    return -1;
}

/*
* Set general location of ViewObject on screen.
*/
void df::ViewObject::setLocation(ViewObjectLocation new_location){
        Vector p = Vector();
        int y_delta = 0;
        switch (new_location)
        {
        //set new position based on location
        case TOP_LEFT:
                p.setXY((float)WM.getView().getHorizontal() * ((float)1 / 6), (float)1);
                if(!getBorder()){
                        y_delta = -1;
                }
                break;
        case TOP_CENTER:
            LM.writeLog("burned view: %f", WM.getView().getHorizontal());
                p.setXY((float)WM.getView().getHorizontal() * ((float)3 / 6), (float)1);
                if(!getBorder()){
                        y_delta = -1;
                }
                break;
        case TOP_RIGHT:
                p.setXY((float)WM.getView().getHorizontal() * ((float)5 / 6), (float)1);
                if(!getBorder()){
                        y_delta = -1;
                }
                break;
        case BOTTOM_LEFT:
                p.setXY((float)WM.getView().getHorizontal() * ((float)1 / 6), (float)WM.getView().getVertical() - (float)1);
                if(!getBorder()){
                        y_delta = 1;
                }
                break;
        case BOTTOM_CENTER:
                p.setXY((float)WM.getView().getHorizontal() * ((float)3 / 6), (float)WM.getView().getVertical() - (float)1);
                if(!getBorder()){
                        y_delta = 1;
                }
                break;
        case BOTTOM_RIGHT:
                p.setXY((float)WM.getView().getHorizontal() * ((float)5 / 6), (float)WM.getView().getVertical() - (float)1);
                if(!getBorder()){
                        y_delta = 1;
                }
                break;
        }
        //Shift viewobject as needed based on border
        if (y_delta == -1) {
            p.setY(1);
        } else if (y_delta == 1) {
            p.setY((float)WM.getView().getVertical() - (float)1);
        }
        

        //set position of object to new position
        setPosition(p);

        //set new location
        m_location = new_location;
}

/*
* Get general location of ViewObject on screen.
*/
df::ViewObjectLocation df::ViewObject::getLocation() const{
    return m_location;
}

/*
* Set true to draw value with display string.
*/
void df::ViewObject::setDrawValue(bool new_draw_value) {
    m_draw_value = new_draw_value;
}

/*
* Get draw value (true if draw value with display string).
*/
bool df::ViewObject::getDrawValue() const{
    return false;
}

/*
* Set view value.
*/
void df::ViewObject::setValue(int new_value){
    m_value = new_value;
}

/*
* Get view value.
*/
int df::ViewObject::getValue() const{
    return m_value;
}

/*
* Set view border (true = display border).
*/
void df::ViewObject::setBorder(bool new_border){
    if (m_border != new_border) {
        //reset location to account for border setting
        m_border = new_border;
        setLocation(getLocation());
    }
}

/*
* Get view border (true = display border).
*/
bool df::ViewObject::getBorder() const{
    return m_border;
}

/*
* Set view color.
*/
void df::ViewObject::setColor(Color new_color){
    m_color = new_color;
}

/*
* Get view color.
*/
df::Color df::ViewObject::getColor() const{
    return m_color;
}

/*
* Set view display string.
*/
void df::ViewObject::setViewString(std::string new_view_string){
    m_view_string = new_view_string;
}

/*
* Get view display string.
*/
std::string df::ViewObject::getViewString() const{
    return m_view_string;
}