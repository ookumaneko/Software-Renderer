#include "StdAfx.h"
#include "SideSpiralObject.h"
#include <math.h>
using namespace Maths;
using namespace renderer;

namespace demoscene
{

SideSpiralObject::SideSpiralObject(const Mesh& model, const Vector3& position, const Vector3& rotation, 
								   float scale, float angle, float yVelocity, float red, float green, float blue)
								   : DNAObject( model, position, rotation, scale, angle, yVelocity, red, green, blue )
{
	m_radius = 100.0f;
}

SideSpiralObject::~SideSpiralObject(void)
{
}

SideSpiralObject::SideSpiralObject(const SideSpiralObject &obj)
{
	m_model		= obj.m_model;
	m_position	= obj.m_position;
	m_rotation	= obj.m_rotation;
	m_scale		= obj.m_scale;
	m_transform = Matrix4::IDENTITY;
	m_yVelocity = obj.m_yVelocity;
	m_radius	= obj.m_radius;
	m_angle		= obj.m_angle;
	m_angleAddition = obj.m_angleAddition;
}

void SideSpiralObject::Update(float delta)
{
	m_angle += m_angleAddition * delta;
	m_position.X += m_yVelocity * delta;
	m_position.Y = cosf( MathHelper::ToRadian( m_angle ) ) * m_radius;
	m_position.Z = ( sinf( MathHelper::ToRadian( m_angle ) ) * m_radius ) - 250.0f;

	if ( m_angle > 360.0f )
		m_angle -= 360.0f;
	else if ( m_angle < 0.0f )
		m_angle += 360.0f;

	RenderObject::Update( delta );
}

}