#ifndef _RENDER_OBJECT_H_
#define _RENDER_OBJECT_H_

#include "Matrix4.h"
#include "Vector3.h"
#include "Mesh.h"

namespace demoscene
{
	class RenderObject
	{
		public:

			// constructor and destructor
			RenderObject(void){};
			RenderObject(const renderer::Mesh& model, const Maths::Vector3& position, const Maths::Vector3& rotation, float scale);
			RenderObject(const RenderObject& obj);
			virtual ~RenderObject(void);

			// Accessors
			inline void SetTranslate	(const Maths::Vector3& translate)	{ m_position = translate; }
			inline void SetRotation		(const Maths::Vector3& rotation)	{ m_rotation = rotation; }
			inline void SetScale		(float scale)						{ m_scale = scale; }

			inline void Translate	(const Maths::Vector3& translate)	{ m_position += translate; }
			inline void Rotate		(const Maths::Vector3& rotation)	{ m_rotation += rotation; }

			virtual void Initialize(const Maths::Vector3& position, const Maths::Vector3& rotation, float scale);
			virtual void Initialize(const renderer::Mesh& model, const Maths::Vector3& position, const Maths::Vector3& rotation, float scale);
			virtual void Update(float delta);
			virtual void Render(renderer::Renderer* render);

			// member variables
			renderer::Mesh		m_model;

		protected:
			Maths::Matrix4		m_transform;
			Maths::Vector3		m_position;
			Maths::Vector3		m_rotation;
			float				m_scale;
	};
} // end of namespace
#endif // end of _RENDER_OBJECT_H_