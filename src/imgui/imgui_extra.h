#pragma once
#include <initializer_list>
#include <imgui.h>
#include "../AppFontIndex.h"

namespace ImGui
{
	// template need to be in header file
	// won't work if placed under imconfig.h

	template <class OnOkClicked>
	void OkCancelPopupModal(std::string name,
	                        std::string icon,
	                        std::initializer_list<std::string> texts,
	                        OnOkClicked&& onOkClicked)
	{
		OkCancelPopupModal(name, icon, texts, onOkClicked, []()
		                   {
		                   });
	}


	template <class OnOkClicked, class OnCancelClicked>
	void OkCancelPopupModal(std::string name,
	                        std::string icon,
	                        std::initializer_list<std::string> texts,
	                        OnOkClicked&& onOkClicked,
	                        OnCancelClicked&& onCancelClicked)
	{
		SetNextWindowPosCenter();
		if (BeginPopupModal(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			Text("");

			PushFont(AppFontIndex::MaterialIcon_Title);
			Text(icon.c_str());
			PopFont();
			SameLine();

			BeginGroup();
			{
				for (std::string text : texts)
				{
					Text(text.c_str());
				}
			}
			EndGroup();
			Text("");

			if (Button("OK", ImVec2(60, 0)))
			{
				onOkClicked();
				CloseCurrentPopup();
			}
			SameLine();
			if (Button("Cancel", ImVec2(60, 0)))
			{
				onCancelClicked();
				CloseCurrentPopup();
			}

			EndPopup();
		}
	}
}
