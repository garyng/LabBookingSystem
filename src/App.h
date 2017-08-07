#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

class App
{
public:
	void Start();

private:
	const std::string WINDOW_TITLE = "Lab Booking System";
	GLFWwindow* _window;

	void Initialize();

	void LoadFonts() const;

	void SetStyle() const;

	void Loop() const;

	void Render() const;
};
