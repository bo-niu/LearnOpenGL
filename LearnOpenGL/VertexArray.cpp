#include "VertexArray.h"
#include"Renderer.h"
#include "VertexBufferLayout.h"


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));

}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size();i++) {
		const auto& element = elements[i];

		GLCall(glEnableVertexAttribArray(i));
		//how many attributes a vertex has, how many times the function we have to call for each attribute.
		//GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));//the last two: 1. stride to next vertex. 2. offset to next attribute.
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		///important: glVertexAttribPointer link current bound buffer to current vao
		///index buffer is a seperate thing.

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);


		//void glVertexAttribPointer(GLuint index,
		//	GLint size,
		//	GLenum type,
		//	GLboolean normalized,
		//	GLsizei stride,
		//	const GLvoid * pointer);

		//	index
		//	Specifies the index of the generic vertex attribute to be modified.

		//	size
		//	Specifies the number of components per generic vertex attribute.Must be 1, 2, 3, 4. Additionally, the symbolic constant GL_BGRA is accepted by glVertexAttribPointer.The initial value is 4.

		//	type
		//	Specifies the data type of each component in the array.The symbolic constants GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, and GL_UNSIGNED_INT are accepted by glVertexAttribPointerand glVertexAttribIPointer.Additionally GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REVand GL_UNSIGNED_INT_10F_11F_11F_REV are accepted by glVertexAttribPointer.GL_DOUBLE is also accepted by glVertexAttribLPointerand is the only token accepted by the type parameter for that function.The initial value is GL_FLOAT.

		//	normalized
		//	For glVertexAttribPointer, specifies whether fixed - point data values should be normalized(GL_TRUE) or converted directly as fixed - point values(GL_FALSE) when they are accessed.

		//	stride
		//	Specifies the byte offset between consecutive generic vertex attributes.If stride is 0, the generic vertex attributes are understood to be tightly packed in the array.The initial value is 0.

		//	pointer
		//	Specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target.The initial value is 0.

	}

	
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
