#pragma once
#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include "services/NavigationService.h"

class App
{
public:
	App(const std::shared_ptr<NavigationService>& navigation);
	void Start();

private:
	const std::string WINDOW_TITLE = "Lab Booking System";
	GLFWwindow* _window;
	std::shared_ptr<NavigationService> _navigation;

	void Initialize();

	void LoadFonts() const;

	void SetStyle() const;

	void Loop() const;

	void Render() const;
};
