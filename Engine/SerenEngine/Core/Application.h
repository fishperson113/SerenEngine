namespace SerenEngine
{
	struct ApplictionConfig
	{
		int WindowWidth;
		int WindowHeight;
		const char* WindowTitle;
	};
	class Application
	{
	public:
		virtual ~Application() = default;
		virtual bool Init() { return true; };
		void Run();
		virtual void Shutdown() {};
	protected:
		Application() = default;
		Application(const ApplictionConfig& config);
	private:
		ApplictionConfig m_Config;
	};
	extern Application* CreateApplication();
}