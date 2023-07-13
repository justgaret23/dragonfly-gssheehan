//
//resourcemanager.cpp
//

//C includes
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <sstream>

#include "LogManager.h"
#include "ResourceManager.h"

//Stubs

//Get the one and only instance of the ResourceManager.
df::ResourceManager& df::ResourceManager::getInstance() {
    static ResourceManager single;
    return single;
}

df::ResourceManager::ResourceManager() {

}

/*
* Load sound from file
* Return 0 on success, -1 on fail
*/
int df::ResourceManager::loadSound(std::string filename, std::string label){
    //Check to see if array is full
    if(sound_count == MAX_SOUNDS){
        LM.writeLog("RM::loadSound ERROR: Sound array is full! Cannot load more sounds");
        return -1;
    }

    //Check to see if sound can be loaded
    if(sound[sound_count].loadSound(filename) == -1){
        LM.writeLog("RM::loadSound ERROR: Cannot load sound from file");
        return -1;
    }

    //If we passed both errors, we can go ahead, set labels, and increment
    sound[sound_count].setLabel(label);
    sound_count++;
    return 0;
}

/*
* Remove sound with indicated label
* Return 0 on success, -1 on fail
*/
int df::ResourceManager::unloadSound(std::string label){
    for (int i = 0; i < sound_count; i++){
        //Upon finding the sound, 
        if(label == sound[i].getLabel()){
            //we scoot over all remaining sounds, decrement, and return a success
            for (int j = i; j < sound_count - 2; j++){
                sound[j] = sound[j + 1];
            }

            sound_count--;
            return 0;
        }
    }
    LM.writeLog("RM::unloadSound ERROR: Sound %s could not be unloaded", label);
    return -1;
}

/*
* Find sound with indicated label
* Return pointer if found, return NULL if not
*/
df::Sound* df::ResourceManager::getSound(std::string label){
    //Iterate through all sounds, and if we find the label, return its pointer
    for (int i = 0; i < sound_count; i++){
        if(label == sound[i].getLabel()){
            return (&sound[i]);
        }
    }

    //If we got here, we couldn't find the sprite
    return NULL;
}

/*
* Associate file with music
* Return 0 on success, -1 on fail
*/
int df::ResourceManager::loadMusic(std::string filename, std::string label){
    //Check to see if array is full
    if(music_count == MAX_MUSICS){
        LM.writeLog("RM::loadMusic ERROR: Music array is full! Cannot load more sounds");
        return -1;
    }

    //Check to see if music can be loaded
    if(music[music_count].loadMusic(filename) == -1){
        LM.writeLog("RM::loadMusic ERROR: Cannot load music from file");
        return -1;
    }

    //If we passed both errors, we can go ahead, set labels, and increment
    music[music_count].setLabel(label);
    music_count++;
    return 0;
}

/*
* Remove music with indicated label
* Return 0 on success, -1 on fail
* NOTE: "" cannot be used to distinguish an unloaded music, as we replace sounds with ""
*/
int df::ResourceManager::unloadMusic(std::string label){
    for (int i = 0; i < music_count; i++) {
        //Upon finding the sound, 
        if (label == music[i].getLabel()) {
            //We set the unloaded sound to the empty character ""
            music[i].setLabel("");
            return 0;
        }
    }
    LM.writeLog("RM::unloadSound ERROR: Sound %s could not be unloaded", label);
    return -1;
}

/*
* Find music with indicated label
* Return pointer if found, return NULL if not
*/
df::Music* df::ResourceManager::getMusic(std::string label){
    //Iterate through all musics, and if we find the label, return its pointer
    for (int i = 0; i < music_count; i++) {
        if (label == music[i].getLabel()) {
            return (&music[i]);
        }
    }

    //If we got here, we couldn't find the music
    return NULL;
}