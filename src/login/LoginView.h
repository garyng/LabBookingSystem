#pragma once
#include "../ViewBase.h"
#include <memory>

class LoginViewModel;

class LoginView 
	: public ViewBase
{
protected:
	std::shared_ptr<LoginViewModel> _viewModel;
public:
	explicit LoginView(const std::shared_ptr<LoginViewModel>& loginViewModel);
	void Render() override;
};
