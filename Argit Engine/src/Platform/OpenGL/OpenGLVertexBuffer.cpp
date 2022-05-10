#include "pch.h"
#include "OpenGLVertexBuffer.h"
#include "glew/glew.h"

namespace Argit {
	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size): m_RendererId(0)
	{
		glGenBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}
	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}
	void OpenGLVertexBuffer::AddData(int offset, void* data, size_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}
	RendererId OpenGLVertexBuffer::getRendererId()
	{
		return m_RendererId;
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}
}
