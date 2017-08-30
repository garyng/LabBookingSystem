#pragma once
#include "ViewModelBase.h"

template <class TViewModel,
          std::enable_if_t<std::is_base_of<ViewModelBase, TViewModel>::value>* = nullptr>
class ViewBase
	: public IView
{
protected:
	std::shared_ptr<TViewModel> _viewModel;

	void ClearCharBuffer(char* buffer, int bufferSize, char value) const
	{
		std::fill_n(buffer, bufferSize, value);
	}
	void FillCharBuffer(char* buffer, int bufferSisze, std::string source) const
	{
		snprintf(buffer, bufferSisze, ("%." + std::to_string(bufferSisze) + "s").c_str(), source.c_str());
	}

public:
	explicit ViewBase(const std::shared_ptr<TViewModel>& viewModel)
		: _viewModel(viewModel)
	{
	}
};
