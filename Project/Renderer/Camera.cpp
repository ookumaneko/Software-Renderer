#include "Camera.h"
#include <math.h>
using namespace Maths;

namespace renderer
{

ViewFrustum::ViewFrustum()
{
	Left.Position = Maths::Vector4::ZERO;
	Left.Normal = Maths::Vector4( -1.0f, 0.0f, 1.0f, 1.0f );

	this->Right.Position = Maths::Vector4::ZERO;
	this->Right.Normal = Maths::Vector4( 1.0f, 0.0f, 1.0f, 1.0f );

	this->Top.Position = Maths::Vector4::ZERO;
	this->Top.Normal = Maths::Vector4( 0.0f, -1.0f, 1.0f, 1.0f );

	this->Bottom.Position = Maths::Vector4::ZERO;
	this->Bottom.Normal = Maths::Vector4( 0.0f, 1.0f, 1.0f, 1.0f );

	//this->Near.Position = Maths::Vector4::ZERO;
	//this->Near.Normal = Maths::Vector4::ZERO;
}

Camera::Camera() : m_viewMatrix( Matrix4::IDENTITY ), m_projectionMatrix( Matrix4::IDENTITY ),
	m_screenTransform( Matrix4::IDENTITY ), m_position( 0.0f, 0.0f, 0.0f, 1.0f ), m_aspectRatio( 4.0f / 3.0f ),
	m_fov( 90.0f ), m_nearZ( 10.0f ), m_farZ( 500.0f ), m_screenWidth( 800 ), m_screenHeight( 600 )
{
}

Camera::Camera(int width, int height, float fov, float nearZ, float farZ) : 
	m_viewMatrix( Matrix4::IDENTITY ), m_projectionMatrix( Matrix4::IDENTITY ),
	m_screenTransform( Matrix4::IDENTITY ), m_position( 0.0f, 0.0f, 0.0f, 1.0f ), m_aspectRatio( 4.0f / 3.0f ),
	m_fov( fov ), m_nearZ( nearZ ), m_farZ( farZ ), m_screenWidth( width ), m_screenHeight( height )
{
}

Camera::Camera(const Camera &camera)
{
	//TODO:
}

Camera::~Camera()
{

}

Camera& Camera::operator =(const Camera &camera)
{
	//TODO:
	return *this;
}

////Rotate and translate view matrx
//void Camera::TransformViewMatrix(const Maths::Vector4& position, float rotateX, float rotateY, float rotateZ)
//{
//	Matrix4 left;
//	Matrix4 out = m_viewMatrix;
//	Matrix4 a = m_viewMatrix;
//	Matrix4 temp;
//
//	m_position += position;
//	m_position.W = 1;
//
//	Matrix4::InverseTranslation( Matrix4::IDENTITY, position.X, position.Y, position.Z, left );
//	Matrix4::InverseRotateX( left, rotateX, temp);
//	Matrix4::InverseRotateY( temp, rotateY, left);
//	Matrix4::InverseRotateZ( left, rotateZ, temp);
//	Matrix4::Multiply(temp, a, m_viewMatrix);
//	//Matrix4::Transform( m_viewMatrix, Vector4::Vector4(1, 1, 1, 1) , m_position );
//}

void Camera::Translate(const Vector4& translation)
{
	m_position += translation;
	m_lookAt += translation;
	BuildViewMatrix( m_position, m_lookAt, m_up );
}

void Camera::TranslateTo(const Vector4& location)
{
	m_position = location;
	BuildViewMatrix( m_position, m_lookAt, m_up );
}

void Camera::BuildViewMatrix(const Maths::Vector4 &position, const Maths::Vector4 &lookAt, const Maths::Vector4 &up)
{
	Vector4 viewDir = lookAt - position;
	Vector4 viewSide, viewUp;
	
	// store values
	m_up = up;
	m_position = position;
	m_lookAt = lookAt;

	viewDir.Normalize();
	viewUp = up - viewDir * up.DotProduct( viewDir );
	viewUp.Normalize();
	viewSide = viewDir.CrossProduct( viewUp );

	// setup inverse rotation matrix
	Matrix4 rotation;
	rotation.SetRows( viewSide, viewUp, Vector4( -viewDir.X, -viewDir.Y, -viewDir.Z, -viewDir.W ), Vector4( 0.0f, 0.0f, 0.0f, 1.0f ) );

	//transform translation
	Vector4 invPos;
	Matrix4::Transform( rotation, position, invPos );
	m_inversePosition = -invPos;

	// build view matrix
	Matrix4 view;
	Matrix4::Multiply( view, rotation, m_viewMatrix );
	m_viewMatrix( 0, 3 ) = m_inversePosition.X;
	m_viewMatrix( 1, 3 ) = m_inversePosition.Y;
	m_viewMatrix( 2, 3 ) = m_inversePosition.Z;
	m_viewMatrix( 3, 3 ) = m_inversePosition.W;

	m_viewDir = viewDir;
}

void Camera::BuildProjectionMatrix()
{
	float d = 1.0f;
	//float d = tan( Maths::MathHelper::ToRadian( m_fov ) / 2 );
	m_projectionMatrix( 0, 0 ) = -d;
	m_projectionMatrix( 1, 1 ) = -d * m_aspectRatio;
	m_projectionMatrix( 2, 2 ) = 1.0f;
	//m_projectionMatrix._m[2][2] = -d; 
	m_projectionMatrix( 3, 2 ) = 1.0f;
	m_projectionMatrix( 3, 3 ) = 0.0f;
}

void Camera::BuildScreenMatrix()
{
	float w = (float)m_screenWidth - 1;
	float h = (float)m_screenHeight - 1;

	w /= 2;
	h /= 2;
	
	m_screenTransform( 0, 0 ) = w;
	m_screenTransform( 0, 3 ) = w;
	m_screenTransform( 1, 1 ) = -h;
	m_screenTransform( 1, 3 ) = h;
}

}