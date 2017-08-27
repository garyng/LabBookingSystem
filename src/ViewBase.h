#pragma once
#include "ViewModelBase.h"

template <class TViewModel,
          std::enable_if_t<std::is_base_of<ViewModelBase, TViewModel>::value>* = nullptr>
class ViewBase
	: public IView
{
protected:
	std::shared_ptr<TViewModel> _viewModel;

	template <class Arr, class Val>
	void ClearBuffer(Arr* buffer, const Val& value)
	{
		std::fill_n(buffer, static_cast<int>(sizeof(buffer)) / (sizeof(*buffer)), value);
	}

public:
	explicit ViewBase(const std::shared_ptr<TViewModel>& viewModel)
		: _viewModel(viewModel)
	{
	}
};
