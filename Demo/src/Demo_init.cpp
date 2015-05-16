#include "Demo.hpp"

Demo::Demo(const std::shared_ptr<Engine::Window> &w)
	: window(w)
{
	Engine::Renderer::Instance().setGLContext(window);

	gBuffer = std::shared_ptr<Engine::GBuffer>(new Engine::GBuffer);
	for (GLuint i = 0; i < CSM_NUM; i++) depthMaps.push_back(std::shared_ptr<Engine::DepthMap>(new Engine::DepthMap));
	camera = std::shared_ptr<Engine::FreeCam>(new Engine::FreeCam(-glm::pi<GLfloat>() / 2, 0));

	octree = std::shared_ptr<Engine::Octree>(new Engine::Octree(4, glm::vec3(0, 0, 0), 1000));

	nightBox = std::shared_ptr<NightBox>(new NightBox);
	tree = std::shared_ptr<Tree>(new Tree);
	animModel = std::shared_ptr<AnimModel>(new AnimModel);
	helicopter = std::shared_ptr<Helicopter>(new Helicopter);
	ground = std::shared_ptr<Ground>(new Ground);
	moonLight = std::shared_ptr<MoonLight>(new MoonLight);
	torchLight = std::shared_ptr<TorchLight>(new TorchLight);
	rainEffect = std::shared_ptr<RainEffect>(new RainEffect);
	smokeEffect = std::shared_ptr<SmokeEffect>(new SmokeEffect);
	textDisplay = std::shared_ptr<TextDisplay>(new TextDisplay);
	screenDisplay = std::shared_ptr<ScreenDisplay>(new ScreenDisplay);

	// GBuffer config
	gBuffer->config(window->getWidth(), window->getHeight());
	for (GLuint i = 0; i < CSM_NUM; i++) depthMaps[i]->config(2048, 2048);

	// Camera config
	camera->setCameraPosition(glm::vec3(30, 5, 0));

	// Model config
	tree->getModel()->setPosition(glm::vec3(50, 0, 50));
	tree->getModel()->setRotation(glm::vec3(-glm::pi<GLfloat>() / 2, 0, 0));
	tree->getModel()->setScale(glm::vec3(5, 5, 5));

	animModel->getModel()->setPosition(glm::vec3(-25, 0, 25));
	animModel->getModel()->setRotation(glm::vec3(0, 1, 0), glm::pi<GLfloat>() / 2);

	helicopter->getModel()->setPosition(glm::vec3(-50, 304, 50));
	helicopter->getModel()->setRotation(glm::vec3(-0.1f, 0, -0.5f));
	helicopter->getModel()->setScale(glm::vec3(2, 2, 2));

	rainEffect->init(camera->getCameraPosition(), 10000);
	smokeEffect->init(helicopter->getModel()->getPosition(), 100);

	octree->addModel(ground->getModel().get(), 1000);
	octree->addModel(tree->getModel().get(), 40);
	octree->addModel(animModel->getModel().get(), 40);
	octree->addModel(helicopter->getModel().get(), 40);

	torchLight->getLight()->setPosition(glm::vec3(25, 100, -25));
	torchLight->getLight()->setDirection(glm::vec3(-1.0f, -1.0f, 1.0f));
	torchLight->getLight()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	torchLight->getLight()->setSpotCutOff(glm::pi<GLfloat>() / 4);
	torchLight->getLight()->setMaxDistance(250);

	// Text config
	textDisplay->getText()->writeScreen(0 + (window->getWidth() - (window->getWidth() / 10)), 0,
		window->getWidth() / 10, window->getHeight() / 10,
		window, "test");

	rainEffect->getSound()->setGain(0.10f);
	rainEffect->getSound()->setPitch(1.0f);
	rainEffect->getSound()->setLoop(AL_TRUE);
	rainEffect->getSound()->loadFromFile("../share/Demo/resources/sound/rain_stereo.wav", 44100, AL_FORMAT_STEREO16);

	smokeEffect->getSound()->setGain(0.75f);
	smokeEffect->getSound()->setPitch(0.75f);
	smokeEffect->getSound()->setLoop(AL_TRUE);
	smokeEffect->getSound()->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	smokeEffect->getSound()->setDistances(1.0f, 100.0f);
	smokeEffect->getSound()->loadFromFile("../share/Demo/resources/sound/fire_mono.wav", 44100, AL_FORMAT_MONO16);

	rainEffect->getSound()->play();
	smokeEffect->getSound()->play();
	
	moon_light = moonLight->getLight();
	torch_light = torchLight->getLight();
	rain_particles = rainEffect->getParticlesManager();
	smoke_particles = smokeEffect->getParticlesManager();
	text_display = textDisplay->getText();
	screen_display = screenDisplay->getScreen();
	helicopter_model = helicopter->getModel();
}

Demo::~Demo(void)
{
}