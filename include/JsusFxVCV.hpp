#pragma once

#include "rack.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx.h"
#include <string>

class JsusFxVCV : public JsusFx {
public:
    JsusFxVCV(JsusFxPathLibrary &pathLibrary, std::string effectPath);

    std::string displayname();
    int numsliders();

    void displayMsg(const char *fmt, ...) override;

    void displayError(const char *fmt, ...) override;

private:
    std::string effectPath;
};
