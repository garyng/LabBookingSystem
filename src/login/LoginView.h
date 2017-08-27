#pragma once
#include <memory>
#include "LoginViewModel.h"
#include "../ViewBase.h"


class LoginView
	: public ViewBase<LoginViewModel>
{
private:
	void RenderPasswordIncorrectDialog();
public:
	explicit LoginView(const std::shared_ptr<LoginViewModel>& viewModel);
	void Render() override;
};
