#include "app.hpp"

static App* sInstance = nullptr;

App::App(const AppSpecs& specs) 
	: m_specs(specs), m_running(true)
{
	sInstance = this;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Failed to initialize SDL! Error: " << SDL_GetError() << std::endl;
	}

	if (m_specs.windowSpecs.title.empty())
		m_specs.windowSpecs.title = m_specs.name;

	m_pWindow = std::make_unique<Window>(m_specs.windowSpecs);
	m_pWindow->create();

	m_pAssetLoader = std::make_unique<AssetLoader>();
	m_pSceneManager = std::make_unique<SceneManager>();
	m_pRenderer = std::make_unique<Renderer>();

	onLoad();
}

App::~App()
{
	SDL_Quit();

	sInstance = nullptr;
}

void App::run() 
{
	m_pTime = std::make_unique<Time>();

	SDL_Event e;

	while (m_running) {
		m_pTime->updateDeltaTime();

		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_EVENT_QUIT:
				m_running = false;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (e.key.key == SDLK_ESCAPE)
					m_running = false;
				break;
			}
		}

		Input::updateState();

		onUpdate();
		m_pSceneManager->updateActiveScene();
		
		m_pWindow->beginFrame({ 46, 144, 220 });
		onRender();
		m_pSceneManager->renderActiveScene();
		m_pWindow->endFrame();

		m_pTime->updateFps();
	}
}

App& App::getInstance()
{
	return *sInstance;
}