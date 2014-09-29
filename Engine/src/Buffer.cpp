#include "Engine/Buffer.hpp"

Engine::Buffer::Buffer(void)
	: _target(GL_ARRAY_BUFFER), _idBuffer(0), _size(0)
{
}

Engine::Buffer::~Buffer(void)
{
	if (glIsBuffer(_idBuffer)) glDeleteBuffers(1, &_idBuffer);
}

GLenum Engine::Buffer::getTarget(void)
{
	return _target;
}

GLuint Engine::Buffer::getId(void)
{
	return _idBuffer;
}

void Engine::Buffer::createStore(const GLenum &target, const GLvoid *data, const GLsizeiptr &size, const GLenum &usage)
{
	_target = target;
	_size = size;

	if (_target == GL_UNIFORM_BUFFER)
	{
		if ((size % 16) != 0)
		{
			std::cerr << "Need a power of 16 for Uniform Buffer" << std::endl;
			exit(1);
		}
	}

	if (glIsBuffer(_idBuffer)) glDeleteBuffers(1, &_idBuffer);
	glGenBuffers(1, &_idBuffer);
	glBindBuffer(_target, _idBuffer);
	glBufferData(_target, _size, data, usage);
	glBindBuffer(_target, 0);
}

void Engine::Buffer::updateStoreSub(const GLvoid *data)
{
	glBindBuffer(_target, _idBuffer);
	glBufferSubData(_target, 0, _size, data);
	glBindBuffer(_target, 0);
}

void Engine::Buffer::updateStoreMap(const GLvoid *data)
{
	void *mappedResource;

	glBindBuffer(_target, _idBuffer);
	mappedResource = glMapBuffer(_target, GL_WRITE_ONLY);
	memcpy(mappedResource, data, _size);
	glUnmapBuffer(_target);
	glBindBuffer(_target, 0);
}