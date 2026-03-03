#include "OptionsGroup.h"
#include "../../Minecraft.h"
#include "ImageButton.h"
#include "OptionsItem.h"
#include "Slider.h"
#include "../../../locale/I18n.h"
OptionsGroup::OptionsGroup( std::string labelID ): label(labelID) {
}

void OptionsGroup::setupPositions() {
	// First we write the header and then we add the items
	int curY = y + 10;
	for(std::vector<GuiElement*>::iterator it = children.begin(); it != children.end(); ++it) {
		(*it)->width = width - 5;
		
		(*it)->y = curY;
		(*it)->x = x + 10;
		(*it)->setupPositions();
		curY += (*it)->height + 3;
	}
	height = curY;
}

void OptionsGroup::render( Minecraft* minecraft, int xm, int ym ) {
	minecraft->font->draw(label, (float)x + 2, (float)y, 0xffffffff, false);
	super::render(minecraft, xm, ym);
}
