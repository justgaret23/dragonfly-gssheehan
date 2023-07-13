#pragma once
//
//displaymanager.h
//

#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

//C includes
#include <SFML/Graphics.hpp>
#include <algorithm>

//Dragonfly includes
#include "Color.h"
#include "Manager.h"
#include "Vector.h"

# define DM df :: DisplayManager :: getInstance ()

//Defaults for SFML Window
const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";

namespace df {

	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,
	};

	class DisplayManager : Manager {
	private:
		//singleton
		DisplayManager(); //private constructor
		DisplayManager(DisplayManager const&); //no copy!
		void operator=(DisplayManager const&); //no assign!

		//other attributes
		sf::Font m_font; //font used for ASCII graphics
		sf::RenderWindow* m_p_window; //Pointer to SFML window
		int m_window_horizontal_pixels; //horizontal pixels in window
		int m_window_vertical_pixels; //vertical pixels in window
		int m_window_horizontal_chars; //horizontal ASCII spaces in window
		int m_window_vertical_chars; //vertical ASCII spaces in window

		sf::Color m_window_background_color;
	public:
		//Get singleton instance of DisplayManager
		static DisplayManager& getInstance();

		//Open graphics window to prepare for the text-based display
		int startUp();

		//Close graphics window
		void shutDown();

		//Draw character at window location (x, y) with color
		//Return 0 if ok, else -1
		int drawCh(Vector world_pos, char ch, Color color) const;

		//Draw string at window location (x, y) with default color
		//Justified left, center, or right
		//Return 0 if successful, return -1 if not
		int drawString(Vector pos, std::string str, Justification just, Color color) const;

		//Return window's horizontal maximum (in characters)
		int getHorizontal() const;

		//Return window's vertical maximum (in characters)
		int getVertical() const;

		//Return window's horizontal maximum (in pixels)
		int getHorizontalPixels() const;

		//Return window's vertical maximum (in pixels)
		int getVerticalPixels() const;

		//Return current window buffer
		//Return 0 if ok, -1 if fail
		int swapBuffers();

		//Helper function that computes character height based on window size and font.
		float charHeight();

		//Helper function that computes character width based on window size and font
		float charWidth();

		//Helper function that converts ASCII spaces (x,y) to window pixels (x,y)
		df::Vector spacesToPixels(df::Vector spaces);

		//Helper function thatconverts window pixels (x,y) to ASCII spaces (x,y)
		df::Vector pixelsToSpaces(df::Vector pixels);

		//Return pointer to SFML graphics window
		sf::RenderWindow* getWindow() const;
	};
}

#endif
