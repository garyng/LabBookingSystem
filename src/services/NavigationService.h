#pragma once
#include <map>
#include <typeindex>
#include <memory>
#include <functional>
#include <stack>
#include "../IView.h"
#include "../logger/Logger.h"

class ViewModelBase;

class ViewViewModelPair
{
private:
	std::shared_ptr<ViewModelBase> _viewModel;
	std::shared_ptr<IView> _view;

public:
	std::shared_ptr<ViewModelBase> ViewModel() const { return _viewModel; }
	std::shared_ptr<IView> View() const { return _view; }
	bool IsEmpty() const { return _view == nullptr || _viewModel == nullptr; }

	ViewViewModelPair(const std::shared_ptr<::ViewModelBase>& viewModel, const std::shared_ptr<IView>& view)
		: _viewModel(viewModel),
		  _view(view)
	{
	}

	std::string ToString() const
	{
		return "[ViewModel: " + std::string(typeid(*_viewModel).name()) + " View: " + std::string(typeid(*_view).name()) + "]";
	}

};

class NavigationService
{
private:
	std::shared_ptr<ILogger> Log = Logger::Instance();

	ViewViewModelPair _currentViewViewModelPair;

	std::map<std::type_index, ViewViewModelPair> _viewModelViewPair;
	std::stack<ViewViewModelPair> _history;
public:
	NavigationService() : _currentViewViewModelPair(nullptr, nullptr)
	{
	}

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
	void GoTo()
	{
		GoTo<TViewModel>([](std::shared_ptr<ViewModelBase> vm)
			{
			});
	}

	template <class TViewModel, class CallBack,
	          std::enable_if_t<
		          std::is_base_of<ViewModelBase, TViewModel>::value>* = nullptr>
	void GoTo(CallBack&& callBack, bool pushCurrentToHistory = false)
	{
		std::type_index key = typeid(TViewModel);

		std::map<std::type_index, ViewViewModelPair>::iterator result = _viewModelViewPair.find(key);

		std::shared_ptr<ViewModelBase> viewModel = result->second.ViewModel();
		std::shared_ptr<IView> view = result->second.View();

		std::shared_ptr<TViewModel> castedViewModel = std::static_pointer_cast<TViewModel>(viewModel);
		callBack(castedViewModel);

		if (pushCurrentToHistory && !_currentViewViewModelPair.IsEmpty())
		{
			_history.emplace(_currentViewViewModelPair.ViewModel(), _currentViewViewModelPair.View());
			Log->Debug("Pushed " + _currentViewViewModelPair.ToString() + " to history stack");
		}

		if (result != _viewModelViewPair.end())
		{
			_currentViewViewModelPair = result->second;
		}

		Log->Debug("Navigated to " + _currentViewViewModelPair.ToString());
	}


	void GoBack()
	{
		if (!_history.empty())
		{
			_currentViewViewModelPair = _history.top();
			_history.pop();
			Log->Debug("Navigated backwards to " + _currentViewViewModelPair.ToString());
		}
		else
		{
			Log->Warn("History stack is empty! Unable to go backwards!");
		}
	}

	void RenderCurrent() const
	{
		_currentViewViewModelPair.View()->Render();
	}

	void RenderAll() const
	{
		for (auto& p :_viewModelViewPair)
		{
			p.second.View()->Render();
		}
	}
};
