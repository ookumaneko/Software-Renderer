#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Matrix4.h"
#include "Vector4.h"
#include "RendererLibDef.h"

namespace renderer
{
	struct ViewPlane
	{
		Maths::Vector4 Normal;
		Maths::Vector4 Position;
	};

	struct ViewFrustum
	{
		ViewFrustum(void);

		ViewPlane Left;
		ViewPlane Right;
		ViewPlane Top;
		ViewPlane Bottom;
		ViewPlane Near;
		ViewPlane Far;
	};

	class RENDER_DECLSPEC Camera
	{
		public:

			// constructors and destructor
			Camera	(void);
			Camera	(int width, int height, float fov, float nearZ, float farZ);
			Camera	(const Camera &camera);
			~Camera	(void);

			// operator
			Camera& operator=(const Camera& camera);

			// matrix transforms
			//void BuildViewMatrix		(const Vector4& position, float rotateX, float rotateY, float rotateZ);
			void BuildViewMatrix		(const Maths::Vector4& position, const Maths::Vector4& lookAt, const Maths::Vector4& up);
			void BuildProjectionMatrix	(void);
			void BuildScreenMatrix		(void);

			// Accessors
			inline const Maths::Matrix4& GetViewMatrix			(void) const { return m_viewMatrix; } ;
			inline const Maths::Matrix4& GetProjectionMatrix	(void) const { return m_projectionMatrix; };
			inline const Maths::Matrix4& GetScreenMatrix		(void) const { return m_screenTransform; };

			inline const Maths::Vector4& GetPosition			(void) const { return m_position; }
			inline const Maths::Vector4& GetInversePosition		(void) const { return m_inversePosition; }
			inline const Maths::Vector4& GetLookAt				(void) const { return m_lookAt; }
			inline const Maths::Vector4& GetUp					(void) const { return m_up; }
			inline const Maths::Vector4& GetViewDirection		(void) const { return m_viewDir; }

			inline float GetNearZ						(void) const { return m_nearZ; };
			inline float GetFarZ						(void) const { return m_farZ; };
			inline void  SetNearZ						(float z)	 { m_nearZ = z; }
			inline void  SetFarZ						(float z)	 { m_farZ = z; }

			inline const ViewFrustum& GetFrustum		(void) const { return m_frustum; }

			// camera movements
			void Translate	(const Maths::Vector4& translation);
			void TranslateTo(const Maths::Vector4& location);

		private:

			// member variables
			ViewFrustum	   m_frustum;
			Maths::Matrix4 m_viewMatrix;
			Maths::Matrix4 m_projectionMatrix;
			Maths::Matrix4 m_screenTransform;
			Maths::Vector4 m_inversePosition;
			Maths::Vector4 m_position;
			Maths::Vector4 m_lookAt;
			Maths::Vector4 m_up;
			Maths::Vector4 m_viewDir;
			float m_fov;
			float m_nearZ;
			float m_farZ;
			float m_aspectRatio;
			int m_screenWidth;
			int m_screenHeight;
	};

}// end of namespace

#endif // end of _CAMERA_H_