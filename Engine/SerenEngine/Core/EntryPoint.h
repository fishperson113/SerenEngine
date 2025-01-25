#include "Application.h"

int main()
{
	SerenEngine::Application* app = SerenEngine::CreateApplication();
	if (app->Init())
	{
		app->Run();
	}
	app->Shutdown();
	delete app;
	return 0;
}