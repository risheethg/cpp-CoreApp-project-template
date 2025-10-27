#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Project {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);

	private:
		unsigned int m_RendererID;
	};
	 
}

