//System includes
#include <SFML/Graphics.hpp>
#include <Windows.h>

//Dragonfly includes
#include "Box.h"
#include "Clock.h"
#include "DisplayManager.h"
#include "Frame.h"
#include "GameManager.h"
#include "LogManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "WorldManager.h"
#include "Vector.h"
#include "ViewObject.h"

//Global manager variables
//The order of these matter! 
//LogManager is needed before most because other managers write on startup
//df::DisplayManager display_manager;
df::LogManager &log_manager = df::LogManager::getInstance();
df::GameManager &game_manager = df::GameManager::getInstance();
df::WorldManager &world_manager = df::WorldManager::getInstance();

#define TARGET_TIME 33000 //target frame time in microseconds

//Stubs
void logTests();
void clockTests(df::Clock clock);
void vecTests();
void objectTests();
void objectListTests();
bool dmTests();
bool frameSpriteTests();
bool animationTests();
bool boxTests();
bool compareFloats(float fl1, float fl2);
int sfmlHelloWorld(sf::Font font);
void loadResources(void);


bool intTest(std::string testName, int parameter1, int parameter2);
bool boolTest(std::string testName, bool parameter1, bool parameter2);
bool stringTest(std::string testName, std::string parameter1, std::string parameter2);


int main()
{
    //Define clock and start up
    df::Clock clock;


    GM.startUp();

    //set game world boundaries
    df::Vector corner(0, 0);
    df::Box world_boundary(corner, 80, 50);
    WM.setBoundary(world_boundary);

    //set game world view
    df::Box view(corner, 80, 24);
    WM.setView(view);

    loadResources();

    //Preliminary test cases
    logTests();
    //clockTests(clock);
    vecTests();
    //objectTests();
    //objectListTests();
    dmTests();
    frameSpriteTests();
    animationTests();
    boxTests();
    
    //primary game loop
    GM.run();

    //Shut down all managers
    GM.shutDown();
    LM.shutDown();

    return 0;
}

void loadResources(void) {

    //sprites
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
    RM.loadSprite("sprites/ship-spr.txt", "ship");

    //sound
    RM.loadSound("sounds/fire.wav", "fire");
    RM.loadSound("sounds/explode.wav", "explode");

    //music
    RM.loadMusic("sounds/start-music.wav", "start music");
}

/*
Tests for the game engine logger
*/
void logTests() {
    //Write normal log
    LM.writeLog("Test 1");

    //Write string log
    LM.writeLog("Test %s", "two");

    //write decimal log
    LM.writeLog("Test %d", 3);

    //write float log
    LM.writeLog("Test %f", 3.5);

    //combine all of the above
    LM.writeLog("Test 1, %s, %d, and %f all work!", "two", 3, 3.5);
}

/*
Tests for the game engine clock
*/
void clockTests(df::Clock clock) {
    LM.writeLog("*** Testing Clock class... ***");

    //Initial parameters so tests can easily be altered later
    long int max_millisecond_difference = 30000;
    long int sleep_time_microseconds = 1000000;
    long int sleep_time_milliseconds = 1000;

    //Sleep and record time. 
    //Delta resets the timer one second in, while split records a one-second interval from the reset.
    Sleep(sleep_time_milliseconds);
    long int splitTime = clock.delta();
    Sleep(sleep_time_milliseconds);
    long int elapsedTime = clock.split();

    //Test split
    if ((splitTime - sleep_time_microseconds) < max_millisecond_difference) {
        LM.writeLog("Split time is under 30 milliseconds off!");
    }

    //Test elapsed
    if ((elapsedTime - sleep_time_microseconds) < max_millisecond_difference) {
        LM.writeLog("Elapsed time is under 30 milliseconds off!");
    }
}

/*
Tests for the game engine vector
*/
void vecTests() {

    LM.writeLog("*** Testing Vector class... ***");

    //Test default constructor
    df::Vector* testZeroVector = new df::Vector();
    if (testZeroVector->getX() == 0 && testZeroVector->getY() == 0) {
        LM.writeLog("Zero constructor passes!");
    }

    //Test making a vector with inputted floats
    df::Vector* testVector = new df::Vector(1, 1);
    if (testVector->getX() == 1 && testVector->getY() == 1) {
        LM.writeLog("Written constructor passes!");
    }

    //Test setX
    testVector->setX(2);
    if (testVector->getX() == 2) {
        LM.writeLog("setX passes!");
    }

    //Test setY
    testVector->setY(2);
    if (testVector->getY() == 2) {
        LM.writeLog("setY passes!");
    }

    //Test setXY
    testVector->setXY(3, 3);
    if (testVector->getX() == 3 && testVector->getY() == 3) {
        LM.writeLog("setXY passes!");
    }

    //Test scale
    testVector->scale(2);
    if (testVector->getX() == 6 && testVector->getY() == 6) {
        LM.writeLog("scale passes!");
    }

    //Test normalize
    df::Vector* ezNormalizeVector = new df::Vector(3, 4);
    ezNormalizeVector->normalize();
    if (compareFloats(ezNormalizeVector->getX(), (float)0.6) && compareFloats(ezNormalizeVector->getY(), (float)0.8)) {
        LM.writeLog("normalize passes!");
    }
    else {
        LM.writeLog("Actual normalized x: %f", ezNormalizeVector->getX());
        LM.writeLog("Actual normalized y: %f", ezNormalizeVector->getY());
    }

    //Test compare floats to prove that it works
    float testFloat = 2.0;
    if (compareFloats(testFloat, 2.0)) {
        LM.writeLog("compareFloats works as expected!");
    }

    //Test if normalize fails under the right circumstances

    //TODO: Test vector adder

}

/*
* Helper function that compares floats
*/
bool compareFloats(float fl1, float fl2) {
    if (fabs(fl1 - fl2) < 0.001) {
        return true;
    }
    else {
        return false;
    }
}

/*
* Tests for the game engine objects
* World manager count and removal are also tested
*/
void objectTests() {
    LM.writeLog("*** Testing Object class... ***");

    //Test default constructor
    df::Object* testObject1 = new df::Object();
    if (testObject1->getId() == 0 && 
        testObject1->getPosition().getX() == 0 && 
        testObject1->getPosition().getY() == 0 &&
        testObject1->getType() == "default_type") {
        LM.writeLog("Object initialization works as expected!");
    }

    //Test setID and getId
    testObject1->setId(20);
    if (testObject1->getId() == 20) {
        LM.writeLog("Object SetID works!");
    }

    //Test setType and getType
    testObject1->setType("test");
    if (testObject1->getType() == "test") {
        LM.writeLog("Object SetType works!");
    }

    //Test setPosition and getPosition
    testObject1->setPosition(df::Vector(2, 2));
    if (testObject1->getPosition().getX() == 2 &&
        testObject1->getPosition().getY() == 2) {
        LM.writeLog("Object setPosition works!");
    }

    //Test to see if WM adding works
    if (WM.getAllObjects().getcount() == 1) {
        LM.writeLog("The object was successfully added to the world!");
    }

    //Test to see if WM removal works
    WM.removeObject(testObject1);
    if (WM.getAllObjects().getcount() == 0) {
        LM.writeLog("The object was successfully removed from the world!");
    }
}

/*
* Tests for the game engine object list and world manager
* markForDelete is also tested here, though its success isn't known until the game loop begins
*/
void objectListTests() {
    df::ObjectList* testList = new df::ObjectList();
    df::ObjectListIterator liTest(testList);

    //Test default constructor
    if (testList->getcount() == 0) {
        LM.writeLog("Default initialization works!");
    }

    //test insert. We insert dummy objects to make sure that the iterator works as intended
    df::Object* dummy1 = new df::Object;
    df::Object* testObject = new df::Object;
    df::Object* dummy2 = new df::Object;
    df::Object* dummy3 = new df::Object;
    testObject->setId(20);
    testObject->setType("test");
    testObject->setPosition(df::Vector(3, 3));
    testList->insert(dummy1);
    testList->insert(testObject);
    testList->insert(dummy2);
    testList->insert(dummy3);
    if (testList->getcount() == 4) {
        LM.writeLog("The list has acknowledged the first batch of additions!");
    }

    //See if World Manager has acknowledged an addition
    //If this works, this means that WM.inse
    if (WM.getAllObjects().getcount() == 4) {
        LM.writeLog("WM.insertObject works!");
    }
    else {
        LM.writeLog("FAIL: there are %d objects in the world", WM.getAllObjects().getcount());
    }

    //See if an object with the assigned parameters can be found among the dummies
    for (liTest.first(); !liTest.isDone(); liTest.next()) {
        if (liTest.currentObject()->getId() == 20 && 
            liTest.currentObject()->getType() == "test" &&
            liTest.currentObject()->getPosition().getX() == 3 &&
            liTest.currentObject()->getPosition().getY() == 3){
            LM.writeLog("The object has the correct parameters!");
        }
    }

    //See if objectsOfType is working properly
    if (WM.objectsOfType("test").getcount() == 1) {
        LM.writeLog("objectsOfType is working properly!");
    }
    else {
        LM.writeLog("FAIL: There are %d objects of type test in the world.", WM.objectsOfType("test").getcount());
    }
    

    //test remove and isEmpty
    //test isEmpty (should fail here)
    if (!testList->isEmpty()) {
        LM.writeLog("isEmpty returns false here as expected");
    }
    testList->remove(testObject);
    testList->remove(dummy1);
    testList->remove(dummy2);
    testList->remove(dummy3);
    WM.removeObject(testObject);
    WM.removeObject(dummy1);
    WM.removeObject(dummy2);
    WM.removeObject(dummy3);
    if (testList->getcount() == 0 && WM.getAllObjects().getcount() == 0) {
        LM.writeLog("The list has acknowledged the first batch of removals!");
    }

    //test isEmpty (should succeed here)
    if (testList->isEmpty()) {
        LM.writeLog("isEmpty returns true here as expected");
    }

    //test clear
    df::Object* testObject2 = new df::Object;
    df::Object* testObject3 = new df::Object;
    df::Object* testObject4 = new df::Object;
    df::Object* testObject5 = new df::Object;
    testList->insert(testObject2);
    testList->insert(testObject3);
    testList->insert(testObject4);
    testList->insert(testObject5);

    //check to see if repeated inserts work
    if (WM.getAllObjects().getcount() == 4) {
        LM.writeLog("The world manager has acknowledged consecutive additions!");
    }

    //test clear proper
    testList->clear();
    if (testList->getcount() == 0) {
        LM.writeLog("The list has successfully been cleared!");
    }

    if (!testList->isFull()) {
        LM.writeLog("isFull returns false here as expected");
    }

    //Test isFull
    for (int i = 0; i < 1000; i++) {
        testList->insert(testObject2);
    }
    LM.writeLog("Count: %d", testList->getcount());
    if (testList->isFull()) {
        LM.writeLog("isFull returns true here as expected");
    }

    //re-clear list in preparation for game
    testList->clear();

    //Mark all testObjects for delete when the game loop begins
    WM.markForDelete(testObject4);
    WM.markForDelete(testObject2);
    WM.markForDelete(testObject3);
    WM.markForDelete(testObject5);
}

//Test to ensure sfml is working as intended
int sfmlHelloWorld(sf::Font font) {
    sf::Text testText;

    //Set text attributes
    testText.setFont(font); //font
    testText.setString("based gaming"); //string
    testText.setCharacterSize(32); //character size
    testText.setFillColor(sf::Color::Green); //fill color
    testText.setStyle(sf::Text::Bold); //style
    testText.setPosition(96, 134); //position

    //Create window to draw on
    sf::RenderWindow* p_window = new sf::RenderWindow(sf::VideoMode(400, 300), "SFML - Hello World!");
    if (!p_window) {
        LM.writeLog("ERROR: unable to allocate RenderWindow");
    }

    //Make mouse cursor invisible
    p_window->setMouseCursorVisible(false);

    //Synchronize refresh rate with monitor
    p_window->setVerticalSyncEnabled(true);

    //Repeat this loop until we murder death kill the window
    while (1) {

        //Clear window and draw text
        p_window->clear();
        p_window->draw(testText);
        p_window->display();

        //Check if window has been closed
        sf::Event event;
        while (p_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                p_window->close();
                delete p_window;
                return 0;
            }
        }
    }
}

bool dmTests() {
    //test horizontal
    if (!intTest("getHorizontal()", DM.getHorizontal(), WINDOW_HORIZONTAL_CHARS_DEFAULT)) {
        return false;
    }

    //test vertical
    if (!intTest("getVertical()", DM.getVertical(), WINDOW_VERTICAL_CHARS_DEFAULT)) {
        return false;
    }

    LM.writeLog("****All Display Manager Tests have passed!****");
    return true;
}

bool frameSpriteTests() {
    df::Frame* testFrame = new df::Frame(3, 2, ">-");
    //get width
    if (!intTest("getWidth()", 3, testFrame->getWidth())) {
        return false;
    }

    //set width
    testFrame->setWidth(2);
    if (!intTest("setWidth()", 2, testFrame->getWidth())) {
        return false;
    }

    //get height
    if (!intTest("getHeight()", 2, testFrame->getHeight())) {
        return false;
    }

    //set height
    testFrame->setHeight(1);
    if (!intTest("setHeight()", 1, testFrame->getHeight())) {
        return false;
    }

    //get string
    if (!stringTest("getString()", ">-", testFrame->getString())) {
        return false;
    }

    df::Sprite* testSprite = new df::Sprite(2);
    testSprite->setLabel("fsTest");
    //get/set label
    if (!stringTest("getLabel()", "fsTest", testSprite->getLabel())) {
        return false;
    }

    //get max frame count
    if (!intTest("getMaxFrameCount()", 2, testSprite->getMaxFrameCount())) {
        return false;
    }

    //get frame count
    if (!intTest("getFrameCount() before add", 0, testSprite->getFrameCount())) {
        return false;
    }

    //test adding frames
    testSprite->addFrame(*testFrame);
    testSprite->addFrame(*testFrame);
    if (!intTest("getFrameCount() after add", 2, testSprite->getFrameCount())) {
        return false;
    }

    //check to make sure you can't go above max
    testSprite->addFrame(*testFrame);
    if (!intTest("getFrameCount() max restrict", 2, testSprite->getFrameCount())) {
        return false;
    }

    //get frame
    if (!stringTest("getFrame()", ">-", testSprite->getFrame(1).getString())) {
        return false;
    }

    //get/set width
    testSprite->setWidth(2);
    if (!intTest("getWidth()", 2, testSprite->getWidth())) {
        return false;
    }

    //get/set height
    testSprite->setHeight(1);
    if (!intTest("getHeight()", 1, testSprite->getHeight())) {
        return false;
    }

    LM.writeLog("***All Sprite/Frame tests pass!");
    return true;
}

bool animationTests() {
    df::Animation* testAnimation = new df::Animation();
    testAnimation->setSprite(RM.getSprite("bullet"));

    //get/set name
    //get frame
    if (!stringTest("getLabel()", "bullet", testAnimation->getSprite()->getLabel())) {
        return false;
    }

    //get height/width
    if (!intTest("getWidth()", 2, testAnimation->getSprite()->getWidth())) {
        return false;
    }

    if (!intTest("getHeight()", 1, testAnimation->getSprite()->getHeight())) {
        return false;
    }

    //get frame str
    if (!stringTest("getFrame0Str()", ">-", testAnimation->getSprite()->getFrame(0).getString())) {
        return false;
    }

    if (!stringTest("getFrame1Str()", ">:", testAnimation->getSprite()->getFrame(1).getString())) {
        return false;
    }


    return true;

}

bool boxTests() {
    //positive horizontal collision
    //negative horizontal collision
    //positive vertical collision
    //negative vertical collision

    //box a is completely contained within box b
    //box b is completely contained within box a
    return true;
}

bool intTest(std::string testName, int parameter1, int parameter2) {
    if (parameter1 == parameter2) {
        LM.writeLog("%s passed!", testName.c_str());
        return true;
    }
    else {
        LM.writeLog("%s failed., actual result was %d", testName.c_str(), parameter2);
        return false;
    }

    
}

bool boolTest(std::string testName, bool parameter1, bool parameter2) {
    if (parameter1 == parameter2) {
        LM.writeLog("%s passed!", testName.c_str());
        return true;
    }
    else {
        LM.writeLog("%s failed...", testName.c_str());
        return false;
    }
}

bool stringTest(std::string testName, std::string parameter1, std::string parameter2) {
    if (parameter1 == parameter2) {
        LM.writeLog("%s passed!", testName.c_str());
        return true;
    }
    else {
        LM.writeLog("%s failed...", testName.c_str());
        return false;
    }
}