#include "UserViewModel.h"
#include "../login/LoginViewModel.h"
#include "../request/RequestViewModel.h"

UserViewModel::UserViewModel(const std::shared_ptr<NavigationService>& navigation): ViewModelBase(navigation)
{
}


void UserViewModel::LogoutCommand() const
{
	_navigation->GoTo<LoginViewModel>();
}

void UserViewModel::GoToRequestViewCommand() const
{
	_navigation->GoTo<RequestViewModel>([&](std::shared_ptr<RequestViewModel> vm)
	                                    {
		                                    vm->UserName(_userName);
											vm->LoadUserRequestCommand();
	                                    }, true);
}
