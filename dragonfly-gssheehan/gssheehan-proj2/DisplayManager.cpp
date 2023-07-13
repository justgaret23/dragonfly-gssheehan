//
//displaymanager.cpp
//

#include <algorithm>
//Dragonfly includes
#include "DisplayManager.h"
#include "LogManager.h"
#include "utility.h"


//constructor
df::DisplayManager::DisplayManager() {
	
	m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
	m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
	m_p_window = new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_horizontal_pixels), "Dragonfly");
	m_font = sf::Font();
}

//singleton
df::DisplayManager& df::DisplayManager::getInstance() {
	static DisplayManager single;
	return single;
}

/*
* startup display manager (init everything to empty)
* return 0 on success
*/
int df::DisplayManager::startUp() {
	if (m_p_window == NULL) {
		LM.writeLog("ERROR: m_p_window is NULL");
		return -1;
	}

	//create window
	//Window dimensions in pixels
	int window_horizontal = 1024;
	int window_vertical = 768;
	sf::RenderWindow window(sf::VideoMode(window_horizontal, window_vertical), "Title - Dragonfly", sf::Style::Titlebar);

	//Make mouse cursor invisible
	m_p_window->setMouseCursorVisible(false);

	//Synchronize refresh rate with monitor
	m_p_window->setVerticalSyncEnabled(true);

	//Load graphical font
	std::string fontFile = "df-font.ttf";
	if (!m_font.loadFromFile(FONT_FILE_DEFAULT)) {
		LM.writeLog("DANGER ERROR: The graphical font file cannot be found!");
		return -1;
	}

	//if nothing broke, we invoke Manager::startup
	Manager::startUp();
}

/*
* Close graphics window
*/
void df::DisplayManager::shutDown() {
	Manager::shutDown();
}

/*
* Draw character at window location (x, y) with color
* Return 0 if ok, else -1
*/
int df::DisplayManager::drawCh(Vector world_pos, char ch, Color color) const{
	//Error check
	if (m_p_window == NULL) {
		LM.writeLog("ERROR: m_p_window is NULL");
		return -1;
	}

	//convert to world coordinates
	Vector view_pos = worldToView(world_pos);

	//Convert spaces (x,y) to pixels (x,y)
	df::Vector pixel_pos = DM.spacesToPixels(view_pos);
	

	//Draw background rectangle b/c characters are see-through in SFML
	static sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(DM.charWidth(), DM.charHeight()));
	rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	rectangle.setPosition(pixel_pos.getX() - DM.charWidth() / 10,
		                  pixel_pos.getY() + DM.charHeight() / 5);
	m_p_window->draw(rectangle);

	//Create character text to draw
	static sf::Text text("", m_font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold); //bold looks nicer in Dragonfly

	//Scale to the right size
	if (DM.charWidth() < DM.charHeight()) {
		text.setCharacterSize((unsigned int)DM.charWidth() * 2);
	}
	else {
		text.setCharacterSize((unsigned int)DM.charHeight() * 2);
	}

	//Set SFML color based on Dragonfly color
	switch (color) {
		case BLACK:
			text.setFillColor(sf::Color::Black);
			break;
		case RED:
			text.setFillColor(sf::Color::Red);
			break;
		case GREEN:
			text.setFillColor(sf::Color::Green);
			break;
		case YELLOW:
			text.setFillColor(sf::Color::Yellow);
			break;
		case BLUE:
			text.setFillColor(sf::Color::Blue);
			break;
		case MAGENTA:
			text.setFillColor(sf::Color::Magenta);
			break;
		case CYAN:
			text.setFillColor(sf::Color::Cyan);
			break;
		case WHITE:
			text.setFillColor(sf::Color::White);
			break;
	}

	//Set position in window (in pixels)
	text.setPosition(pixel_pos.getX(), pixel_pos.getY());

	//Draw character
	m_p_window->draw(text);
}

/*
* Draw string at window location (x, y) with default color
* Justified left, center, or right
* Return 0 if successful, return -1 if not
*/
int df::DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const {
	//get starting position
	Vector starting_pos = pos;

	//switch case to determine justification
	switch (just) {
	case CENTER_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size() / 2);
		break;
	case RIGHT_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size());
		break;
	case LEFT_JUSTIFIED:
		break;
	default:
		break;
	}

	//draw string character by character
	for (int i = 0; i < str.size(); i++) {
		Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
	}

	return 0;
}

/*
* Return current window buffer
* Return 0 if ok, -1 if fail
*/
int df::DisplayManager::swapBuffers() {
	//Error check
	if (m_p_window == NULL) {
		LM.writeLog("ERROR: m_p_window is NULL");
		return -1;
	}

	//Display current window
	m_p_window->display();

	//Clear other window to get ready for the next draw
	m_p_window->clear();

	return 0;
}

//Return window's horizontal maximum (in characters)
int df::DisplayManager::getHorizontal() const {
	return m_window_horizontal_chars;
}

//Return window's vertical maximum (in characters)
int df::DisplayManager::getVertical() const{
	return m_window_vertical_chars;
}

//Return window's horizontal maximum (in pixels)
int df::DisplayManager::getHorizontalPixels() const{
	return m_window_horizontal_pixels;
}

//Return window's vertical maximum (in pixels)
int df::DisplayManager::getVerticalPixels() const{
	return m_window_vertical_pixels;
}

//Return pointer to SFML graphics window
sf::RenderWindow* df::DisplayManager::getWindow() const {
	return m_p_window;
}

/*
* Helper function that computes character height based on window size and font.
*/
float df::DisplayManager::charHeight() {
	return (float)getVerticalPixels()/getVertical();
}

/*
* Helper function that computes character width based on window size and font.
*/
float df::DisplayManager::charWidth() {
	return (float)getHorizontalPixels()/getHorizontal();
}

/*
* Helper function that converts ASCII spaces (x,y) to window pixels (x,y)
*/
df::Vector df::DisplayManager::spacesToPixels(df::Vector spaces) {
	df::Vector stpVec = Vector();
	stpVec.setX(spaces.getX() * charWidth());
	stpVec.setY(spaces.getY() * charHeight());

	return stpVec;
}

/*
* Helper function thatconverts window pixels (x,y) to ASCII spaces (x,y)
*/
df::Vector df::DisplayManager::pixelsToSpaces(df::Vector pixels) {
	df::Vector ptsVec = Vector();
	ptsVec.setX(pixels.getX() / charWidth());
	ptsVec.setY(pixels.getY() / charHeight());

	return ptsVec;
}