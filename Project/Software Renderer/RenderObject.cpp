#include "StdAfx.h"
#include "RenderObject.h"
using namespace Maths;

namespace demoscene
{

RenderObject::RenderObject(const renderer::Mesh& model, const Maths::Vector3& position, const Maths::Vector3& rotation, float scale)
: m_model( model ), m_position( position ), m_rotation( rotation ), m_scale( scale )
{
}

RenderObject::RenderObject(const RenderObject& obj)
{
	m_model		= obj.m_model;
	m_position	= obj.m_position;
	m_rotation	= obj.m_rotation;
	m_scale		= obj.m_scale;
	m_transform = Matrix4::IDENTITY;
}

RenderObject::~RenderObject(void)
{
}

void RenderObject::Initialize(const Maths::Vector3& position, const Maths::Vector3& rotation, float scale)
{
	m_position	= position;
	m_rotation	= rotation;
	m_scale		= scale;
}

void RenderObject::Initialize(const renderer::Mesh& model, const Maths::Vector3& position, const Maths::Vector3& rotation, float scale)
{
	m_model		= model;
	m_position	= position;
	m_rotation	= rotation;
	m_scale		= scale;
}

void RenderObject::Update(float delta)
{
	Matrix4 trans, rot, scale, world;
	Matrix4::Translation( Matrix4::IDENTITY, m_position.X, m_position.Y, m_position.Z, trans );
	Matrix4::BuildXYZRotation( m_rotation.X, m_rotation.Y, m_rotation.Z, rot );
	Matrix4::Scale( Matrix4::IDENTITY, m_scale, m_scale, m_scale, scale );
	
	Matrix4::Multiply( scale, rot, world );
	Matrix4::Multiply( world, trans, m_transform );	
}

void RenderObject::Render(renderer::Renderer* render)
{ 
	render->SetWorldMatrix( m_transform );
	render->RenderMesh( m_model );
}

}