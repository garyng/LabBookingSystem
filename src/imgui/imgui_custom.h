#pragma once
#include <initializer_list>
#include <imgui.h>

namespace ImGui
{
	// template need to be in header file
	// won't work if placed under imconfig.h

	template <class OnOkClicked>
	void RenderOkCancelPopupModel(std::string name,
	                              std::initializer_list<std::string> texts,
	                              OnOkClicked&& onOkClicked)
	{
		RenderOkCancelPopupModel(name, texts, onOkClicked, []()
		                         {
		                         });
	}

	template <class OnOkClicked, class OnCancelClicked>
	void RenderOkCancelPopupModel(std::string name,
	                              std::initializer_list<std::string> texts,
	                              OnOkClicked&& onOkClicked,
	                              OnCancelClicked&& onCancelClicked)
	{
		if (BeginPopupModal(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			// each element is a seperate line

			for (std::string text : texts)
			{
				Text(text.c_str());
			}
			Spacing();
			Separator();
			if (Button("OK", ImVec2(120, 0)))
			{
				onOkClicked();
				CloseCurrentPopup();
			}
			SameLine();
			if (Button("Cancel", ImVec2(120, 0)))
			{
				onCancelClicked();
				CloseCurrentPopup();
			}
			EndPopup();
		}
	}
}
