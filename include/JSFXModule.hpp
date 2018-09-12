#pragma once

#include "rack.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx.h"
#include "JsusFxVCV.hpp"

struct JSFXModule : rack::Module {
	JSFXModule(JsusFxVCV* jsusfx);
  ~JSFXModule();
	void step() override;

  float inbuffer[64][64];
  float outbuffer[64][64];
  int buffpos;
  int buffsize;

  JsusFxVCV* _jsusfx;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - onReset, onRandomize, onCreate, onDelete: implements special behavior when user clicks these from the context menu
};
