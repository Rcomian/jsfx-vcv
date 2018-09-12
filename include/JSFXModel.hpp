#pragma once

#include "rack.hpp"

struct JSFXModel : rack::Model
{
	std::string effectPath;
  bool useGfx;
	rack::ModuleWidget *createModuleWidget() override;
	rack::ModuleWidget *createModuleWidgetNull() override;
};
