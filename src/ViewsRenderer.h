#pragma once
#include "IView.h"
#include <memory>
#include "AppFontIndex.h"

class ViewVisibilityPair
{
private:
	std::shared_ptr<IView> _view;
	bool _isVisible;

public:
	std::shared_ptr<IView> View() const { return _view; }

	bool IsVisible() const { return _isVisible; }
	void IsVisible(bool value) { _isVisible = value; }


	ViewVisibilityPair(const std::shared_ptr<IView>& view, bool visibility)
		: _view(view),
		  _isVisible(visibility)
	{
	}
};

class ViewsRenderer
{
	// handles all rendering logic including the menu bar
private:
	std::map<std::type_index, ViewVisibilityPair> _views;
	std::shared_ptr<NavigationService> _navigation;

public:
	explicit ViewsRenderer(const std::shared_ptr<NavigationService>& navigationService)
		: _navigation(navigationService)
	{
	}

	template <class TView,
	          std::enable_if_t<
		          std::is_base_of<IView, TView>::value>* = nullptr>
	void RegisterToDebugMenu(std::shared_ptr<IView> view)
	{
		std::type_index key = typeid(TView);
		_views.insert({key, {view, false}});
	}

	void Render()
	{
		static bool showAllViewsInNavigation;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Debug"))
			{
				ImGui::Text("Navigation Service");
				ImGui::Checkbox("Show all registered views", &showAllViewsInNavigation);

				ImGui::Separator();

				ImGui::Text("Tests");

				RenderShowAllTestViewsButton();
				RenderMenuForEachView();

				ImGui::EndMenu();
			}

			RenderAboutMenu();
		}
		ImGui::EndMainMenuBar();

		RenderVisibleViews();

		if (showAllViewsInNavigation)
		{
			_navigation->RenderAll();
		}
		else
		{
			_navigation->RenderCurrent();
		}
	}

	void RenderShowAllTestViewsButton()
	{
		if (ImGui::FullWidthButton("Show all test views"))
		{
			for (auto& view : _views)
			{
				view.second.IsVisible(true);
			}
		}
	}

	void RenderMenuForEachView()
	{
		for (auto& view : _views)
		{
			ViewVisibilityPair& vv = view.second;
			bool enabled = vv.IsVisible();
			ImGui::Checkbox(vv.View()->Name().c_str(), &enabled);
			vv.IsVisible(enabled);
		}
	}

	void RenderVisibleViews()
	{
		for (auto& view : _views)
		{
			if (view.second.IsVisible())
			{
				view.second.View()->Render();
			}
		}
	}

	void RenderAboutMenu()
	{
		if (ImGui::BeginMenu("About"))
		{
			ImGui::MenuItem("TCP1121", nullptr, false, false);
			ImGui::MenuItem("@garyng", "https://github.com/garyng/", false, false);
			ImGui::EndMenu();
		}
	}
};
