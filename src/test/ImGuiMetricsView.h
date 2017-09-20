#pragma once

class ImGuiMetricsView
	: public IView
{
public:
	void Render() override
	{
		ImGui::ShowMetricsWindow();
	}
	std::string Name() override { return "ImGuiMetricsView"; }
};
