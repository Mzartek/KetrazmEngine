#ifndef GL_HEAD
#define GL_HEAD

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <cassert>
#include <cctype>
#include <cmath>
#include <cstring>

#ifdef WIN
#include <GL/glew.h>
#else
#define GL_GLEXT_PROTOTYPES
#endif
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "matrix.h"

namespace engine
{
  enum pixelFormat {UNKNOWN, RGB, BGR, RGBA};
  extern pixelFormat testFormat(unsigned f);
  extern void loadTex(const std::string path, GLuint *texture);
}

#endif