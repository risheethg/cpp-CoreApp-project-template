#pragma once

#include "Application/Core/Events/Event.h"

namespace Project {

	class Layer
	{
	public:
		Layer(const std::string& debugName);
		virtual ~Layer();
		
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnEvent(Event& event);
		virtual void OnUpdate();
	private:
		std::string m_DebugName;
	};

}