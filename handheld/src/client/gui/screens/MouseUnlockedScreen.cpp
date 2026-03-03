#include "MouseUnlockedScreen.h"
#include "../../Minecraft.h"

#include <cstddef>

bool MouseUnlockedScreen::isPauseScreen() {
	return false;
}
bool MouseUnlockedScreen::isInGameScreen() {
	return true;
}

void MouseUnlockedScreen::buttonClicked(Button *button) {
	this->minecraft->setScreen(NULL);
}

MouseUnlockedScreen::MouseUnlockedScreen() {
    this->button = NULL;
}
MouseUnlockedScreen::~MouseUnlockedScreen() {
    if (this->button) {
        delete this->button;
    }
}

void MouseUnlockedScreen::init() {
    this->button = new Touch::TButton(1, "Close");
    this->buttons.push_back(this->button);
    this->tabButtons.push_back(this->button);
}
