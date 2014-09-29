#include <Engine/Light.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>

Engine::Light::Light(void)
{
	glGenVertexArrays(1, &_idVAO);
	_vertexBuffer = new Buffer;
	_shadowMatrixBuffer = new Buffer;
	_IVPMatrixBuffer = new Buffer;
	_screenBuffer = new Buffer;
	_cameraBuffer = new Buffer;
	_lightInfoBuffer = new Buffer;
	_VPMatrix = new glm::mat4;
	_shadow = new ShadowMap;
}

Engine::Light::~Light(void)
{
	glDeleteVertexArrays(1, &_idVAO);
	delete _vertexBuffer;
	delete _shadowMatrixBuffer;
	delete _IVPMatrixBuffer;
	delete _screenBuffer;
	delete _cameraBuffer;
	delete _lightInfoBuffer;
	delete _VPMatrix;
	delete _shadow;
}

void Engine::Light::configShadowMap(const GLuint &width, const GLuint &height)
{
	_shadow->config(width, height);
}

glm::mat4 Engine::Light::getVPMatrix(void) const
{
	return *_VPMatrix;
}

Engine::ShadowMap *Engine::Light::getShadowMap(void)
{
	return _shadow;
}

void Engine::Light::clear(void) const
{
	_shadow->clear();
}
