#include <CoreHeader.h>

class Sandbox : public Project::Application {
public:
	Sandbox() {
		PROJECT_INFO("App Has Been initialized!");
	}

	~Sandbox() {

	}
};

Project::Application* Project::CreateApplication() {
	return new Sandbox();
}


