#include "IndexBuffer.h"
#include"Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	glGenBuffers(1, &m_RendererID);//1. how many buffers. 2. bufferId returned.

	//1. the buffer we input is an array. 2. bufferId.
	//the binded buffer is the thing to draw. (state machine)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

	//specify the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW);//1. buffer type. 2. size of buffer. 3. the real buffer. 4. usage hint

}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
