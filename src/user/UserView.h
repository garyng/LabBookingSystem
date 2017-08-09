#pragma once
#include "../ViewBase.h"
#include <memory>
#include "UserViewModel.h"

class UserView
	: public ViewBase
{
protected:
	std::shared_ptr<UserViewModel> _viewModel;
public:
	explicit UserView(const std::shared_ptr<UserViewModel>& viewModel);
	void Render() override;
};
