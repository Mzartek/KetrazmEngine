#ifndef SHADERPROGRAM_HEADER
#define SHADERPROGRAM_HEADER

#include "../Object.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI ShaderProgram : public Object
		{
		private:
			GLuint _idProgram;
			GLuint _idVertexShader;
			GLuint _idTessControlShader;
			GLuint _idTessEvaluationShader;
			GLuint _idGeometryShader;
			GLuint _idFragmentShader;

		public:
			ShaderProgram(const GLchar *vs, const GLchar *tcs, const GLchar *tes, const GLchar *gs, const GLchar *fs);
			ShaderProgram(const GLchar *vs, const GLchar *tcs, const GLchar *tes, const GLchar *gs, const GLchar *fs, const GLchar **varyings, GLsizei count);
			~ShaderProgram(void);
			GLuint getId(void) const;
		};
	}
}

#endif
