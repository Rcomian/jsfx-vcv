#include "../include/JSFXModuleWidget.hpp"
#include "../include/JsusFxGfx_VCV.hpp"
using namespace rack;

struct GraphicsCursor {
  GraphicsCursor() {
    x = 0;
    y = 0;
    columnTop = 0;
  }

  void MoveRight(float right) {
    x += right;
  }

  void SetY(float newY) {
    y = newY;
  }

  void SetHeight(float newHeight) {
    totalheight = newHeight;
  }

  void StartColumn(float width, float height) {
    columnTop = y;
    columnItemWidth = width;
    columnItemHeight = height;
    columnUsed = false;
  }

  void EndColumn(float spacing) {
    y = columnTop;

    if (columnUsed) {
      x += columnItemWidth + spacing;
    }
  }

  Vec NextBox(float height = 0.f) {
    columnUsed = true;

    if (height == 0.f) {
      height = columnItemHeight;
    }

    if (y > columnTop && y + height > totalheight) {
      y = columnTop;
      x += columnItemWidth;
    }

    Vec result(x, y);

    y += height;

    return result;
  }

  float x;
  float y;
  float totalheight;

  float columnTop;
  float columnItemWidth;
  float columnItemHeight;
  bool columnUsed;
};

JSFXModuleWidget::JSFXModuleWidget(JSFXModule *module) : ModuleWidget(module) {
  _jsusfx = module->_jsusfx;
  _jsusfx_gfx = static_cast<JsusFxGfx_VCV*>(module->_jsusfx->gfx);
  auto module_height = RACK_GRID_HEIGHT;

  if (_jsusfx->usesGfx()) {
    info("Module requests graphics: %d %d", _jsusfx->gfx_w, _jsusfx->gfx_h);

    float top_padding = RACK_GRID_WIDTH * 3;
    float bottom_padding = RACK_GRID_WIDTH;

    if (_jsusfx->gfx_h > RACK_GRID_HEIGHT - top_padding - bottom_padding) {
      module_height = RACK_GRID_HEIGHT * ceil((_jsusfx->gfx_h + top_padding + bottom_padding) / RACK_GRID_HEIGHT);
    }

    _jsusfx->gfx_h = module_height - top_padding - bottom_padding;
  }

  box.size = Vec(RACK_GRID_WIDTH * 50, module_height);

  {
    panel = new LightPanel();
    panel->box.size = box.size;
    addChild(panel);
  }

  // Add controls
  GraphicsCursor cursor;
  cursor.MoveRight(RACK_GRID_WIDTH/2);
  cursor.SetY(RACK_GRID_WIDTH * 3);
  cursor.SetHeight(module_height);

  // Add inputs
  cursor.StartColumn(85, 30);

  // Add tempo input
  auto itempos = cursor.NextBox();
  {
    auto label = new Label();
    label->color = nvgRGB(0x00, 0x00, 0x00);
    label->text = "BPM";
    label->box.pos.x = itempos.x + 20;
    label->box.pos.y = itempos.y + 2; 
    label->box.size.x = 65;
    addChild(label);
  }
  addInput(Port::create<PJ301MPort>(Vec(itempos.x, itempos.y), Port::INPUT, module, module->_jsusfx->numInputs + module->_jsusfx->numsliders()));

  for (int inputid = 0; inputid < module->_jsusfx->numInputs; inputid += 1) {
    auto itempos = cursor.NextBox();
    addInput(Port::create<PJ301MPort>(Vec(itempos.x, itempos.y), Port::INPUT, module, inputid));

    {
      auto label = new Label();
      label->color = nvgRGB(0x00, 0x00, 0x00);
      char output[4096];
      snprintf(output, 4095, "Input %d", inputid);
      label->text = output;
      label->box.pos.x = itempos.x + 20;
      label->box.pos.y = itempos.y + 2; 
      label->box.size.x = 65;
      addChild(label);
    }

  }
  cursor.EndColumn(RACK_GRID_WIDTH/2);

  // Add Sliders
  int paramindex = 0;
  cursor.StartColumn(170, 55);
  int numsliders = module->_jsusfx->numsliders();
  int cvoffset = 30;
  int trimpotleft = 3;
  int trimpottop = 28;
  for (auto slider : module->_jsusfx->sliders) {
    if (slider.exists) {

      if (!slider.isEnum) {
        auto itempos = cursor.NextBox(70);

        addInput(Port::create<PJ301MPort>(Vec(itempos.x, itempos.y), Port::INPUT, module, module->_jsusfx->numInputs + paramindex));
        addParam(ParamWidget::create<Trimpot>(Vec(itempos.x + trimpotleft, itempos.y + trimpottop), module, numsliders + paramindex, -1, 1, 0));

        if (slider.inc > 0) {
          auto knob = ParamWidget::create<Davies1900hBlackKnob>(Vec(itempos.x + cvoffset, itempos.y + 5), module, paramindex, slider.min / slider.inc, slider.max / slider.inc, slider.def / slider.inc);
          knob->snap = true;
          addParam(knob);
        } else {
          auto knob = ParamWidget::create<Davies1900hBlackKnob>(Vec(itempos.x + cvoffset, itempos.y + 5), module, paramindex, slider.min, slider.max, slider.def);
          addParam(knob);
        }

        {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.desc;
          label->box.pos.x = itempos.x + 33 + cvoffset;
          label->box.pos.y = itempos.y; 
          label->box.size.x = 100;
          addChild(label);
        }

      } else if (slider.enumNames.size() == 2) {
        auto itempos = cursor.NextBox(70);

        addInput(Port::create<PJ301MPort>(Vec(itempos.x, itempos.y + 18), Port::INPUT, module, module->_jsusfx->numInputs + paramindex));
        addParam(ParamWidget::create<Trimpot>(Vec(itempos.x + trimpotleft, itempos.y + trimpottop + 18), module, numsliders + paramindex, -1, 1, 0));

        {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.desc;
          label->box.pos.x = itempos.x - 5;
          label->box.pos.y = itempos.y; 
          label->box.size.x = 175;
          addChild(label);
        }

        addParam(ParamWidget::create<CKSS>(Vec(itempos.x+10 + cvoffset, itempos.y + 28), module, paramindex, slider.min, slider.max, slider.def));

        {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.enumNames[0];
          label->box.pos.x = itempos.x + 20 + cvoffset;
          label->box.pos.y = itempos.y + 35; 
          label->box.size.x = 130;
          addChild(label);
        }

        {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.enumNames[1];
          label->box.pos.x = itempos.x + 20 + cvoffset;
          label->box.pos.y = itempos.y + 23; 
          label->box.size.x = 130;
          addChild(label);
        }
      } else if (slider.enumNames.size() == 3) {
        auto itempos = cursor.NextBox(80);

        addInput(Port::create<PJ301MPort>(Vec(itempos.x, itempos.y + 18), Port::INPUT, module, module->_jsusfx->numInputs + paramindex));
        addParam(ParamWidget::create<Trimpot>(Vec(itempos.x + trimpotleft, itempos.y + trimpottop + 18), module, numsliders + paramindex, -1, 1, 0));

        {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.desc;
          label->box.pos.x = itempos.x - 5;
          label->box.pos.y = itempos.y; 
          label->box.size.x = 175;
          addChild(label);
        }

        addParam(ParamWidget::create<CKSSThree>(Vec(itempos.x+10 + cvoffset, itempos.y + 28), module, paramindex, slider.min, slider.max, slider.def));

        {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.enumNames[0];
          label->box.pos.x = itempos.x + 20 + cvoffset;
          label->box.pos.y = itempos.y + 45; 
          label->box.size.x = 130;
          addChild(label);
        }

        {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.enumNames[1];
          label->box.pos.x = itempos.x + 20 + cvoffset;
          label->box.pos.y = itempos.y + 33; 
          label->box.size.x = 130;
          addChild(label);
        }

        {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.enumNames[2];
          label->box.pos.x = itempos.x + 20 + cvoffset;
          label->box.pos.y = itempos.y + 21; 
          label->box.size.x = 130;
          addChild(label);
        }

      } else {
        int height = 60;
        int calcheight = 21 + (slider.enumNames.size() * 12) + 12;
        if (calcheight > height) {
          height = calcheight;
        }
        

        auto itempos = cursor.NextBox(height);

        addInput(Port::create<PJ301MPort>(Vec(itempos.x, itempos.y + 25), Port::INPUT, module, module->_jsusfx->numInputs + paramindex));
        addParam(ParamWidget::create<Trimpot>(Vec(itempos.x + trimpotleft, itempos.y + trimpottop + 25), module, numsliders + paramindex, -1, 1, 0));

        {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.desc;
          label->box.pos.x = itempos.x - 5;
          label->box.pos.y = itempos.y; 
          label->box.size.x = 175;
          addChild(label);
        }

        auto knob = ParamWidget::create<Davies1900hBlackKnob>(Vec(itempos.x + cvoffset, itempos.y + 28), module, paramindex, slider.min, slider.max, slider.def);
        knob->snap = true;
        knob->smooth = false;
        addParam(knob);

        for (uint i = 0; i < slider.enumNames.size(); i += 1) {
          auto label = new Label();
          slider.desc[63] = '\0';
          label->color = nvgRGB(0x00, 0x00, 0x00);
          label->text = slider.enumNames[i];
          label->box.pos.x = itempos.x + 33 + cvoffset;
          label->box.pos.y = itempos.y + 21 + (i * 12); 
          label->box.size.x = 130;
          addChild(label);
        }

      }

      paramindex += 1;
    }
  }
  cursor.EndColumn(RACK_GRID_WIDTH/2);


  // Add outputs
  cursor.StartColumn(90, 30);
  for (int outputid = 0; outputid < module->_jsusfx->numOutputs; outputid += 1) {
    auto pos = cursor.NextBox();

    {
      auto label = new Label();
      label->color = nvgRGB(0x00, 0x00, 0x00);
      char output[4096];
      snprintf(output, 4095, "Output %d", outputid);
      label->text = output;
      label->alignment = Label::RIGHT_ALIGNMENT;
      label->box.pos.x = pos.x;
      label->box.pos.y = pos.y + 2; 
      label->box.size.x = 70;
      addChild(label);
    }
    
    addOutput(Port::create<PJ301MPort>(Vec(pos.x + 70, pos.y), Port::OUTPUT, module, outputid));
  }
  cursor.EndColumn(RACK_GRID_WIDTH/2);

  // Add graphics
  cursor.StartColumn(_jsusfx->gfx_w, _jsusfx->gfx_h);
  _gfx_point = cursor.NextBox();
  cursor.EndColumn(RACK_GRID_WIDTH/2);

  // Set panel size
  box.size.x = ceil(cursor.x / RACK_GRID_WIDTH) * RACK_GRID_WIDTH;
  panel->box.size.x = box.size.x;

  // Add title
  {
    auto label = new Label();
    label->color = nvgRGB(0x00, 0x00, 0x00);
    label->text = module->_jsusfx->displayname();
    label->box.pos.x = 0;
    label->box.size.x = box.size.x;
    label->box.pos.y = RACK_GRID_WIDTH / 2.f; 
    label->alignment = Label::CENTER_ALIGNMENT;
    addChild(label);
  }

  // Add screws
  addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
  addChild(Widget::create<ScrewSilver>(Vec(15, module_height - 15)));
  addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
  addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, module_height - 15)));

}

void JSFXModuleWidget::draw(NVGcontext *vg) {
  ModuleWidget::draw(vg);

  if (_jsusfx->usesGfx()) {
    nvgScissor(vg, _gfx_point.x, _gfx_point.y, _jsusfx->gfx_w, _jsusfx->gfx_h);

    nvgTranslate(vg, _gfx_point.x, _gfx_point.y);

    // Background
    nvgBeginPath(vg);
    nvgRect(vg, 0, 0, _jsusfx->gfx_w, _jsusfx->gfx_h);
    nvgFillColor(vg, nvgRGB(0x00, 0x00, 0x00));
    nvgFill(vg);

    _jsusfx_gfx->vg = vg;
    *_jsusfx_gfx->m_gfx_w = _jsusfx->gfx_w;
    *_jsusfx_gfx->m_gfx_h = _jsusfx->gfx_h;
    *_jsusfx_gfx->m_gfx_r = 1;
    *_jsusfx_gfx->m_gfx_g = 1;
    *_jsusfx_gfx->m_gfx_b = 1;
    *_jsusfx_gfx->m_gfx_a = 1;
    _jsusfx->draw();

  	nvgResetScissor(vg);
  }

}
