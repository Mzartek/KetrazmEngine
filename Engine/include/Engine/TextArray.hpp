#ifndef TEXT_ARRAY
#define TEXT_ARRAY

#include "Object.hpp"

namespace Engine
{
	class Texture;
	class Buffer;
	class ShaderProgram;
	class Renderer;

	class DLLAPI TextArray : public Object
	{
	private:
		TTF_Font *_font;
		Texture *_texture;
		Buffer *_vertexBuffer;
		Buffer *_MVPMatrixBuffer;
		glm::mat4 *_mat;
		ShaderProgram *_program;
		GLuint _idVAO;
		SDL_Color _color;
	public:
		TextArray(ShaderProgram *program);
		~TextArray(void);
		void setFont(const GLchar *font, const GLuint &size, const GLubyte &r, const GLubyte &g, const GLubyte &b);
		void writeScreen(const GLuint &x, const GLuint &y, const GLuint &w, const GLuint &h, Renderer *renderer, const GLchar *text);
		void writeScreen(const GLchar *text);
		void display(Renderer *renderer);
	};
}

#endif
