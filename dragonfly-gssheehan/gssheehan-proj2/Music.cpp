///
///music.h
/// 

//Dragonfly includes
#include "LogManager.h"
#include "Music.h"

//constructor
df::Music::Music() {

}

/*
* Associate music buffer with file.
* Return 0 if ok, else -1.
*/
int df::Music::loadMusic(std::string filename) {
    if (!m_music.openFromFile(filename)) {
        LM.writeLog("Music.loadMusic ERROR: this music does not have the right filename!");
        return -1;
    }
    //m_music.play();
   
    return 0;
}

/*
* Set label associated with music.
*/
void df::Music::setLabel(std::string new_label) {
    m_label = new_label;
}

/*
* Get label associated with music.
*/
std::string df::Music::getLabel() const {
    return m_label;
}

/*
* Play music.
* If loop is true, repeat play when done.
*/
void df::Music::play(bool loop) {
    m_music.play();
    if (loop) {
        m_music.setLoop(true);
    }
    else {
        m_music.setLoop(false);
    }
}

/*
* Stop music.
*/
void df::Music::stop() {
    m_music.stop();
}

/*
* Pause music.
*/
void df::Music::pause() {
    m_music.pause();
}

/*
* Return pointer to SFML music.
*/
sf::Music* df::Music::getMusic() {
    return &m_music;
}