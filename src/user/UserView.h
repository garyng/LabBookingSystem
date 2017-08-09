#pragma once
#include <memory>
#include "UserViewModel.h"
#include "../ViewBase.h"

class UserView
	: public ViewBase<UserViewModel>
{
public:
	explicit UserView(const std::shared_ptr<UserViewModel>& viewModel);
	void Render() override;
};
