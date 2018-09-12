#pragma once

#include "rack.hpp"

struct JSFXModel : rack::Model
{
	std::string effectPath;
	rack::ModuleWidget *createModuleWidget() override;
	rack::ModuleWidget *createModuleWidgetNull() override;
};
