#pragma once
#include <GLFW/glfw3.h>
#include "ViewsRenderer.h"

class App
{
private:
	const std::string WINDOW_TITLE = "Lab Booking System";
	GLFWwindow* _window;
	std::shared_ptr<ViewsRenderer> _renderer;

	void Initialize();

	void LoadFonts() const;
	void AddIconFont(ImGuiIO& io, float offsetY, float fontSize, bool merge = true) const;

	void SetStyle() const;

	void Loop() const;

	void Render() const;
public:
	explicit App(const std::shared_ptr<ViewsRenderer>& viewsRenderer);
	void Start();
};
