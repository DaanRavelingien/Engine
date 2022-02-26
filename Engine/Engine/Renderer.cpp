#include "EnginePCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

#ifdef _DEBUG
//imgui includes
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"
#endif // _DEBUG

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

#ifdef _DEBUG
	//setting up imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
#endif // _DEBUG

}

void Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
#ifdef _DEBUG
	//rendering imgui
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	SceneManager::GetInstance().RenderGui();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
#endif // _DEBUG

	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
#ifdef _DEBUG
	//destroying the stuff from imgui
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
#endif // _DEBUG


	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, glm::vec4 dstRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(dstRect.x);
	dst.y = static_cast<int>(dstRect.y);
	dst.w = static_cast<int>(dstRect.z);
	dst.h = static_cast<int>(dstRect.w);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, glm::vec4 dstRect, glm::vec4 srcRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(dstRect.x);
	dst.y = static_cast<int>(dstRect.y);
	dst.w = static_cast<int>(dstRect.z);
	dst.h = static_cast<int>(dstRect.w);
	SDL_Rect src{};
	src.x = static_cast<int>(srcRect.x);
	src.y = static_cast<int>(srcRect.y);
	src.w = static_cast<int>(srcRect.z);
	src.h = static_cast<int>(srcRect.w);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}
