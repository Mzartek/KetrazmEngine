#ifndef SKELETALMODEL_HEADER
#define SKELETALMODEL_HEADER

#define SKELETAL_MODEL_MAX_BONES 200

#include "../Model.hpp"

namespace Engine
{
	namespace Graphics
	{
		struct Skeleton;
		struct Bone;

		class DLLAPI SkeletalModel : public Model
		{
			struct
			{
				glm::mat4 bones[SKELETAL_MODEL_MAX_BONES];
			} _bonesTest;

			std::shared_ptr<Buffer> _bonesBuffer;

			std::shared_ptr<Skeleton> _skeleton;
			std::vector<std::shared_ptr<Bone>> _bones;

		public:
			SkeletalModel(const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
			SkeletalModel(const std::shared_ptr<SkeletalModel> &model, const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
			~SkeletalModel(void);
			void loadFromFile(const GLchar *inFile, const GLchar *node_name = nullptr);

			void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) override;
			void displayTransparent(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) override;
			void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<Camera> &cam) override;
			void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<SpotLight> &light) override;
			void displayDepthMaps(const std::vector<std::shared_ptr<DepthMap>> &depthMaps, const std::shared_ptr<DirLight> &light) override;
		};
	}
}

#endif