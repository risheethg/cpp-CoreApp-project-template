#pragma once

#include "Application/Core/Layers/Layer.h"
#include "Application/Core/Events/Event.h"


namespace Project {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const std::string& name);
		virtual ~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		virtual void OnUpdate() override;
		virtual void Draw();

	public:
		bool CreateButton(const char* label);
		void CreateColorEditWidget(const char* label, float col[4]);

	private:

	};

}