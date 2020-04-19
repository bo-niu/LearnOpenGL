#include "VertexBuffer.h"
#include"Renderer.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_RendererID);//1. how many buffers. 2. bufferId returned.

	//1. the buffer we input is an array. 2. bufferId.
	//the binded buffer is the thing to draw. (state machine)
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

	//specify the data
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);//1. buffer type. 2. size of buffer. 3. the real buffer. 4. usage hint

}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
