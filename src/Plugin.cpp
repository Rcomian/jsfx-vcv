#include "../include/Plugin.hpp"
#include "../include/JSFXModel.hpp"
#include "../include/JsusFxVCV.hpp"
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

void loadEffectsInPath(std::string path) {
	for (std::string jsfxPath : systemListEntries(path)) {
		if (systemIsDirectory(jsfxPath)) {

			loadEffectsInPath(jsfxPath);

		} else {

			JsusFxPathLibrary_Basic fxpath(path.c_str());
			auto jsusfx = new JsusFxVCV(fxpath, jsfxPath);
			jsusfx->init();

			auto compiled = jsusfx->compile(fxpath, jsfxPath, 0);
			if (!compiled) {
				warn("JSFX Load Failed: %s", jsfxPath.c_str());
				continue;
			}

			info("JSFX Loaded: %s", jsusfx->displayname().c_str());

			auto effectPath = jsfxPath.substr(localJSFX.length() + 1);

			auto model = new JSFXModel();
			model->author = "JSFX";
			model->slug = effectPath;
			model->name = jsusfx->displayname();
			model->effectPath = effectPath;

			plugin->addModel(model);
		}
	}
}

void init(Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	localJSFX = assetLocal("jsfx");
	mkdir(localJSFX.c_str(), 0755);
	loadEffectsInPath(localJSFX);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
