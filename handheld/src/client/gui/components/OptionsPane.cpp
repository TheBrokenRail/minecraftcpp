#include "OptionsPane.h"
#include "OptionsGroup.h"
#include "OptionsItem.h"
#include "ImageButton.h"
#include "Slider.h"
#include "../../Minecraft.h"

OptionsPane::OptionsPane(): optionGroupCount(0) {
}

void OptionsPane::setupPositions() {
	int currentHeight = y + 1;
	for(std::vector<GuiElement*>::iterator it = children.begin(); it != children.end(); ++it ) {
		(*it)->width = width;
		(*it)->y = currentHeight;
		(*it)->x = x;
		currentHeight += (*it)->height + 1;
	}
	height = currentHeight;
	super::setupPositions();
}

int OptionsPane::createOptionsGroup( std::string label ) {
	children.push_back(new OptionsGroup(label));
	// create and return a new group index
	return optionGroupCount++;
}

void OptionsPane::createToggle( unsigned int group, std::string label, const Options::Option* option ) {
	if(group > children.size()) return;
	ImageDef def;
	def.setSrc(IntRectangle(160, 206, 39, 20));
	def.name = "gui/touchgui.png";
	def.width = 39 * 0.7f;
	def.height = 20 * 0.7f;
	OptionButton* element = new OptionButton(option);
	element->setImageDef(def, true);
	toggleButtons.push_back(element);
	OptionsItem* item = new OptionsItem(label, element);
	((OptionsGroup*)children[group])->addChild(item);
	setupPositions();
}

void OptionsPane::createProgressSlider( Minecraft* minecraft, unsigned int group, std::string label, const Options::Option* option, float progressMin/*=1.0f*/, float progressMax/*=1.0f */ ) {
	if(group > children.size()) return;
	Slider* element = new Slider(minecraft, option, progressMin, progressMax);
	element->width = 100;
	element->height = 20;
	sliders.push_back(element);
	OptionsItem* item = new OptionsItem(label, element);
	((OptionsGroup*)children[group])->addChild(item);
	setupPositions();
}

void OptionsPane::createStepSlider( Minecraft* minecraft, unsigned int group, std::string label, const Options::Option* option, const std::vector<int>& stepVec ) {
	if(group > children.size()) return;
	Slider* element = new Slider(minecraft, option, stepVec);
	element->width = 100;
	element->height = 20;
	sliders.push_back(element);
	OptionsItem* item = new OptionsItem(label, element);
	((OptionsGroup*)children[group])->addChild(item);
	setupPositions();
}

void OptionsPane::mouseClicked(Minecraft *minecraft, int x, int y, int buttonNum ) {
	if (buttonNum == MouseAction::ACTION_LEFT) {
		for (std::vector<OptionButton*>::iterator it = toggleButtons.begin(); it != toggleButtons.end(); ++it) {
			if ((*it)->clicked(minecraft, x, y)) {
				(*it)->toggle(&minecraft->options);
			}
		}
	}
	for (std::vector<Slider*>::iterator it = sliders.begin(); it != sliders.end(); ++it) {
		if (*it != NULL) {
			(*it)->mouseClicked(minecraft, x, y, buttonNum);
		}
	}
}

void OptionsPane::mouseReleased(Minecraft *minecraft, int x, int y, int buttonNum) {
	for (std::vector<Slider*>::iterator it = sliders.begin(); it != sliders.end(); ++it) {
		if (*it != NULL) {
			(*it)->mouseReleased(minecraft, x, y, buttonNum);
		}
	}
}
