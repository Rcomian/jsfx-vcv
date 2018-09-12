#pragma once

#include "rack.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/jsusfx_gfx.h"


struct JsusFxGfx_VCV : JsusFxGfx {
  NVGcontext *vg;

	virtual void gfx_line(int np, EEL_F ** params) override;
	virtual void gfx_rect(int np, EEL_F ** params) override;
	virtual void gfx_circle(EEL_F x, EEL_F y, EEL_F radius, bool fill, bool aa) override;
	virtual void gfx_triangle(EEL_F ** params, int np) override;
	
	virtual void gfx_lineto(EEL_F xpos, EEL_F ypos, EEL_F useaa) override;
	virtual void gfx_rectto(EEL_F xpos, EEL_F ypos) override;
	virtual void gfx_arc(int np, EEL_F ** params) override;
	virtual void gfx_set(int np, EEL_F ** params) override;
	
	virtual void gfx_roundrect(int np, EEL_F ** params) override;
	
	virtual void gfx_grad_or_muladd_rect(int mod, int np, EEL_F ** params) override;
	
	virtual void gfx_drawnumber(EEL_F n, int nd) override;
	virtual void gfx_drawchar(EEL_F n) override;
	virtual void gfx_drawstr(void * opaque, EEL_F ** parms, int np, int mode) override;
	
	virtual void gfx_setpixel(EEL_F r, EEL_F g, EEL_F b) override;
	virtual void gfx_getpixel(EEL_F * r, EEL_F * g, EEL_F * b) override;

	// virtual EEL_F gfx_loadimg(JsusFx & jsusFx, int img, EEL_F loadFrom) override;
	virtual void gfx_getimgdim(EEL_F img, EEL_F * w, EEL_F * h) override;
	// virtual EEL_F gfx_setimgdim(int img, EEL_F * w, EEL_F * h) override;
	
	// virtual EEL_F gfx_setfont(int np, EEL_F ** parms) override;
	// virtual EEL_F gfx_getfont(int np, EEL_F ** parms) override;
	
	// virtual EEL_F gfx_showmenu(EEL_F ** parms, int nparms) override;
	// virtual EEL_F gfx_setcursor(EEL_F ** parms, int nparms) override;
	
	virtual void gfx_blurto(EEL_F x, EEL_F y) override;

	virtual void gfx_blit(EEL_F img, EEL_F scale, EEL_F rotate) override;
	virtual void gfx_blitext(EEL_F img, EEL_F * coords, EEL_F angle) override;
	virtual void gfx_blitext2(int mp, EEL_F ** params, int blitmode) override;

  void drawString(char * str);
};
