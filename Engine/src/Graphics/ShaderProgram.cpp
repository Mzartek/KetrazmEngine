#include <Engine/Graphics/ShaderProgram.hpp>

inline GLchar *readText(const GLchar *filename)
{
	std::ifstream file(filename, std::ifstream::in | std::ifstream::binary);
	GLchar *content;
	GLint size;

	if (!file.is_open())
	{
		std::exception(std::string("Error while opening file: " + std::string(filename)).c_str());
	}
	// Lenght of the file
	file.seekg(0, std::ifstream::end);
	size = (GLint)file.tellg();
	file.seekg(0, std::ifstream::beg);

	// Add content
	content = new GLchar[size + 1];
	file.read(content, size);
	content[size] = '\0';

	file.close();
	return content;
}

inline GLuint loadShader(const GLchar *filename, const GLenum &type)
{
	GLuint id;
	GLchar *content, *log;
	GLsizei logsize;
	GLint status;

	id = glCreateShader(type);
	if (id == 0)
	{
		throw std::exception("Error while creating shader");
	}

	content = readText(filename);

	glShaderSource(id, 1, (const GLchar **)&content, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logsize);

		log = new GLchar[logsize + 1];
		log[logsize] = '\0';

		glGetShaderInfoLog(id, logsize, &logsize, log);
		std::string errorMessage("Error while compiling shader: " + std::string(filename) + "\n" + log);

		glDeleteShader(id);
		delete[] log;

		throw std::exception(errorMessage.c_str());
	}

	delete[] content;
	return id;
}

Engine::Graphics::ShaderProgram::ShaderProgram(const GLchar *vs, const GLchar *tcs, const GLchar *tes, const GLchar *gs, const GLchar *fs)
	: _idProgram(0), _idVertexShader(0), _idTessControlShader(0), _idTessEvaluationShader(0), _idGeometryShader(0), _idFragmentShader(0)
{
	GLchar *log;
	GLsizei logsize;
	GLint status;

	_idProgram = glCreateProgram();
	if (_idProgram == 0)
	{
		throw std::exception("Error while creating program");
	}

	if (vs != NULL)
	{
		_idVertexShader = loadShader(vs, GL_VERTEX_SHADER);
		glAttachShader(_idProgram, _idVertexShader);
	}

	if (tcs != NULL)
	{
		_idTessControlShader = loadShader(tcs, GL_TESS_CONTROL_SHADER);
		glAttachShader(_idProgram, _idTessControlShader);
	}

	if (tes != NULL)
	{
		_idTessEvaluationShader = loadShader(tes, GL_TESS_EVALUATION_SHADER);
		glAttachShader(_idProgram, _idTessEvaluationShader);
	}

	if (gs != NULL)
	{
		_idGeometryShader = loadShader(gs, GL_GEOMETRY_SHADER);
		glAttachShader(_idProgram, _idGeometryShader);
	}

	if (fs != NULL)
	{
		_idFragmentShader = loadShader(fs, GL_FRAGMENT_SHADER);
		glAttachShader(_idProgram, _idFragmentShader);
	}

	glLinkProgram(_idProgram);

	glGetProgramiv(_idProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetProgramiv(_idProgram, GL_INFO_LOG_LENGTH, &logsize);

		log = new GLchar[logsize + 1];
		log[logsize] = '\0';

		glGetProgramInfoLog(_idProgram, logsize, &logsize, log);
		std::string errorMessage("Error while linking program: " + std::to_string(_idProgram) + "\n" + log);

		delete[] log;

		throw std::exception(errorMessage.c_str());
	}
}

Engine::Graphics::ShaderProgram::ShaderProgram(const GLchar *vs, const GLchar *tcs, const GLchar *tes, const GLchar *gs, const GLchar *fs, const GLchar **varyings, GLsizei count)
	: _idProgram(0), _idVertexShader(0), _idTessControlShader(0), _idTessEvaluationShader(0), _idGeometryShader(0), _idFragmentShader(0)
{
	GLchar *log;
	GLsizei logsize;
	GLint status;

	_idProgram = glCreateProgram();
	if (_idProgram == 0)
	{
		throw std::exception("Error while creating program");
	}

	if (vs != NULL)
	{
		_idVertexShader = loadShader(vs, GL_VERTEX_SHADER);
		glAttachShader(_idProgram, _idVertexShader);
	}

	if (tcs != NULL)
	{
		_idTessControlShader = loadShader(tcs, GL_TESS_CONTROL_SHADER);
		glAttachShader(_idProgram, _idTessControlShader);
	}

	if (tes != NULL)
	{
		_idTessEvaluationShader = loadShader(tes, GL_TESS_EVALUATION_SHADER);
		glAttachShader(_idProgram, _idTessEvaluationShader);
	}

	if (gs != NULL)
	{
		_idGeometryShader = loadShader(gs, GL_GEOMETRY_SHADER);
		glAttachShader(_idProgram, _idGeometryShader);
	}

	if (fs != NULL)
	{
		_idFragmentShader = loadShader(fs, GL_FRAGMENT_SHADER);
		glAttachShader(_idProgram, _idFragmentShader);
	}

	glTransformFeedbackVaryings(_idProgram, count, varyings, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram(_idProgram);

	glGetProgramiv(_idProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetProgramiv(_idProgram, GL_INFO_LOG_LENGTH, &logsize);

		log = new GLchar[logsize + 1];
		log[logsize] = '\0';

		glGetProgramInfoLog(_idProgram, logsize, &logsize, log);
		std::string errorMessage("Error while linking program: " + std::to_string(_idProgram) + "\n" + log);

		delete[] log;

		throw std::exception(errorMessage.c_str());
	}
}

Engine::Graphics::ShaderProgram::~ShaderProgram(void)
{
	if (glIsProgram(_idProgram)) glDeleteProgram(_idProgram);
	if (glIsShader(_idVertexShader)) glDeleteShader(_idVertexShader);
	if (glIsShader(_idTessControlShader)) glDeleteShader(_idTessControlShader);
	if (glIsShader(_idTessEvaluationShader)) glDeleteShader(_idTessEvaluationShader);
	if (glIsShader(_idGeometryShader)) glDeleteShader(_idGeometryShader);
	if (glIsShader(_idFragmentShader)) glDeleteShader(_idFragmentShader);
}

GLuint Engine::Graphics::ShaderProgram::getId(void) const
{
	return _idProgram;
}
