#ifndef LIGHT
#define LIGHT

#include "Object.hpp"

namespace engine
{
	class Buffer;
	class ShadowMap;
	class ShaderProgram;
	class GBuffer;
	class Camera;

	class DLLAPI Light : public Object
	{
	protected:
		GLuint _idVAO;
		Buffer *_vertexBuffer;
		Buffer *_lightInfoBuffer;
		ShaderProgram *_program;
		GLint _normalTextureLocation;
		GLint _materialTextureLocation;
		GLint _depthTextureLocation;
		GLint _shadowMapLocation;
		GLint _shadowMatrixLocation;
		GLint _IVPMatrixLocation;
		GLint _screenLocation;
		GLint _camPositionLocation;
		GLuint _lightInfoBlockIndex;
		glm::mat4 *_VPMatrix;
		ShadowMap *_shadow;
	public:
		Light(void);
		~Light(void);
		void configShadowMap(const GLuint &width, const GLuint &height);
		glm::mat4 getVPMatrix(void) const;
		ShadowMap *getShadowMap(void);
		void clear(void) const;
		virtual void display(GBuffer *gbuf, Camera *cam) = 0;
	};
}

#endif
