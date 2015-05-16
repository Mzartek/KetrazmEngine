#ifndef SCREEN_HEADER
#define SCREEN_HEADER

#include "../Object.hpp"

#include "Buffer.hpp"
#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "Renderer.hpp"

namespace Engine
{
	class DLLAPI Screen : public Object
	{
	private:
		std::shared_ptr<Buffer> _vertexBuffer;
		std::shared_ptr<Buffer> _colorBuffer;
		std::shared_ptr<ShaderProgram> _backgroundProgram;
		std::shared_ptr<ShaderProgram> _directProgram;
		GLuint _idVAO;

	public:
		Screen(const std::shared_ptr<ShaderProgram> &backgroundProgram, const std::shared_ptr<ShaderProgram> &directProgram);
		~Screen(void);
		void background(const std::shared_ptr<GBuffer> &gbuf) const;
		void display(const std::shared_ptr<Window> &window, const std::shared_ptr<GBuffer> &gbuf, GLfloat r, GLfloat g, GLfloat b, GLfloat a) const;
	};
}

#endif