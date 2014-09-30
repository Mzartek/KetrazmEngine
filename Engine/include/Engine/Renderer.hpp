#ifndef RENDERER
#define RENDERER

#include "Object.hpp"

namespace Engine
{
	class DLLAPI GameLoop : public Object
	{
	public:
		GameLoop(void);
		~GameLoop(void);
		virtual void display(GLfloat state) = 0;
		virtual void idle(void) = 0; 
		virtual void reshape(GLuint w, GLuint h) = 0;
	};

	class DLLAPI Renderer : public Object
	{
	private:
		GLboolean _stopLoop;
		GLuint _width;
		GLuint _height;
		SDL_Window *_Window;
		SDL_GLContext _GLContext;
	public:
		Renderer(const GLchar *title, const GLint &w, const GLint &h, const GLboolean &fullScreen);
		~Renderer(void);
		GLuint getWidth(void);
		GLuint getHeight(void);
		SDL_Window *getWindow(void);
		void mainLoop(GameLoop *gameLoop);
		void stopLoop(void);
		void setState(void) const;
		void clear(void) const;
	};
}

#endif
