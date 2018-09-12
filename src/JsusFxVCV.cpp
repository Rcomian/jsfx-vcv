#include "../include/JsusFxVCV.hpp"
#include <string>

using namespace std;
using namespace rack;

JsusFxVCV::JsusFxVCV(JsusFxPathLibrary &pathLibrary, string effectPath) : JsusFx(pathLibrary) {
  this->effectPath = effectPath;
}

string JsusFxVCV::displayname() {
  if (desc[0] == '\0') {
    return effectPath;
  } else {
    desc[63] = '\0';
    return desc;
  }
}

int JsusFxVCV::numsliders() {
  uint slidercount = 0;
  for (auto slider : sliders) {
    if (slider.exists) {
      slidercount += 1;
    }
  }
  return slidercount;
}

void JsusFxVCV::displayMsg(const char *fmt, ...) {
    char output[4096];
    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(output, 4095, fmt, argptr);
    va_end(argptr);

    info("%s", output);
}

void JsusFxVCV::displayError(const char *fmt, ...) {
    char output[4096];
    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(output, 4095, fmt, argptr);
    va_end(argptr);

    warn("%s", output);
}
