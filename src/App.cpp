#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <string>
#include <IconsMaterialDesign.h>
#include "App.h"

using namespace std;

App::App(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<GenericViewsRenderer>& renderer)
	: _navigation(navigation), _renderer(renderer)
{
}

void App::Start()
{
	Initialize();
	Loop();
}

void App::Initialize()
{
	glfwSetErrorCallback([](int error, const char* description)
		{
			cout << "Error " << error << ": " << description << endl;
		});

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(1280, 720, WINDOW_TITLE.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);
	gl3wInit();

	ImGui_ImplGlfwGL3_Init(_window, true);

	LoadFonts();
	SetStyle();
}

void App::LoadFonts() const
{
	// Font index is best retrieved via class AppFontIndex
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 17.0f);

	ImFontConfig config;
	config.GlyphOffset.y += 3;
	config.MergeMode = true;
	const ImWchar iconRange[] = {ICON_MIN_MD, ICON_MAX_MD, 0};
	io.Fonts->AddFontFromFileTTF("Fonts/MaterialIcons-Regular.ttf", 17.0f, &config, iconRange);
	io.Fonts->AddFontFromFileTTF("fonts/Roboto-Light.ttf", 25.0f);
	io.Fonts->AddFontFromFileTTF("fonts/Roboto-Bold.ttf", 17.0f);
	io.Fonts->Build();
}

void App::SetStyle() const
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(20, 20);
	style.WindowRounding = 5.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
}

void App::Loop() const
{
	ImVec4 clearColor = ImColor(114, 144, 154);

	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		Render();

		int displayWidth, displayHeight;
		glfwGetFramebufferSize(_window, &displayWidth, &displayHeight);
		glViewport(0, 0, displayWidth, displayHeight);
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(_window);
	}

	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();
}

void App::Render() const
{
	//_navigation->RenderCurrent();
	_navigation->RenderAll();
	_renderer->RenderAll();
	ImGui::ShowStyleEditor();
}
