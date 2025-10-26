#pragma once

namespace Project {

	struct VertexBufferElement {
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type) {
			switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;

			}
		}
	};

	class VertexBufferLayout {
	public:
		VertexBufferLayout()
			: m_Stride(0) {}
		
		template<typename T>
		void Push(unsigned int count) {
			PROJECT_CORE_ASSERT(false);
		}
		
		template<>
		void Push<float>(unsigned int count) {
			m_Elements.push_back({ GL_FLOAT, count, false });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}

		template<>
		void Push<unsigned int>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const unsigned int GetStride() const { return m_Stride; }
		inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

	private:
		unsigned int m_Stride;
		std::vector<VertexBufferElement> m_Elements;
	};

}