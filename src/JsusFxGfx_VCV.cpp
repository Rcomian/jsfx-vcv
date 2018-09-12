#include "rack.hpp"
#include "../include/JsusFxGfx_VCV.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx_gfx.h"

using namespace rack;

void JsusFxGfx_VCV::gfx_line(int np, EEL_F ** params) {
  nvgBeginPath(vg);

  if (np >= 4) {
    float x = *params[0];
    float y = *params[1];
    float x2 = *params[2];
    float y2 = *params[3];

    nvgLine(vg, x, y, x2, y2);
    nvgStrokeColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
    nvgStroke(vg);
}
void JsusFxGfx_VCV::gfx_rect(int np, EEL_F ** params) {
  nvgBeginPath(vg);

  if (np >= 4) {
    float x = *params[0];
    float y = *params[1];
    float w = *params[2];
    float h = *params[3];

    nvgRect(vg, x, y, w, h);
    nvgFillColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
    nvgFill(vg);
  }
}

void JsusFxGfx_VCV::gfx_circle(EEL_F x, EEL_F y, EEL_F radius, bool fill, bool aa) { }
void JsusFxGfx_VCV::gfx_triangle(EEL_F ** params, int np) { }

void JsusFxGfx_VCV::gfx_lineto(EEL_F xpos, EEL_F ypos, EEL_F useaa) {
  nvgBeginPath(vg);

  nvgMoveTo(vg, *m_gfx_x, *m_gfx_y);

  nvgLineTo(vg, xpos, ypos);
  nvgStrokeColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
  nvgStroke(vg);

  *m_gfx_x = xpos;
  *m_gfx_y = ypos;
}
void JsusFxGfx_VCV::gfx_rectto(EEL_F xpos, EEL_F ypos) {
  nvgBeginPath(vg);

  nvgRect(vg, *m_gfx_x, *m_gfx_y, xpos - (*m_gfx_x), ypos - (*m_gfx_y));
  nvgFillColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
  nvgFill(vg);

  *m_gfx_x = xpos;
  *m_gfx_y = ypos;
}
void JsusFxGfx_VCV::gfx_arc(int np, EEL_F ** params) { }
void JsusFxGfx_VCV::gfx_set(int np, EEL_F ** params) { }

void JsusFxGfx_VCV::gfx_roundrect(int np, EEL_F ** params) { }

void JsusFxGfx_VCV::gfx_grad_or_muladd_rect(int mod, int np, EEL_F ** params) { }

void JsusFxGfx_VCV::drawString(char* str) {
  float bounds[4];
  nvgTextBounds(vg, *m_gfx_x, (*m_gfx_y) + 1, str, NULL, bounds);

  nvgBeginPath(vg);
  nvgFillColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
  nvgText(vg, bounds[0],bounds[3], str, NULL);
  nvgFill(vg);
  *m_gfx_texth = bounds[3] - bounds[1];

  *m_gfx_x = bounds[2] + 1;
}

void JsusFxGfx_VCV::gfx_drawnumber(EEL_F n, int nd) {
  char fmt[4096];
  snprintf(fmt, 4095, "%%0.%df", nd);

  char output[4096];
  snprintf(output, 4095, fmt, n);

  drawString(output);
}

void JsusFxGfx_VCV::gfx_drawchar(EEL_F n) { 
  char output[4096];
  snprintf(output, 4095, "%c", static_cast<int>(floor(n)));

  drawString(output);
}
void JsusFxGfx_VCV::gfx_drawstr(void * opaque, EEL_F ** parms, int np, int mode) { }

void JsusFxGfx_VCV::gfx_setpixel(EEL_F r, EEL_F g, EEL_F b) { }
void JsusFxGfx_VCV::gfx_getpixel(EEL_F * r, EEL_F * g, EEL_F * b) { }

// EEL_F JsusFxGfx_VCV::gfx_loadimg(JsusFx & jsusFx, int img, EEL_F loadFrom) { }
void JsusFxGfx_VCV::gfx_getimgdim(EEL_F img, EEL_F * w, EEL_F * h) { }
// EEL_F JsusFxGfx_VCV::gfx_setimgdim(int img, EEL_F * w, EEL_F * h) { }

// EEL_F JsusFxGfx_VCV::gfx_setfont(int np, EEL_F ** parms) { }
// EEL_F JsusFxGfx_VCV::gfx_getfont(int np, EEL_F ** parms) { }

// EEL_F JsusFxGfx_VCV::gfx_showmenu(EEL_F ** parms, int nparms) { }
// EEL_F JsusFxGfx_VCV::gfx_setcursor(EEL_F ** parms, int nparms) { }

void JsusFxGfx_VCV::gfx_blurto(EEL_F x, EEL_F y) { }

void JsusFxGfx_VCV::gfx_blit(EEL_F img, EEL_F scale, EEL_F rotate) { }
void JsusFxGfx_VCV::gfx_blitext(EEL_F img, EEL_F * coords, EEL_F angle) { }
void JsusFxGfx_VCV::gfx_blitext2(int mp, EEL_F ** params, int blitmode) { }
