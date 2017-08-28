#include "AdminViewModel.h"
#include "../login/LoginViewModel.h"
#include "../request/RequestViewModel.h"

AdminViewModel::AdminViewModel(const std::shared_ptr<NavigationService>& navigation): ViewModelBase(navigation)
{
}

void AdminViewModel::LogoutCommand() const
{
	_navigation->GoTo<LoginViewModel>();
}


void AdminViewModel::GoToRequestViewCommand() const
{
	_navigation->GoTo<RequestViewModel>([&](std::shared_ptr<RequestViewModel> vm)
	                                    {
		                                    vm->UserName(_userName);
		                                    vm->LoadUserRequestCommand();
	                                    }, true);
}
