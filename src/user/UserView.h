#pragma once
#include "UserViewModel.h"

class UserView
	: public ViewBase<UserViewModel>
{
public:
	explicit UserView(const std::shared_ptr<UserViewModel>& viewModel);
	void Render() override;
	std::string Name() override { return "UserView"; }
};
