#include "../include/Plugin.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx.h"
#include "../include/JSFXModule.hpp"
#include "engine.hpp"

JSFXModule::JSFXModule(JsusFxVCV* jsusfx) : Module(jsusfx->numsliders() * 2, jsusfx->numInputs + jsusfx->numsliders(), jsusfx->numOutputs, 0) {
  _jsusfx = jsusfx;

  for (buffpos = 0; buffpos < 64; buffpos += 1) {
    for (int c = 0; c < 64; c += 1) {
      inbuffer[c][buffpos] = 0.f;
      outbuffer[c][buffpos] = 0.f;
    }
  }

  buffsize = 64;
  buffpos = 0;

  _jsusfx->prepare(engineGetSampleRate(), buffsize);
}

JSFXModule::~JSFXModule() {
  delete _jsusfx;
}

void JSFXModule::step() {

  for (int c = 0; c < _jsusfx->numInputs; c += 1) {
    inbuffer[c][buffpos] = inputs[c].value / 20.f;
  }

  for (int c = 0; c < _jsusfx->numOutputs; c += 1) {
    outputs[c].value = outbuffer[c][buffpos] * 20.f;
  }

  buffpos = (buffpos + 1) % buffsize;

  if (buffpos == 0) {
    const float *ins[64];
    for (int c = 0; c < _jsusfx->numInputs; c += 1) {
      ins[c] = inbuffer[c];
    }

    float *outs[64];
    for (int c = 0; c < _jsusfx->numOutputs; c += 1) {
      outs[c] = outbuffer[c];
    }

    int numsliders = _jsusfx->numsliders();
    uint sliderid = 0;
    uint paramid = 0;
    for (auto slider : _jsusfx->sliders) {
      if (slider.exists) {
        auto paramvalue = params[paramid].value * slider.inc;
        if (slider.inc == 0.f) {
          paramvalue = params[paramid].value;
        }

        if (inputs[_jsusfx->numInputs + paramid].active) {
          auto range = slider.max - slider.min;
          auto trimamount = params[numsliders + paramid].value;
          auto cv = clamp(-1.f, 1.f, inputs[_jsusfx->numInputs + paramid].value / 5.f);
          paramvalue += (cv * trimamount * range);
        }

        _jsusfx->moveSlider(sliderid, paramvalue);
        paramid += 1;
      }
      sliderid += 1;
    }

    _jsusfx->process(ins, outs, buffsize, _jsusfx->numInputs, _jsusfx->numOutputs);
  }
}

