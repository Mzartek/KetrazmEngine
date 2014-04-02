#ifndef MODEL
#define MODEL

#include "matrix.h"
#include "Object.hpp"
#include "Vector3D.hpp"

namespace engine
{
  class Model
  {
  private:
    friend class ShadowMap;
    std::vector<Object *> _tObject;
    GLfloat _modelMatrix[16];
    ShaderProgram *_program;
    GLint _modelMatrixLocation;
  public:
    Model();
    ~Model();
    void setShaderProgram(ShaderProgram *program);
    void createObject(const GLuint &sizeVertexArray, const GLfloat *vertexArray,
		      const GLuint &sizeIndexArray, const GLuint *indexArray,
		      const std::string pathTexture,
		      const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess);
    void matIdentity(void);
    void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    Vector3D<GLfloat> getPosition(void);
    void display(void);
  };
}
    

#endif
