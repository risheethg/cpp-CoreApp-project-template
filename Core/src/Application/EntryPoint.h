#pragma once

#include "Application.h"

extern Project::Application* Project::CreateApplication();

  ////////////////////////////////
 ///////// Entry Point //////////
////////////////////////////////
int main() {
	Project::Application* app = Project::CreateApplication();
	app->Run();
	delete app;
}
////////////////////////