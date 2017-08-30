#pragma once
#include "ViewModelBase.h"

template <class TViewModel,
          std::enable_if_t<std::is_base_of<ViewModelBase, TViewModel>::value>* = nullptr>
class ViewBase
	: public IView
{
protected:
	std::shared_ptr<TViewModel> _viewModel;

	void ClearCharBuffer(char* buffer, int bufferSize, char value)
	{
		std::fill_n(buffer, bufferSize, value);
	}


public:
	explicit ViewBase(const std::shared_ptr<TViewModel>& viewModel)
		: _viewModel(viewModel)
	{
	}
};
