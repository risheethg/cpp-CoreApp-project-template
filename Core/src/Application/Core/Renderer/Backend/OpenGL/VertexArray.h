#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Project {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		

		void AddVertexBuffer(VertexBuffer vb, VertexBufferLayout layout);

	private:
		unsigned int m_RendererID;
	};
	 
}

