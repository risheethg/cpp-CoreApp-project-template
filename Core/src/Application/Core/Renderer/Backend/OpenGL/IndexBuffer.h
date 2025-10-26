#pragma once

namespace Project {

	class IndexBuffer
	{
	public:
		IndexBuffer(const void* data, unsigned int count);
		~IndexBuffer();

		void Bind();
		void Unbind();
	private:
		unsigned int m_RendererID;
	};

}