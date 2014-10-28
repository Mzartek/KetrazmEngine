#ifndef CONFIG
#define CONFIG

#include <ctime>

#include <Engine/Renderer.hpp>
#include <Engine/Input.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/PlayerCam.hpp>
#include <Engine/SkyBox.hpp>
#include <Engine/Model.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/SpotLight.hpp>
#include <Engine/Screen.hpp>
#include <Engine/TextArray.hpp>

#include "Player.hpp"
#include "Cepe.hpp"
#include "Phalloide.hpp"
#include "Satan.hpp"

class GameManager : public Engine::GameLoop
{
private:
	Engine::Renderer *renderer;
	Engine::Input *input;

	Engine::ShaderProgram *skyboxProgram;
	Engine::ShaderProgram *objectProgram;
	Engine::ShaderProgram *dirLightProgram;
	Engine::ShaderProgram *spotLightProgram;
	Engine::ShaderProgram *shadowMapProgram;
	Engine::ShaderProgram *backgroundProgram;
	Engine::ShaderProgram *screenProgram;
	Engine::ShaderProgram *textProgram;

	Engine::GBuffer *gBuffer;
	Player *player;
	Engine::SkyBox *skybox;
	Engine::Model *sol;
	Cepe *model_cepe;
	Phalloide *model_phalloide;
	Satan *model_satan;
	std::vector<Cepe *> *vector_cepe;
	std::vector<Phalloide *> *vector_phalloide;
	std::vector<Satan *> *vector_satan;
	Engine::SpotLight *torch;
	Engine::Screen *screen;
	Engine::TextArray *text;
	void configSol(void);
	void configChamp(void);
public:
	GameManager(Engine::Renderer *r, Engine::Input *i);
	~GameManager(void);
	void display(GLfloat state);
	void idle(void);
	void reshape(GLuint w, GLuint h);
	void launch(void);
};




#endif
