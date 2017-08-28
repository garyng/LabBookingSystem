#pragma once
#include <map>
#include <typeindex>
#include <memory>
#include <functional>
#include "../IView.h"

class ViewModelBase;

class NavigationService
{
private:

	std::shared_ptr<IView> _currentView;
	std::map<std::type_index, std::pair<std::shared_ptr<ViewModelBase>, std::shared_ptr<IView>>> _viewModelViewPair;

public:
	template <class TViewModel, class TView,
	          std::enable_if_t<
		          std::is_base_of<ViewModelBase, TViewModel>::value &&
		          std::is_base_of<IView, TView>::value>* = nullptr>
	void Register(const std::shared_ptr<ViewModelBase>& viewModel, const std::shared_ptr<IView>& view)
	{
		std::type_index key = typeid(TViewModel);
		_viewModelViewPair.insert({key, {viewModel, view}});
	}


	template <class TViewModel,
	          std::enable_if_t<
		          std::is_base_of<ViewModelBase, TViewModel>::value>* = nullptr>
	void NavigateTo()
	{
		NavigateTo<TViewModel>([](std::shared_ptr<ViewModelBase> vm)
			{
			});
	}

	template <class TViewModel, class CallBack,
	          std::enable_if_t<
		          std::is_base_of<ViewModelBase, TViewModel>::value>* = nullptr>
	void NavigateTo(CallBack&& callBack)
	{
		std::type_index key = typeid(TViewModel);
		std::map<std::type_index, std::pair<std::shared_ptr<ViewModelBase>, std::shared_ptr<IView>>>::iterator result = _viewModelViewPair.find(key);
		std::shared_ptr<ViewModelBase> viewModel = result->second.first;
		std::shared_ptr<TViewModel> castedViewModel = std::static_pointer_cast<TViewModel>(viewModel);
		callBack(castedViewModel);
		if (result != _viewModelViewPair.end())
		{
			_currentView = result->second.second;
		}
	}

	void RenderCurrent() const
	{
		_currentView->Render();
	}

	void RenderAll() const
	{
		for (auto& p :_viewModelViewPair)
		{
			p.second.second->Render();
		}
	}
};
