#pragma once
#include "IView.h"
#include <vector>
#include <memory>

class GenericViewsRenderer
{
	// holds only views/view that doesn't need navigation logic
	// todo: add flag to render only a particular view
private:
	std::vector<std::shared_ptr<IView>> _views;
public:
	void Register(const std::shared_ptr<IView>& view)
	{
		_views.push_back(view);
	}
	void RenderAll()
	{
		for (auto view : _views)
		{
			view->Render();
		}
	}
};
