#pragma once

#include "rack.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx.h"
#include "JSFXModule.hpp"

struct JSFXModuleWidget : rack::ModuleWidget {
  rack::Panel *panel;
	JSFXModuleWidget(JSFXModule *module);
};
