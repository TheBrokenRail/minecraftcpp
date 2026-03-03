#include "OptionsItem.h"
#include "../../Minecraft.h"
#include "../../../util/Mth.h"
OptionsItem::OptionsItem( std::string label, GuiElement* element )
: GuiElementContainer(false, true, 0, 0, 24, 12),
  label(label),
  element(element) {
}

OptionsItem::~OptionsItem() {
	if (element != NULL) {
		delete element;
		element = NULL;
	}
}

void OptionsItem::setupPositions() {
	element->x = x + width - element->width - 15;
	element->y = y;
	height = Mth::Max(element->height, 12);
}

void OptionsItem::render( Minecraft* minecraft, int xm, int ym ) {
	int yOffset = (height - 8) / 2;
	minecraft->font->draw(label, (float)x, (float)y + yOffset, 0x909090, false);
	element->render(minecraft, xm, ym);
	super::render(minecraft, xm, ym);
}

void OptionsItem::tick(Minecraft *minecraft) {
	if (element != NULL) {
		element->tick(minecraft);
	}
}
