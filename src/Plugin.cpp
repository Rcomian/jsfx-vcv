#include "../include/Plugin.hpp"
#include "../include/JSFXModel.hpp"
#include "../include/JsusFxVCV.hpp"
#include "../include/JsusFxGfx_VCV.hpp"
#include <string>

#include <sys/stat.h>

#if ARCH_WIN
	#include <windows.h>
	#include <direct.h>
	#define mkdir(_dir, _perms) _mkdir(_dir)
#else
	#include <dlfcn.h>
#endif

using namespace std;

Plugin *plugin;
std::string localJSFX;

int loadEffectsInPath(std::string path) {
	int count = 0;
	for (std::string jsfxPath : systemListEntries(path)) {
		if (systemIsDirectory(jsfxPath)) {

			count += loadEffectsInPath(jsfxPath);

		} else {

			JsusFxPathLibrary_Basic fxpath(path.c_str());
			auto jsusfx = new JsusFxVCV(fxpath, jsfxPath);
			jsusfx->init();

			jsusfx->gfx = new JsusFxGfx_VCV();
			jsusfx->gfx->init(jsusfx->m_vm);

			auto compiled = jsusfx->compile(fxpath, jsfxPath, JsusFx::kCompileFlag_CompileGraphicsSection);
			if (!compiled) {
				warn("JSFX Load Failed: %s", jsfxPath.c_str());
				continue;
			}

			count++;

			info("JSFX Loaded: %s", jsusfx->displayname().c_str());

			auto effectPath = jsfxPath.substr(localJSFX.length() + 1);

			auto model = new JSFXModel();
			model->author = "JSFX";
			model->slug = "nogfx-" + effectPath;
			model->name = jsusfx->displayname();
			model->effectPath = effectPath;

			plugin->addModel(model);

			if (jsusfx->usesGfx()) {
				info("Found graphical effect: %s", jsusfx->displayname().c_str());
				auto model = new JSFXModel();
				model->author = "JSFX";
				model->slug = "gfx-" + effectPath;
				model->name = jsusfx->displayname() + "(GFX)";
				model->effectPath = effectPath;
				model->useGfx = true;

				plugin->addModel(model);
			}
		}
	}

	return count;
}

void init(Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	localJSFX = assetLocal("jsfx");
	mkdir(localJSFX.c_str(), 0755);
	auto loaded = loadEffectsInPath(localJSFX);
	if (loaded == 0) {
		p->addModel(modelInstructionsPanel);
	}

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
