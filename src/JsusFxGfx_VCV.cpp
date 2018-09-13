#include "rack.hpp"
#include "../include/JsusFxGfx_VCV.hpp"
#include "../include/JsusFxVCV.hpp"
#include "../dep/jsusfx-0.4.0b1b/src/WDL/wdlstring.h"

using namespace rack;

void JsusFxGfx_VCV::gfx_line(int np, EEL_F ** params) {
  nvgBeginPath(vg);

  if (np >= 4) {
    float x = *params[0];
    float y = *params[1];
    float x2 = *params[2];
    float y2 = *params[3];

    nvgMoveTo(vg, x, y);
    nvgLineTo(vg, x2, y2);

    nvgStrokeColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
    nvgStroke(vg);
  }
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

void JsusFxGfx_VCV::gfx_circle(EEL_F x, EEL_F y, EEL_F radius, bool fill, bool aa) {
  nvgBeginPath(vg);

  nvgCircle(vg, x, y, radius);

  if (fill) {
    nvgFillColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
    nvgFill(vg);
  } else {
    nvgStrokeColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
    nvgStroke(vg);
  }
}

void JsusFxGfx_VCV::gfx_triangle(EEL_F ** params, int np) {
  nvgBeginPath(vg);
  
  nvgMoveTo(vg, *params[0], *params[1]);

  for (int i = 2; i < np; i += 2) {
    nvgLineTo(vg, *params[i], *params[i+1]);
  }

  nvgFillColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
  nvgFill(vg);
}

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
void JsusFxGfx_VCV::gfx_arc(int np, EEL_F ** params) {
  nvgBeginPath(vg);

  float cx = *params[0];
  float cy = *params[1];
  float r = *params[2];
  float a0 = *params[3];
  float a1 = *params[4];

  nvgArc(vg, cx, cy, r, a0, a1, NVG_CW);

  nvgStrokeColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
  nvgStroke(vg);
}
void JsusFxGfx_VCV::gfx_set(int np, EEL_F ** params) {
  int i = 0;

  *m_gfx_r = *params[i++];
  if (i >= np) i--;

  *m_gfx_g = *params[i++];
  if (i >= np) i--;

  *m_gfx_b = *params[i++];
  if (i >= np) {
    *m_gfx_a = 1.f;
    return;
  };

  *m_gfx_a = *params[i++];
  if (i >= np) return;

  *m_gfx_mode = *params[i++];
  if (i >= np) return;

}

void JsusFxGfx_VCV::gfx_roundrect(int np, EEL_F ** params) {
  float x = *params[0];
  float y = *params[1];
  float w = *params[2];
  float h = *params[3];
  float radius = *params[4];

  nvgBeginPath(vg);

  nvgRoundedRect(vg, x, y, w, h, radius);
  nvgFillColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
  nvgFill(vg);
}

void JsusFxGfx_VCV::gfx_grad_or_muladd_rect(int mod, int np, EEL_F ** params) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_grad_or_muladd_rect not implemented");
  }
}

Vec JsusFxGfx_VCV::drawString(const char* str) {
  float bounds[4];
  nvgTextBounds(vg, *m_gfx_x, (*m_gfx_y) + 1, str, NULL, bounds);

  nvgBeginPath(vg);
  nvgFillColor(vg, nvgRGBA((*m_gfx_r) * 255, (*m_gfx_g) * 255, (*m_gfx_b) * 255, (*m_gfx_a) * 255));
  nvgText(vg, bounds[0],bounds[3] + ((bounds[3] - bounds[1])/2.f), str, NULL);
  nvgFill(vg);
  *m_gfx_texth = bounds[3] - bounds[1];

  *m_gfx_x = bounds[2] + 1;

  return Vec(bounds[2] - bounds[0], bounds[3] - bounds[1]);
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


static int _gfx_validate_format_specifier(const char *fmt_in, char *typeOut, 
                                         char *fmtOut, int fmtOut_sz, 
                                         char *varOut, int varOut_sz, 
                                         int *varOut_used
                                         )
{
  const char *fmt = fmt_in+1;
  int state=0;
  if (fmt_in[0] != '%') return 0; // ugh passed a non-specifier

  *varOut_used = 0;
  *varOut = 0;

  if (fmtOut_sz-- < 2) return 0;
  *fmtOut++ = '%';

  while (*fmt)
  {
    const char c = *fmt++;
    if (fmtOut_sz < 2) return 0;

    if (c == 'f'|| c=='e' || c=='E' || c=='g' || c=='G' || c == 'd' || c == 'u' || 
        c == 'x' || c == 'X' || c == 'c' || c == 'C' || c =='s' || c=='S' || c=='i') 
    {
      *typeOut = c;
      fmtOut[0] = c;
      fmtOut[1] = 0;
      return (int) (fmt - fmt_in);
    }
    else if (c == '.')
    {
      *fmtOut++ = c; fmtOut_sz--;
      if (state&(2)) break;
      state |= 2;
    }
    else if (c == '+') 
    {
      *fmtOut++ = c; fmtOut_sz--;
      if (state&(32|16|8|4)) break;
      state |= 8;
    }
    else if (c == '-' || c == ' ') 
    {
      *fmtOut++ = c; fmtOut_sz--;
      if (state&(32|16|8|4)) break;
      state |= 16;
    }
    else if (c >= '0' && c <= '9') 
    {
      *fmtOut++ = c; fmtOut_sz--;
      state|=4;
    }
    else if (c == '{')
    {
      if (state & 64) break;
      state|=64;
      if (*fmt == '.' || (*fmt >= '0' && *fmt <= '9')) return 0; // symbol name can't start with 0-9 or .

      while (*fmt != '}')
      {
        if ((*fmt >= 'a' && *fmt <= 'z') ||
            (*fmt >= 'A' && *fmt <= 'Z') ||
            (*fmt >= '0' && *fmt <= '9') ||
            *fmt == '_' || *fmt == '.' || *fmt == '#')
        {
          if (varOut_sz < 2) return 0;
          *varOut++ = *fmt++;
          varOut_sz -- ;
        }
        else
        {
          return 0; // bad character in variable name
        }
      }
      fmt++;
      *varOut = 0;
      *varOut_used=1;
    }
    else
    {
      break;
    }
  }
  return 0;
}




static int _gfx_format_strings(JsusFx *jsusfx, const char *fmt, const char *fmt_end, char *buf, int buf_sz, int num_fmt_parms, EEL_F **fmt_parms, int* params_used)
{
  *params_used = 1;

  int fmt_parmpos = 0;
  char *op = buf;
  while ((fmt_end ? fmt < fmt_end : *fmt) && op < buf+buf_sz-128)
  {
    if (fmt[0] == '%' && fmt[1] == '%') 
    {
      *op++ = '%';
      fmt+=2;
    }
    else if (fmt[0] == '%')
    {
      char ct=0;
      char fs[128];
      char varname[128];
      int varname_used=0;
      const int l=_gfx_validate_format_specifier(fmt,&ct,fs,sizeof(fs),varname,sizeof(varname),&varname_used);
      if (!l || !ct) 
      {
        *op=0;
        return -1;
      }

      EEL_F vv=0.0;
      const EEL_F *varptr = NULL;
      if (varname_used)
      {
        static bool named_var_warned = false;
        if (!named_var_warned) {
          named_var_warned = true;
          warn("_gfx_format_strings: cannot format named variable: %s", varname);
        }
      }
      else
      {
        if (fmt_parmpos < num_fmt_parms) {
          varptr = fmt_parms[fmt_parmpos];
          fmt_parmpos++;
          *params_used += 1;
        }
      }
      double v = varptr ? (double)*varptr : 0.0;

      if (ct == 's' || ct=='S')
      {
        WDL_FastString *wr=NULL;
        const char *str = jsusfx->getString(v,&wr);
        const int maxl=(int) (buf+buf_sz - 2 - op);
        if (wr && !fs[2]) // %s or %S -- todo: implement padding modes for binary compat too?
        {
          int wl = wr->GetLength();
          if (wl > maxl) wl=maxl;
          memcpy(op,wr->Get(),wl);
          op += wl;
          *op=0;
        }
        else
        {
          snprintf(op,maxl,fs,str ? str : "");
        }
      }
      else
      {
        if (varptr == &vv) // passed %{#str}d etc, convert to float
        {
          const char *str = jsusfx->getString(v,NULL);
          v = str ? atof(str) : 0.0;
        }

        if (ct == 'x' || ct == 'X' || ct == 'd' || ct == 'u' || ct=='i')
        {
          snprintf(op,64,fs,(int) (v));
        }
        else if (ct == 'c')
        {
          *op++=(char) (int)v;
          *op=0;
        }
        else if (ct == 'C')
        {
          const unsigned int iv = (unsigned int) v;
          int bs = 0;
          if (iv &      0xff000000) bs=24;
          else if (iv & 0x00ff0000) bs=16;
          else if (iv & 0x0000ff00) bs=8;
          while (bs>=0)
          {
            const char c=(char) (iv>>bs);
            *op++=c?c:' ';
            bs-=8;
          }
          *op=0;
        }
        else
          snprintf(op,64,fs,v);
      }

      while (*op) op++;

      fmt += l;
    }
    else 
    {
      *op++ = *fmt++;
    }

  }
  *op=0;
  return (int) (op - buf);
}


static std::string _gfx_sprintf(JsusFx *jsusfx, int num_param, EEL_F **parms, int* parms_used)
{
  if (num_param<1) return "";

  if (jsusfx)
  {
    WDL_FastString * wr_fmt = nullptr;
    const char * fmt = jsusfx->getString(*(parms[0]), &wr_fmt);
    if (!fmt)
    {
      static bool format_specifier_warned = false;
      if (!format_specifier_warned) {
        format_specifier_warned = true;
        warn("_gfx_sprintf: bad format specifier passed %f (supressing future warnings)",*(parms[0]));
      }
    }
    else
    {
      char buf[16384];
      const int fmt_len = _gfx_format_strings(jsusfx,fmt,wr_fmt?(fmt+wr_fmt->GetLength()):NULL,buf,(int)sizeof(buf), (int)num_param-1, parms+1, parms_used);

      if (fmt_len>=0)
      {
        return buf;
      }
      else
      {
        static bool format_string_warned = false;
        if (!format_string_warned) {
          format_string_warned = true;
          warn("_gfx_sprintf: bad format string passed %s (supressing future warnings)",fmt);
        }
      }
    }
  }
  return "";
}



void JsusFxGfx_VCV::gfx_drawstr(void * opaque, EEL_F ** parms, int np, int mode) {
 
  int parms_used = 0;
  std::string str = _gfx_sprintf(((JsusFx*)opaque), np, parms, &parms_used);


  auto size = drawString(str.c_str());

  if (np == parms_used + 2) {
    *parms[np-2] = size.x;
    *parms[np-1] = size.y;
  }
}

void JsusFxGfx_VCV::gfx_setpixel(EEL_F r, EEL_F g, EEL_F b) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_setpixel not implemented");
  }
}

void JsusFxGfx_VCV::gfx_getpixel(EEL_F * r, EEL_F * g, EEL_F * b) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_getpixel not implemented");
  }
}

EEL_F JsusFxGfx_VCV::gfx_loadimg(JsusFx & jsusFx, int img, EEL_F loadFrom) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_loadimg not implemented");
  }
  return 0.f;
}

void JsusFxGfx_VCV::gfx_getimgdim(EEL_F img, EEL_F * w, EEL_F * h) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_getimgdim not implemented");
  }
}

EEL_F JsusFxGfx_VCV::gfx_setimgdim(int img, EEL_F * w, EEL_F * h) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_setimgdim not implemented");
  }
  return 0.f;
}

EEL_F JsusFxGfx_VCV::gfx_setfont(int np, EEL_F ** parms) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_setfont not implemented");
  }
  return 0.f;
}

EEL_F JsusFxGfx_VCV::gfx_getfont(int np, EEL_F ** parms) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_getfont not implemented");
  }
  return 0.f;
}

EEL_F JsusFxGfx_VCV::gfx_showmenu(EEL_F ** parms, int nparms) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_showmenu not implemented");
  }
  return 0.f;
}

EEL_F JsusFxGfx_VCV::gfx_setcursor(EEL_F ** parms, int nparms) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_setcursor not implemented");
  }
  return 0.f;
}

void JsusFxGfx_VCV::gfx_blurto(EEL_F x, EEL_F y) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_blurto not implemented");
  }
}

void JsusFxGfx_VCV::gfx_blit(EEL_F img, EEL_F scale, EEL_F rotate) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_blit not implemented");
  }
}

void JsusFxGfx_VCV::gfx_blitext(EEL_F img, EEL_F * coords, EEL_F angle) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_blitext not implemented");
  }
}

void JsusFxGfx_VCV::gfx_blitext2(int mp, EEL_F ** params, int blitmode) {
  static bool warned = false;
  if (!warned) {
    warned = true;
    warn("gfx_blitext2 not implemented");
  }
}
