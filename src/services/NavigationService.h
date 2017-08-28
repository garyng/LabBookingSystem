#pragma once
#include <map>
#include <typeindex>
#include <memory>
#include <functional>
#include <stack>
#include "../IView.h"

class ViewModelBase;

class ViewViewModelPair
{
private:
	std::shared_ptr<ViewModelBase> _viewModelBase;

	std::shared_ptr<IView> _view;

public:
	std::shared_ptr<ViewModelBase> ViewModelBase() const { return _viewModelBase; }

	std::shared_ptr<IView> View() const { return _view; }

	ViewViewModelPair(const std::shared_ptr<::ViewModelBase>& viewModelBase, const std::shared_ptr<IView>& view)
		: _viewModelBase(viewModelBase),
		  _view(view)
	{
	}
};

class NavigationService
{
private:

	std::shared_ptr<IView> _currentView;
	std::map<std::type_index, ViewViewModelPair> _viewModelViewPair;
	std::stack<std::pair<std::shared_ptr<ViewModelBase>, std::shared_ptr<IView>>> _navigationHistory;
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

		std::map<std::type_index, ViewViewModelPair>::iterator result = _viewModelViewPair.find(key);
		std::shared_ptr<ViewModelBase> viewModel = result->second.ViewModelBase();

		std::shared_ptr<TViewModel> castedViewModel = std::static_pointer_cast<TViewModel>(viewModel);
		callBack(castedViewModel);
		if (result != _viewModelViewPair.end())
		{
			_currentView = result->second.View();
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
			p.second.View()->Render();
		}
	}
};
