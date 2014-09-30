#include <Engine/Renderer.hpp>

Engine::GameLoop::GameLoop(void){}
Engine::GameLoop::~GameLoop(void){}

Engine::Renderer::Renderer(const GLchar *title, const GLint &w, const GLint &h, const GLboolean &fullScreen)
{
	Uint32 flags;

	_width = w;
	_height = h;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error init SDL: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	if (TTF_Init() < -1)
	{
		std::cerr << "Error init SDL_ttf " << TTF_GetError() << std::endl;
		TTF_Quit();
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (fullScreen == GL_TRUE)
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	else
		flags = SDL_WINDOW_OPENGL;

	_Window = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);
	if (_Window == NULL)
	{
		std::cerr << "Error while creating Window: " << SDL_GetError();
		exit(1);
	}
	_GLContext = SDL_GL_CreateContext(_Window);

	SDL_GL_SetSwapInterval(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

#ifdef WIN32
	if (glewInit())
	{
		std::cerr << "Error init GLEW" << std::endl;
		exit(1);
	}
#endif

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

Engine::Renderer::~Renderer(void)
{
	TTF_Quit();
	SDL_Quit();
}

GLuint Engine::Renderer::getWidth(void)
{
	return _width;
}

GLuint Engine::Renderer::getHeight(void)
{
	return _height;
}

SDL_Window *Engine::Renderer::getWindow(void)
{
	return _Window;
}

void Engine::Renderer::mainLoop(GameLoop *gameLoop)
{
	SDL_Event event;
	long long currentTime, newTime, frameTime;
	long long accumulator = 0;
	long long dt = 16;

	if (gameLoop == NULL)
	{
		std::cerr << "Wrong GameLoop" << std::endl;
		exit(1);
	}

	_stopLoop = false;
	gameLoop->reshape(_width, _height);
	currentTime = SDL_GetTicks();
	while (!_stopLoop)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				_stopLoop = true;
				break;
			}
		}
		newTime = SDL_GetTicks();
		frameTime = newTime - currentTime;
		currentTime = newTime;
		for (accumulator += frameTime; accumulator >= dt; accumulator -= dt)
			gameLoop->idle();
		gameLoop->display((GLfloat)accumulator / dt);
		SDL_GL_SwapWindow(_Window); 
	}
}

void Engine::Renderer::stopLoop(void)
{
	_stopLoop = true;
}

void Engine::Renderer::setState(void) const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDisable(GL_STENCIL_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::Renderer::clear(void) const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0xFF);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}