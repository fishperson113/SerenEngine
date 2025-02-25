#include"GameplayLayer.h"
#include<SerenEngine/Base.h>
#include<ECS/System/System.h>
using namespace SerenEngine;
GameplayLayer::GameplayLayer() {
	LOG_TRACE("GameplayLayer is created");
	CreateCameraController(1280, 720);
	Random::Init();
	m_World = new b2World(b2Vec2(0.0f, -9.8f));
}
void GameplayLayer::OnAttach() {
	/*LOG_TRACE("GameplayLayer is attached");

	MemoryManager* memoryManager = new MemoryManager();
	{
		SerenEngine::ECS::Coordinator* coordinator = memoryManager->NewOnStack<SerenEngine::ECS::Coordinator>("Coordinator");
		SerenEngine::Actor* actor = memoryManager->NewOnStack<SerenEngine::Actor>(SerenEngine::Actor::RunTimeType.GetTypeName(), coordinator);
		actor->AddComponent<SerenEngine::TransformComponent>(2.0f, 3.0f);
		SerenEngine::TransformComponent& transform = actor->GetComponent<SerenEngine::TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		transform.SetX(10.0f);
		transform.SetY(-20.0f);
		transform = actor->GetComponent<TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		if (actor->HasComponent<TransformComponent>()) {
			actor->RemoveComponent<TransformComponent>();
		}

		if (!actor->HasComponent<TransformComponent>()) {
			LOG_WARN("Actor transform component has been removed");
		}
		memoryManager->FreeOnStack(actor);
		memoryManager->FreeOnStack(coordinator);
		coordinator->~Coordinator();
	}
	memoryManager->ClearOnStack();*/
	//mTexture = Texture::Create("Assets/Textures/pngimg.com - mario_PNG109.png");
	mRenderer = Application::Get().GetRenderer();

	m_Level.Init(m_World);
	ImGuiIO& io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("Assets/OpenSans-Regular.ttf", 120.0f);
}
void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}
void GameplayLayer::OnUpdate(Time time) {

	m_Time += time.GetDeltaTime();
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_CameraController.GetCamera().SetPosition({playerPos.x, 0.0f, 0.0f});

	switch (m_State)
	{
		case GameState::Play:
		{
			m_Level.OnUpdate(time.GetDeltaTime());
			break;
		}
	}
	RenderCommand::SetClearColor( 0.0f, 0.0f, 0.0f,1.0f );

	mRenderer->BeginScene(m_CameraController.GetCamera());
	m_Level.OnRender();
	mRenderer->EndScene();

}
void GameplayLayer::OnImGuiRender()
{
	switch (m_State)
	{
		case GameState::Play:
		{
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
			break;
		}
		case GameState::MainMenu:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow()->GetWidth();
			auto height = Application::Get().GetWindow()->GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
			//m_Level.GetPlayer().OnImGuiRender();
			break;
		}
		case GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow()->GetWidth();
			auto height = Application::Get().GetWindow()->GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
			//m_Level.GetPlayer().OnImGuiRender();
			pos.x += 200.0f;
			pos.y += 150.0f;
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
			break;
		}
	}
}
bool GameplayLayer::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
	return false;
}

void GameplayLayer::OnProcessInput(const InputState& input)
{
	//m_CameraController.OnProcessInput(input);
	m_Level.GetPlayer().SetInputState(input);
}

bool GameplayLayer::OnWindowResizedEvent(const SerenEngine::WindowResizedEvent& e)
{
	CreateCameraController(e.GetWidth(), e.GetHeight());
	return false;
}

bool GameplayLayer::OnMouseButtonPressedEvent(const MouseButtonPressedEvent&)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

void GameplayLayer::CreateCameraController(uint32_t width, uint32_t height)
{
	float aspectRatio = static_cast<float>(width) / height;
	float zoomLevel = height * 0.5f;

	//perfect pixel
	float left = -aspectRatio * zoomLevel;
	float right = aspectRatio * zoomLevel;
	float bottom = -zoomLevel;
	float top = zoomLevel;

	m_CameraController.SetZoomLevel(zoomLevel);
	m_CameraController.SetAspectRatio(aspectRatio);
	m_CameraController.GetCamera().SetProjection(left,right,bottom,top);
}
