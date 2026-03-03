#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS__MouseUnlockedScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS__MouseUnlockedScreen_H__

#include "../Screen.h"
#include "../components/ImageButton.h"

class MouseUnlockedScreen: public Screen
{
public:
	bool isPauseScreen();
	bool isInGameScreen();

	void buttonClicked(Button *button);

	virtual ~MouseUnlockedScreen();
	MouseUnlockedScreen();

	void init();

private:
    Button *button;
};

#endif /*NET_MINECRAFT_CLIENT_GUI_SCREENS__MouseUnlockedScreen_H__*/
