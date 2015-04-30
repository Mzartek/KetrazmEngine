#ifndef SKELETALMESH_HEADER
#define SKELETALMESH_HEADER

#include "Mesh.hpp"

namespace Engine
{
	class DLLAPI SkeletalMesh : public Mesh
	{
	public:
		struct Vertex
		{
			glm::vec3 position;
			glm::vec2 texCoord;
			glm::vec3 normal;
			glm::vec3 tangent;
			glm::ivec4 index0;
			glm::ivec4 index1;
			glm::vec4 weight0;
			glm::vec4 weight1;
		};

		SkeletalMesh(void);
		~SkeletalMesh(void);
		void load(const GLsizei &numVertex, const Vertex *vertexArray,
			const GLsizei &numIndex, const GLuint *indexArray);

		MeshType getType(void) const;
	};
}

#endif