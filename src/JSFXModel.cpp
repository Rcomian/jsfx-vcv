#include "../include/JSFXModel.hpp"
#include "../include/JSFXModule.hpp"
#include "../include/JSFXModuleWidget.hpp"
#include "../include/JsusFxVCV.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx.h"
#include "../include/JsusFxGfx_VCV.hpp"

using namespace rack;
using namespace std;

ModuleWidget *JSFXModel::createModuleWidget()
{
  string fullpath = assetLocal("jsfx") + '/' + effectPath;
  JsusFxPathLibrary_Basic fxpath(fullpath.c_str());
  auto jsusfx = new JsusFxVCV(fxpath, effectPath);
  jsusfx->init();

  jsusfx->gfx = new JsusFxGfx_VCV();
  jsusfx->gfx->init(jsusfx->m_vm);

  auto compiled = jsusfx->compile(fxpath, fullpath, JsusFx::kCompileFlag_CompileGraphicsSection);
  if (!compiled) {
    warn("JSFX With Gfx Load Failed: %s", effectPath.c_str());
  
    auto compiled = jsusfx->compile(fxpath, fullpath, 0);
    if (!compiled) {
      warn("JSFX Without Gfx Load Failed: %s", effectPath.c_str());
      return NULL;
    }
  }

  auto module = new JSFXModule(jsusfx);
  auto moduleWidget = new JSFXModuleWidget(module);
  moduleWidget->model = this;
  return moduleWidget;
}

ModuleWidget *JSFXModel::createModuleWidgetNull()
{
  fatal("Creating a NULL JSFX ModuleWidget is not supported");
  return NULL;
}
