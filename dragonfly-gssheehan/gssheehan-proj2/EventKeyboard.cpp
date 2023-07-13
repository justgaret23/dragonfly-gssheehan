//
//eventkeyboard.cpp
//

//Dragonfly includes
#include "EventKeyboard.h"

//constructor
df::EventKeyboard::EventKeyboard() {
	m_key_val = df::Keyboard::UNDEFINED_KEY;
	m_keyboard_action = df::UNDEFINED_KEYBOARD_ACTION;
	setType(KEYBOARD_EVENT);
}

/*
* Set EventKeyboard key
*/
void df::EventKeyboard::setKey(Keyboard::Key new_key){
	m_key_val = new_key;
}

/*
* Get key from EventKeyboard
*/
df::Keyboard::Key df::EventKeyboard::getKey() const{
	return m_key_val;
}

/*
* set keyboard event action
*/
void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action){
	m_keyboard_action = new_action;
}

/*
* get keyboard event action
*/
df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const{
	return m_keyboard_action;
}

/*
* Converts an sfml key press into an appropriate dragonfly EventKeyboard event
* Returns the supported DF event of an SFML key.
*/
df::Keyboard::Key df::EventKeyboard::sfmlToDf(sf::Keyboard::Key sfmlKey) {
	switch (sfmlKey) {
	case sf::Keyboard::Up:
		return df::Keyboard::UPARROW;
		break;
	case sf::Keyboard::Down:
		return df::Keyboard::DOWNARROW;
		break;
	case sf::Keyboard::Left:
		return df::Keyboard::LEFTARROW;
		break;
	case sf::Keyboard::Right:
		return df::Keyboard::RIGHTARROW;
		break;
	case sf::Keyboard::Space:
		return df::Keyboard::SPACE;
		break;
	case sf::Keyboard::Return:
		return df::Keyboard::RETURN;
		break;
	case sf::Keyboard::Escape:
		return df::Keyboard::ESCAPE;
		break;
	case sf::Keyboard::Tab:
		return df::Keyboard::TAB;
		break;
	case sf::Keyboard::Pause:
		return df::Keyboard::PAUSE;
		break;
	case sf::Keyboard::LShift:
		return df::Keyboard::LEFTSHIFT;
		break;
	case sf::Keyboard::RShift:
		return df::Keyboard::RIGHTSHIFT;
		break;
	case sf::Keyboard::Subtract:
		return df::Keyboard::MINUS;
		break;
	case sf::Keyboard::Add:
		return df::Keyboard::PLUS;
		break;
	case sf::Keyboard::Tilde:
		return df::Keyboard::TILDE;
		break;
	case sf::Keyboard::Period:
		return df::Keyboard::PERIOD;
		break;
	case sf::Keyboard::Comma:
		return df::Keyboard::COMMA;
		break;
	case sf::Keyboard::Slash:
		return df::Keyboard::SLASH;
		break;
	case sf::Keyboard::LControl:
		return df::Keyboard::LEFTCONTROL;
		break;
	case sf::Keyboard::RControl:
		return df::Keyboard::RIGHTCONTROL;
		break;
	case sf::Keyboard::F1:
		return df::Keyboard::F1;
		break;
	case sf::Keyboard::F2:
		return df::Keyboard::F2;
		break;
	case sf::Keyboard::F3:
		return df::Keyboard::F3;
		break;
	case sf::Keyboard::F4:
		return df::Keyboard::F4;
		break;
	case sf::Keyboard::F5:
		return df::Keyboard::F5;
		break;
	case sf::Keyboard::F6:
		return df::Keyboard::F6;
		break;
	case sf::Keyboard::F7:
		return df::Keyboard::F7;
		break;
	case sf::Keyboard::F8:
		return df::Keyboard::F8;
		break;
	case sf::Keyboard::F9:
		return df::Keyboard::F9;
		break;
	case sf::Keyboard::F10:
		return df::Keyboard::F10;
		break;
	case sf::Keyboard::F11:
		return df::Keyboard::F11;
		break;
	case sf::Keyboard::F12:
		return df::Keyboard::F12;
		break;
	case sf::Keyboard::A:
		return df::Keyboard::A;
		break;
	case sf::Keyboard::B:
		return df::Keyboard::B;
		break;
	case sf::Keyboard::C:
		return df::Keyboard::C;
		break;
	case sf::Keyboard::D:
		return df::Keyboard::D;
		break;
	case sf::Keyboard::E:
		return df::Keyboard::E;
		break;
	case sf::Keyboard::F:
		return df::Keyboard::F;
		break;
	case sf::Keyboard::G:
		return df::Keyboard::G;
		break;
	case sf::Keyboard::H:
		return df::Keyboard::H;
		break;
	case sf::Keyboard::I:
		return df::Keyboard::I;
		break;
	case sf::Keyboard::J:
		return df::Keyboard::J;
		break;
	case sf::Keyboard::K:
		return df::Keyboard::K;
		break;
	case sf::Keyboard::L:
		return df::Keyboard::L;
		break;
	case sf::Keyboard::M:
		return df::Keyboard::M;
		break;
	case sf::Keyboard::N:
		return df::Keyboard::N;
		break;
	case sf::Keyboard::O:
		return df::Keyboard::O;
		break;
	case sf::Keyboard::P:
		return df::Keyboard::P;
		break;
	case sf::Keyboard::Q:
		return df::Keyboard::Q;
		break;
	case sf::Keyboard::R:
		return df::Keyboard::R;
		break;
	case sf::Keyboard::S:
		return df::Keyboard::S;
		break;
	case sf::Keyboard::T:
		return df::Keyboard::T;
		break;
	case sf::Keyboard::U:
		return df::Keyboard::U;
		break;
	case sf::Keyboard::V:
		return df::Keyboard::V;
		break;
	case sf::Keyboard::W:
		return df::Keyboard::W;
		break;
	case sf::Keyboard::X:
		return df::Keyboard::X;
		break;
	case sf::Keyboard::Y:
		return df::Keyboard::Y;
		break;
	case sf::Keyboard::Z:
		return df::Keyboard::Z;
		break;
	case sf::Keyboard::Num1:
		return df::Keyboard::NUM1;
		break;
	case sf::Keyboard::Num2:
		return df::Keyboard::NUM2;
		break;
	case sf::Keyboard::Num3:
		return df::Keyboard::NUM3;
		break;
	case sf::Keyboard::Num4:
		return df::Keyboard::NUM4;
		break;
	case sf::Keyboard::Num5:
		return df::Keyboard::NUM5;
		break;
	case sf::Keyboard::Num6:
		return df::Keyboard::NUM6;
		break;
	case sf::Keyboard::Num7:
		return df::Keyboard::NUM7;
		break;
	case sf::Keyboard::Num8:
		return df::Keyboard::NUM8;
		break;
	case sf::Keyboard::Num9:
		return df::Keyboard::NUM9;
		break;
	case sf::Keyboard::Num0:
		return df::Keyboard::NUM0;
		break;
	}
}