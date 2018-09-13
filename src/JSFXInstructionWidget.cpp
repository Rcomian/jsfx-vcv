#include "../include/plugin.hpp"
#include "rack.hpp"

using namespace rack;

struct JSFXInstructionWidget : ModuleWidget {
  JSFXInstructionWidget(Module *module) : ModuleWidget(module) {
    box.size = Vec(RACK_GRID_WIDTH * 10, RACK_GRID_HEIGHT);

    {
      auto panel = new LightPanel();
      panel->box.size = box.size;
      addChild(panel);
    }

    {
      auto label = new Label();
      label->color = nvgRGB(0x00, 0x00, 0x00);
      label->box.pos.x = RACK_GRID_WIDTH;
      label->box.pos.y = RACK_GRID_WIDTH; 
      label->box.size.x = RACK_GRID_WIDTH * 8;
      label->box.size.y = RACK_GRID_HEIGHT - (RACK_GRID_WIDTH * 2);

      label->text = "JSFX Loader\n\nNo JSFX effects were found.\n\nCopy them into the jsfx folder next to your plugins folder.\n\nThere are some example effects in the \"res\" folder of this plugin. See README.md for more details.\n\nThis module will be removed if any effects are found.";

      addChild(label);
    }
  }
};

Model *modelInstructionsPanel = Model::create<Module, JSFXInstructionWidget>("JSFX", "jsfx-instructions", "Instructions");
