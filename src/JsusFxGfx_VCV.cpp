#include "../include/JsusFxGfx_VCV.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx_gfx.h"

void JsusFxGfx_VCV::gfx_line(int np, EEL_F ** params) { }
void JsusFxGfx_VCV::gfx_rect(int np, EEL_F ** params) {
}
void JsusFxGfx_VCV::gfx_circle(EEL_F x, EEL_F y, EEL_F radius, bool fill, bool aa) { }
void JsusFxGfx_VCV::gfx_triangle(EEL_F ** params, int np) { }

void JsusFxGfx_VCV::gfx_lineto(EEL_F xpos, EEL_F ypos, EEL_F useaa) { }
void JsusFxGfx_VCV::gfx_rectto(EEL_F xpos, EEL_F ypos) { }
void JsusFxGfx_VCV::gfx_arc(int np, EEL_F ** params) { }
void JsusFxGfx_VCV::gfx_set(int np, EEL_F ** params) { }

void JsusFxGfx_VCV::gfx_roundrect(int np, EEL_F ** params) { }

void JsusFxGfx_VCV::gfx_grad_or_muladd_rect(int mod, int np, EEL_F ** params) { }

void JsusFxGfx_VCV::gfx_drawnumber(EEL_F n, int nd) { }
void JsusFxGfx_VCV::gfx_drawchar(EEL_F n) { }
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
