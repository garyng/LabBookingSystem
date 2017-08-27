#include "AdminViewModel.h"
#include "../login/LoginViewModel.h"

AdminViewModel::AdminViewModel(const std::shared_ptr<NavigationService>& navigation): ViewModelBase(navigation)
{
}

void AdminViewModel::LogoutCommand() const
{
	_navigation->NavigateTo<LoginViewModel>();
}
