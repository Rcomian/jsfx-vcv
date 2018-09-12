#pragma once

#include "rack.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx.h"
#include "JSFXModule.hpp"
#include "../include/JsusFxGfx_VCV.hpp"

struct JSFXModuleWidget : rack::ModuleWidget {
  rack::Panel *panel;
	JSFXModuleWidget(JSFXModule *module);
  void draw(NVGcontext *vg) override;
  JsusFxVCV* _jsusfx;
  JsusFxGfx_VCV* _jsusfx_gfx;
  rack::Vec _gfx_point;
};
