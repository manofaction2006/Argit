#include "pch.h"
#include "OpenGLIndexBuffer.h"
#include "glew/glew.h"

namespace Argit {
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count): m_RendererId(0), count(count)
	{
		glGenBuffers(1, &m_RendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
	}
	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}
	void OpenGLIndexBuffer::AddData(int offset, void* data, uint32_t count)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, count * sizeof(uint32_t), data);
	}
	RendererId OpenGLIndexBuffer::getRendererId()
	{
		return m_RendererId;
	}
	uint32_t OpenGLIndexBuffer::getCount()
	{
		return count;
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}
}
