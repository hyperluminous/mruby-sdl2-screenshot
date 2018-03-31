
#include "mruby.h"
#include "mruby/string.h"

#include <SDL.h>
#include "sdl2.h"
#include "sdl2_render.h"

static mrb_value
mrb_sdl2_renderer_screenshot(mrb_state *mrb, mrb_value self)
{
  mrb_value path;
  SDL_Renderer *renderer = NULL;
  int w,h;

  mrb_get_args(mrb, "S", &path);
  renderer = mrb_sdl2_video_renderer_get_ptr(mrb,self);

  if(SDL_GetRendererOutputSize(renderer,&w,&h)<0){
    printf("SDL_GetRendererOutputSize failed: %s\n", SDL_GetError());
  }else{
    SDL_Surface *ss = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, ss->pixels, ss->pitch);
    SDL_SaveBMP(ss, RSTRING_PTR(path));
    SDL_FreeSurface(ss);
  }
  return self;
}

void
mrb_mruby_sdl2_screenshot_gem_init(mrb_state *mrb)
{
  struct RClass *mod_Video;
  struct RClass *class_Renderer;

  mod_Video      = mrb_module_get_under   (mrb, mod_SDL2,  "Video");
  class_Renderer = mrb_class_get_under    (mrb, mod_Video, "Renderer");

  mrb_define_method(mrb, class_Renderer, "screenshot", mrb_sdl2_renderer_screenshot, MRB_ARGS_REQ(1));
}

void
mrb_mruby_sdl2_screenshot_gem_final(mrb_state *mrb)
{
}
