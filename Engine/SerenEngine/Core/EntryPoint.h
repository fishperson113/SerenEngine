#include "Application.h"

int main()
{
	SerenEngine::Application* app = SerenEngine::CreateApplication();
	if (app->Init())
	{
		app->Run();
	}
	app->Shutdown();
	FREE_MEMORY(app);
	return 0;
}