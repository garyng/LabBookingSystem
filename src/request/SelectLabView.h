#pragma once
#include "SelectLabViewModel.h"

class SelectLabView
	: public ViewBase<SelectLabViewModel>
{
public:

	explicit SelectLabView(const std::shared_ptr<SelectLabViewModel>& viewModel);

	void Render() override
	{
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
		ImGui::BeginDefaultCenteredResizableWindow("Select Lab");

		if (ImGui::Selectable(ICON_MD_ARROW_BACK " Back"))
		{
			_viewModel->GoBackCommand();
		}

		if (_viewModel->Labs().size() > 0)
		{
			RenderLabView();
		}
		else
		{
			RenderNoLabsView();
		}

		ImGui::End();
	}

	void RenderNoLabsView()
	{
		ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
		ImGui::CenteredTexts({"The are no available labs...", "Weird isn't it?"});
		ImGui::PopFont();
	}

	void RenderLabView()
	{
		ImGui::Columns(2);

		RenderLabList();

		ImGui::NextColumn();

		RenderLabDetails();

		ImGui::Columns(1);
		
		RenderRequestButton();
	}

	void RenderRequestButton()
	{
		ImGui::FullWidthButton(ICON_MD_ADD " Request");
		// todo: add request
	}

	void RenderLabList()
	{
		ImGui::BeginChildWithNBottomLineSpace("LabList", 1);
		{
			// range-based loop is more efficient than index-based
			// see http://fastcpp.blogspot.my/2011/03/fast-iteration-over-stl-vector-elements.html
			int i = 0;
			for (Lab& lab : _viewModel->Labs())
			{
				if (ImGui::Selectable(lab.Id().c_str(), i == _viewModel->SelectedIndex()))
				{
					_viewModel->SelectedIndex(i);
				}
				i++;
			}
		}
		ImGui::EndChild();
	}

	void RenderLabDetails()
	{
		Lab lab = _viewModel->Labs().at(_viewModel->SelectedIndex());
		ImGui::BeginChildWithNBottomLineSpace("LabDetails", 2);
		{
			ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
			ImGui::Text(lab.Id().c_str());
			ImGui::PopFont();
			ImGui::Separator();

			ImGui::PrintValueLabel("Description:", lab.Description());
		}
		ImGui::EndChild();
		RenderSelectTimeButton();
	}

	void RenderSelectTimeButton()
	{
		ImGui::FullWidthButton(ICON_MD_ACCESS_TIME " Select Time");
		// todo: select time
	}

	std::string Name() override { return "SelectLabView"; }
};
