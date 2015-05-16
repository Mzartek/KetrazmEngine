#include "Demo.hpp"

void Demo::display(GLfloat state)
{
	UNREFERENCED_PARAMETER(state);

	// Clear Buffers
	window->clear();
	gBuffer->clear();

	nightBox->display(gBuffer, camera);

	// Opaque Object
	for (std::set<Engine::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->display(gBuffer, camera);

	for (GLuint i = 0; i < CSM_NUM; i++) depthMaps[i]->clear();
	for (std::set<Engine::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMaps(depthMaps, moon_light);
	moon_light->display(gBuffer, camera, depthMaps);

	depthMaps[0]->clear();
	for (std::set<Engine::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMap(depthMaps[0], torch_light);
	torch_light->display(gBuffer, camera, depthMaps[0]);

	screen_display->background(gBuffer);

	// Transparent Object
	for (std::set<Engine::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayTransparent(gBuffer, camera);
	moon_light->display(gBuffer, camera);
	torch_light->display(gBuffer, camera);

	screen_display->background(gBuffer);

	// Particles
	rain_particles->display(gBuffer, camera);
	smoke_particles->display(gBuffer, camera);

	screen_display->display(window, gBuffer, 1.0f, 1.0f, 1.0f, 1.0f);

	text_display->display(window);
}

void Demo::state(long long time)
{
	UNREFERENCED_PARAMETER(time);

	const glm::vec3 &camPosition = camera->getCameraPosition();

	this->manage_input();

	if (helicopter_model->getPosition().y > 3)
	{
		helicopter_model->addRotation(glm::vec3(0, 1, 0), 0.025f);
		helicopter_model->addPosition(glm::vec3(0, -1, 0));
	}

	rainEffect->setPosition(camPosition);
	smokeEffect->setPosition(helicopter_model->getPosition());

	rainEffect->updateParticles();
	smokeEffect->updateParticles();
}

void Demo::last_state(void)
{
	const glm::vec3 &camPosition = camera->getCameraPosition();
	const glm::vec3 &camForward = camera->getForwardVector();
	const glm::vec3 &camUp = camera->getUpVector();

	camera->updateData();
	moon_light->updateData(camPosition, 100, 250, 500);
	torch_light->updateData(depthMaps[0]);

	// We retrieve object to display from the octree
	object_display.clear();
	octree->removeModel(helicopter_model.get());
	octree->addModel(helicopter_model.get(), 40);
	octree->getModels(camera, object_display);

	Engine::Audio::Instance().setListenerPosition(camPosition, camForward, camUp);
}

void Demo::reshape(GLuint w, GLuint h)
{
	camera->setPerspective(glm::pi<GLfloat>() / 2, w, h, 0.1f, 1000.0f);
}