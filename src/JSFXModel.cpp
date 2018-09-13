#include "../include/JSFXModel.hpp"
#include "../include/JSFXModule.hpp"
#include "../include/JSFXModuleWidget.hpp"
#include "../include/JsusFxVCV.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx.h"
#include "../include/JsusFxGfx_VCV.hpp"

using namespace rack;
using namespace std;


JsusFxVCV* JSFXModel::compileEngine()
{
  string fullpath = assetLocal("jsfx") + '/' + effectPath;
  JsusFxPathLibrary_Basic fxpath(fullpath.c_str());
  auto jsusfx = new JsusFxVCV(fxpath, effectPath);
  jsusfx->init();

  jsusfx->gfx = new JsusFxGfx_VCV();
  jsusfx->gfx->init(jsusfx->m_vm);

  int flags = 0;
  if (useGfx) {
    flags = JsusFx::kCompileFlag_CompileGraphicsSection;
  }

  auto compiled = jsusfx->compile(fxpath, fullpath, flags);
  if (!compiled) {
    warn("JSFX With Load Failed: %s", effectPath.c_str());
  
    return NULL;
  }

  return jsusfx;
}

ModuleWidget *JSFXModel::createModuleWidget()
{
  auto jsusfx = compileEngine();
  
  if (jsusfx == NULL) { return NULL; }

  auto module = new JSFXModule(jsusfx);
  auto moduleWidget = new JSFXModuleWidget(module, jsusfx);
  moduleWidget->model = this;
  return moduleWidget;
}

ModuleWidget *JSFXModel::createModuleWidgetNull()
{
  auto jsusfx = compileEngine();
  
  if (jsusfx == NULL) { return NULL; }

  auto moduleWidget = new JSFXModuleWidget(NULL, jsusfx);
  moduleWidget->model = this;
  return moduleWidget;
}
