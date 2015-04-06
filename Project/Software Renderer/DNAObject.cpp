#include "StdAfx.h"
#include "DNAObject.h"
#include <math.h>
using namespace Maths;
using namespace renderer;

namespace demoscene
{

DNAObject::DNAObject(const Mesh& model, const Vector3& position, const Vector3& rotation, 
					 float scale, float angle, float yVelocity, float red, float green, float blue) 
					 : RenderObject( model, position, rotation, scale ), 
					 m_angleAddition( 20.0f ), m_angle( angle ), m_radius( 80.0f ), m_yVelocity( yVelocity )
{
	//m_model.SetDiffuseReflection( red, green, blue );
	m_model.SetAmbientReflection( red, green, blue );
}

DNAObject::DNAObject(const DNAObject& obj)
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

DNAObject::~DNAObject(void)
{
}

void DNAObject::Update(float delta)
{
	m_angle += m_angleAddition * delta;
	m_position.Y += m_yVelocity * delta;
	m_position.X = cosf( MathHelper::ToRadian( m_angle ) ) * m_radius;
	m_position.Z = sinf( MathHelper::ToRadian( m_angle ) ) * m_radius;

	if ( m_angle > 360.0f )
		m_angle -= 360.0f;
	else if ( m_angle < 0.0f )
		m_angle += 360.0f;

	//if ( _doLoop )
	//{
		//if ( m_yVelocity > 0.0f && m_position.Y > 270.0f )
		//{
		//	m_position.Y -= 480.0f;
		//}
		//else if ( m_yVelocity < 0 && m_position.Y < -220.0f )
		//{
		//	m_position.Y += 480.0f;		
		//}
	//}
	RenderObject::Update( delta );
}

}