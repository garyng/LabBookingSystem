#pragma once
#include <map>
#include <typeindex>
#include <memory>
#include "../views/ViewBase.h"

class NavigationService
{
private:
	std::map<std::type_index, std::shared_ptr<ViewBase>> _views;
	std::shared_ptr<ViewBase> _currentView;
public:
	template <class TView>
	typename std::enable_if<std::is_base_of<ViewBase, TView>::value, void>::type
	Register(const std::shared_ptr<ViewBase>& view)
	{
		std::type_index key = typeid(TView);
		_views.insert({ key, view });
	}

	template <class TView>
	typename std::enable_if<std::is_base_of<ViewBase, TView>::value, void>::type
	NavigateTo()
	{
		std::type_index key = typeid(TView);
		map<std::type_index, std::shared_ptr<ViewBase>>::iterator result = _views.find(key);
		if (result != _views.end())
		{
			_currentView = result->second;
		}
	}

	void RenderCurrent() const
	{
		_currentView->Render();
	}
};

