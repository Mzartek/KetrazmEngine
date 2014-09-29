#include "config.hpp"

Engine::Renderer *renderer;
Engine::Input *input;
Engine::FreeCam *cam;
Engine::DirLight *sun;
Engine::SpotLight *torch;
Engine::Model *sol;
Engine::Model *heli;
Engine::SkyBox *skybox;
Engine::Screen *screen;
Engine::TextArray *text;
Engine::GBuffer *gBuffer;

Engine::ShaderProgram *objectProgram;
Engine::ShaderProgram *dirLightProgram;
Engine::ShaderProgram *spotLightProgram;
Engine::ShaderProgram *vLightProgram;
Engine::ShaderProgram *shadowMapProgram;
Engine::ShaderProgram *skyboxProgram;
Engine::ShaderProgram *backgroundProgram;
Engine::ShaderProgram *screenProgram;
Engine::ShaderProgram *textProgram;

void display(GLfloat state)
{
	renderer->clear();
	gBuffer->clear();
	sun->clear();
	torch->clear();

	// Skybox
	skybox->display(gBuffer, cam);

	// Shadow Map
	sol->displayShadowMap(sun);
	heli->displayShadowMap(sun);
	sol->displayShadowMap(torch);
	heli->displayShadowMap(torch);

	// Opaque Object
	sol->display(gBuffer, cam);
	heli->display(gBuffer, cam);
	sun->display(gBuffer, cam);
	torch->display(gBuffer, cam);
	screen->background(gBuffer);

	// Transparent Object
	sol->displayTransparent(gBuffer, cam);
	heli->displayTransparent(gBuffer, cam);
	sun->display(gBuffer, cam);
	torch->display(gBuffer, cam);
	screen->background(gBuffer);

	screen->display(renderer, gBuffer, 1.0f, 1.0f, 1.0f, 1.0f);

	//text->display(renderer);
}

void idle(void)
{
	input->refresh();
	if (input->getKeyBoardState(SDL_SCANCODE_ESCAPE))
		renderer->stopLoop();
	cam->keyboardMove(input->getKeyBoardState(SDL_SCANCODE_W), input->getKeyBoardState(SDL_SCANCODE_S), input->getKeyBoardState(SDL_SCANCODE_A), input->getKeyBoardState(SDL_SCANCODE_D));
	cam->mouseMove(input->getMouseRelX(), input->getMouseRelY());
	if (input->getKeyBoardState(SDL_SCANCODE_LSHIFT))
		cam->setSpeed(0.05f);
	else
		cam->setSpeed(0.5f);

	if (input->getMouseState(SDL_BUTTON_LEFT))
		cam->setSpeed(5.0f);

	heli->matRotate(0.1f, 0, 1, 0);

	cam->position();
	sun->position(heli->getPosition(), 25);
	torch->position();
}

void reshape(GLuint w, GLuint h)
{
	cam->setPerspective(90.0f, w, h, 0.1f, 1000.0f);
}

void init(void)
{
	cam = new Engine::FreeCam;
	sun = new Engine::DirLight;
	torch = new Engine::SpotLight;
	sol = new Engine::Model;
	heli = new Engine::Model;
	skybox = new Engine::SkyBox;
	screen = new Engine::Screen;
	text = new Engine::TextArray;
	gBuffer = new Engine::GBuffer;

	objectProgram = new Engine::ShaderProgram;
	dirLightProgram = new Engine::ShaderProgram;
	spotLightProgram = new Engine::ShaderProgram;
	vLightProgram = new Engine::ShaderProgram;
	shadowMapProgram = new Engine::ShaderProgram;
	skyboxProgram = new Engine::ShaderProgram;
	backgroundProgram = new Engine::ShaderProgram;
	screenProgram = new Engine::ShaderProgram;
	textProgram = new Engine::ShaderProgram;

	configShaders();
	configBuffers();
	configText();
	configLights();
	configScreen();
	configModels();
	configSkybox();

	cam->setPositionCamera(glm::vec3(30, 10, 0));
	cam->setInitialAngle(-90, 0);
}

void kill(void)
{
	delete textProgram;
	delete screenProgram;
	delete backgroundProgram;
	delete skyboxProgram;
	delete shadowMapProgram;
	delete vLightProgram;
	delete spotLightProgram;
	delete dirLightProgram;
	delete objectProgram;

	delete gBuffer;
	delete text;
	delete screen;
	delete skybox;
	delete heli;
	delete sol;
	delete torch;
	delete sun;
	delete cam;
}

int main(int argc, char **argv)
{
	renderer = new Engine::Renderer;
	input = new Engine::Input;

	if (argc < 3)
		renderer->initWindow("Demo OpenGL", 800, 600, GL_FALSE);
	else
		renderer->initWindow("Demo OpenGL", atoi(argv[1]), atoi(argv[2]), GL_FALSE);
	renderer->setDisplayFunc(display);
	renderer->setIdleFunc(idle);
	renderer->setReshapeFunc(reshape);

	init();

	renderer->mainLoop();

	kill();

	delete renderer;
	delete input;

	std::cout << "MemState " << Engine::Object::getMemoryState() << std::endl;
	Engine::Object::saveMemoryInfo("memLost.txt");
	return 0;
}
