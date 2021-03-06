#include "pch.h"
#include "OpenGLVertexArray.h"
#include "glew/glew.h"

namespace Argit {
	static uint32_t getOpenglType(LayoutDataType type) {
		switch (type)
		{
		case Argit::LayoutDataType::Int:
			return GL_INT;
			break;
		case Argit::LayoutDataType::Float:
			return GL_FLOAT;
			break;
		default:
			break;
		}
	}

	static size_t getTypeSize(LayoutDataType type) {
		switch (type)
		{
		case Argit::LayoutDataType::Int:
			return sizeof(int);
			break;
		case Argit::LayoutDataType::Float:
			return sizeof(float);
			break;
		default:
			break;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray() : m_RendererId(0)
	{
		glGenVertexArrays(1, &m_RendererId);
		glBindVertexArray(m_RendererId);
	}

	void OpenGLVertexArray::AddBuffer(const Reference<VertexBuffer>& buffer, LayoutDescription layout)
	{
		int stride = 0;
		for (auto& elem : layout.elements) {
			size_t typeSize = getTypeSize(elem.type) * elem.count;
			stride += typeSize;
		}
		glBindVertexArray(m_RendererId);
		buffer->Bind();

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const void*)0);
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (const void*)12);
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (const void*)24);
		//glEnableVertexAttribArray(3);
		//glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, stride, (const void*)32);

		int offset = 0;
		int index = 0;
		for (auto& elem : layout.elements){
			size_t typeSize = getTypeSize(elem.type) * elem.count;
			uint32_t normalize = elem.normalize ? GL_TRUE : GL_FALSE;

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, elem.count, getOpenglType(elem.type), normalize, stride, (const void*)offset);

			offset += typeSize;
			index++;
		}
	}

	RendererId OpenGLVertexArray::getRendererId()
	{
		return m_RendererId;
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

}