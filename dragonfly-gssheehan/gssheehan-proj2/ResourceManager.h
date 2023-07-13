#pragma once
//
//resourcemanager.h
//

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

// System includes.
#include <string>

// Engine includes.
#include "Manager.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"
#include "SpriteResourceManager.h"

// Two-letter acronym for easier access to manager.
#define RM df::ResourceManager::getInstance()

namespace df {

    const int MAX_SOUNDS = 128;
    const int MAX_MUSICS = 128;

    // Delimiters used to parse Sprite files -
    // the ResourceManager "knows" file format.

    class ResourceManager : public SpriteResourceManager {
    private:
        ResourceManager(ResourceManager const&); //Don't allow copy.
        void operator=(ResourceManager const&);  //Don't allow assignment.
        ResourceManager();	                     //Private since a singleton.

        //sound
        Sound sound[MAX_SOUNDS];
        int sound_count;
        Music music[MAX_MUSICS];
        int music_count;

    public:
        /// Get the one and only instance of the ResourceManager.
        static ResourceManager& getInstance();

        //Load sound from file
        //Return 0 on success, -1 on fail
        int loadSound(std::string filename, std::string label);

        //Remove sound with indicated label
        //Return 0 on success, -1 on fail
        int unloadSound(std::string label);

        //Find sound with indicated label
        //Return pointer if found, return NULL if not
        Sound* getSound(std::string label);

        //Associate file with music
        //Return 0 on success, -1 on fail
        int loadMusic(std::string filename, std::string label);

        //Remove music with indicated label
        //Return 0 on success, -1 on fail
        int unloadMusic(std::string label);

        //Find music with indicated label
        //Return pointer if found, return NULL if not
        Music* getMusic(std::string label);
    };

} // end of namespace df
#endif //__RESOURCE_MANAGER_H__
