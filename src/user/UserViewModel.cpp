#include "UserViewModel.h"
#include "../login/LoginViewModel.h"

UserViewModel::UserViewModel(const std::shared_ptr<NavigationService>& navigation): ViewModelBase(navigation)
{
}


void UserViewModel::LogoutCommand() const
{
	_navigation->NavigateTo<LoginViewModel>();
}
