#pragma once
#include "LoginViewModel.h"
#include "ViewBase.h"


class LoginView
	: public ViewBase<LoginViewModel>
{
public:
	explicit LoginView(const std::shared_ptr<LoginViewModel>& viewModel);
	void Render() override;
	std::string Name() override { return "LoginView"; }
};
