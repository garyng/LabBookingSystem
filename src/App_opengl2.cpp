﻿#include "stdafx.h"
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include "App.h"

using namespace std;

App::App(const std::shared_ptr<ViewsRenderer>& viewsRenderer) : _renderer(viewsRenderer)
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
	
	_window = glfwCreateWindow(1280, 720, WINDOW_TITLE.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);

	ImGui_ImplGlfw_Init(_window, true);

	LoadFonts();
	SetStyle();
}

void App::LoadFonts() const
{
	// Font index is best retrieved via class AppFontIndex
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();

	io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 17.0f);
	AddIconFont(io, 3, 17.0f);

	io.Fonts->AddFontFromFileTTF("fonts/Roboto-Light.ttf", 30.0f);
	AddIconFont(io, 6, 27.0f);

	io.Fonts->AddFontFromFileTTF("fonts/Roboto-Bold.ttf", 17.0f);
	AddIconFont(io, 3, 17.0f);

	io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 27.0f);
	AddIconFont(io, 3, 27.0f);

	AddIconFont(io, 0, 50.0f, false);

	io.Fonts->AddFontFromFileTTF("fonts/Roboto-Light.ttf", 27.0f);
	AddIconFont(io, 6, 27.0f);

	io.Fonts->Build();
}

void App::AddIconFont(ImGuiIO& io, float offsetY, float fontSize, bool merge) const
{
	ImFontConfig config;
	config.GlyphOffset.y += offsetY;
	config.MergeMode = merge;
	static const ImWchar iconRange[] = { ICON_MIN_MD, ICON_MAX_MD, 0 };
	io.Fonts->AddFontFromFileTTF("Fonts/MaterialIcons-Regular.ttf", fontSize, &config, iconRange);
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
		ImGui_ImplGlfw_NewFrame();

		Render();

		int displayWidth, displayHeight;
		glfwGetFramebufferSize(_window, &displayWidth, &displayHeight);
		glViewport(0, 0, displayWidth, displayHeight);
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(_window);
	}

	ImGui_ImplGlfw_Shutdown();
	glfwTerminate();
}

void App::Render() const
{
	_renderer->Render();
}
