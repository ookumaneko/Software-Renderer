#include "Vertex.h"

namespace renderer
{

Vertex::Vertex(void)
{
	this->Colour	= Gdiplus::Color::Black;
	this->Position	= Maths::Vector4::Vector4();
	this->Normal	= Maths::Vector4::ZERO;
	this->Tally		= 0;
	this->IsCulled	= false;
	this->U			= 0.0f;
	this->V			= 0.0f;
	this->SavedZ	= 0.0f;
}

Vertex::Vertex(const Maths::Vector4 &position)
{
	this->Colour	= Gdiplus::Color::Black;
	this->Position	= position;
	this->Normal	= Maths::Vector4::ZERO;
	this->Tally		= 0;
	this->IsCulled	= false;
	this->U			= 0.0f;
	this->V			= 0.0f;
	this->SavedZ	= 0.0f;
}

Vertex::Vertex(const Maths::Vector4 &position, const Gdiplus::Color &colour)
{
	this->Colour	= colour;
	this->Position	= position;
	this->Normal	= Maths::Vector4::ZERO;
	this->Tally		= 0;
	this->IsCulled	= false;
	this->U			= 0.0f;
	this->V			= 0.0f;
	this->SavedZ	= 0.0f;
}

Vertex::Vertex(const Maths::Vector4 &position, const Maths::Vector4 &normal, const Gdiplus::Color &colour)
{
	this->Colour	= colour;
	this->Position	= position;
	this->Normal	= normal;
	this->Tally		= 0;
	this->IsCulled	= false;
	this->U			= 0.0f;
	this->V			= 0.0f;
	this->SavedZ	= 0.0f;
}

Vertex::Vertex(const Vertex &vert)
{
	this->Colour	= vert.Colour;
	this->Position	= vert.Position;
	this->Normal	= vert.Normal;
	this->Tally		= vert.Tally;
	this->IsCulled	= vert.IsCulled;
	this->U			= vert.U;
	this->V			= vert.V;
	this->SavedZ	= vert.SavedZ;
}

Vertex::~Vertex(void)
{
}

Vertex& Vertex::operator =(const renderer::Vertex &vert)
{
	this->Colour	= vert.Colour;
	this->Position	= vert.Position;
	this->Normal	= vert.Normal;
	this->Tally		= vert.Tally;
	this->IsCulled	= vert.IsCulled;
	this->U			= vert.U;
	this->V			= vert.V;
	this->SavedZ	= vert.SavedZ;
	return *this;
}

} // end of namespace