#pragma once
#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "services/NavigationService.h"
#include "GenericViewsRenderer.h"
class App
{
public:
	App(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<GenericViewsRenderer>& renderer);
	void Start();

private:
	const std::string WINDOW_TITLE = "Lab Booking System";
	GLFWwindow* _window;
	std::shared_ptr<NavigationService> _navigation;
	const std::shared_ptr<GenericViewsRenderer>& _renderer;

	void Initialize();

	void LoadFonts() const;
	void AddIconFont(ImGuiIO& io, float offsetY, float fontSize, bool merge = true) const;

	void SetStyle() const;

	void Loop() const;

	void Render() const;
};
