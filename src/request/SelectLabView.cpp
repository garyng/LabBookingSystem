#include "stdafx.h"
#include "SelectLabView.h"

using namespace std;

SelectLabView::SelectLabView(const std::shared_ptr<SelectLabViewModel>& viewModel): ViewBase<SelectLabViewModel>(viewModel)
{
}

void SelectLabView::Render()
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

void SelectLabView::RenderNoLabsView()
{
	ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
	ImGui::CenteredTexts({"The are no available labs...", "Weird isn't it?"});
	ImGui::PopFont();
}

void SelectLabView::RenderLabView()
{
	ImGui::Columns(2);

	RenderLabList();

	ImGui::NextColumn();

	RenderLabDetails();
}

void SelectLabView::RenderLabList()
{
	ImGui::BeginChild("LabList");
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

void SelectLabView::RenderLabDetails()
{
	Lab lab = _viewModel->Labs().at(_viewModel->SelectedIndex());
	ImGui::BeginChildWithNBottomLineSpace("LabDetails", 1);
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

void SelectLabView::RenderSelectTimeButton()
{
	if (ImGui::FullWidthButton(ICON_MD_ACCESS_TIME " Select Time"))
	{
		_viewModel->SelectTimeCommand();
	}
}
