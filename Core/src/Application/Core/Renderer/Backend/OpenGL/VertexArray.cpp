#include "pch.h"
#include "VertexArray.h"

namespace Project {

	VertexArray::VertexArray() {

	}

	VertexArray::~VertexArray() {

	}

	void VertexArray::AddVertexBuffer(VertexBuffer vb, VertexBufferLayout layout) {
		vb.Bind();
		std::vector<VertexBufferElement> elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			VertexBufferElement element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}
}