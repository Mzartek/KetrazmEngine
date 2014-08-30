#include <Engine/GLObject.hpp>

engine::GLObject::GLObject(void)
{
	_idTexture = 0;
	_idVAO = 0;
	_idVBO = 0;
	_idIBO = 0;
	_idMaterialBuffer = 0;

	glGenBuffers(1, &_idMaterialBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, _idMaterialBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof _material, NULL, GL_DYNAMIC_DRAW);
}

engine::GLObject::~GLObject(void)
{
	glDeleteBuffers(1, &_idMaterialBuffer);

	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	if(glIsBuffer(_idIBO))
		glDeleteBuffers(1, &_idIBO);
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
}

void engine::GLObject::setTexture(const GLuint &id)
{
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	_idTexture = id;
}

void engine::GLObject::setAmbient(const glm::vec4 &ambient)
{
	_material.ambient = ambient;
	glBindBuffer(GL_UNIFORM_BUFFER, _idMaterialBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof _material, &_material);
}

void engine::GLObject::setDiffuse(const glm::vec4 &diffuse)
{
	_material.diffuse = diffuse;
	glBindBuffer(GL_UNIFORM_BUFFER, _idMaterialBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof _material, &_material);
}

void engine::GLObject::setSpecular(const glm::vec4 &specular)
{
	_material.specular = specular;
	glBindBuffer(GL_UNIFORM_BUFFER, _idMaterialBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof _material, &_material);
}

void engine::GLObject::setShininess(const GLfloat &shininess)
{
	_material.shininess = shininess;
	glBindBuffer(GL_UNIFORM_BUFFER, _idMaterialBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof _material, &_material);
}

GLfloat engine::GLObject::getTransparency(void)
{
	return _material.diffuse.w;
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::GLObject::load(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
			  const GLsizei &sizeIndexArray, const GLuint *indexArray)
{
	_numElement = sizeIndexArray/(GLsizei)sizeof(GLuint);

	// Vertex Array, Vertex Buffer GLObject and Index Buffer GLObject
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);

	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeVertexArray, vertexArray, GL_STATIC_DRAW);

	if(glIsBuffer(_idIBO))
		glDeleteBuffers(1, &_idIBO);
	glGenBuffers(1, &_idIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndexArray, indexArray, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(5 * sizeof(GLfloat)));

	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::GLObject::display(const GLuint &programId) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glUniform1i(glGetUniformLocation(programId, "colorTexture"), 0);
	
	glBindBufferBase(GL_UNIFORM_BUFFER, glGetUniformBlockIndex(programId, "material"), _idMaterialBuffer);

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void engine::GLObject::displayShadow(const GLint &colorLocation) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glUniform1i(colorLocation, 0);

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

int engine::comparGLObject(const void *p1, const void *p2)
{
	GLObject **obj1 = (engine::GLObject **)p1;
	GLObject **obj2 = (engine::GLObject **)p2;

	if ((*obj1)->_material.diffuse.w < (*obj2)->_material.diffuse.w)
		return 1;
	if ((*obj1)->_material.diffuse.w > (*obj2)->_material.diffuse.w)
		return -1;
	return 0;
}