#include "stdafx.h"
#include "AdminViewModel.h"
#include "login/LoginViewModel.h"
#include "request/RequestViewModel.h"
#include "review/ReviewViewModel.h"


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

void AdminViewModel::GoToReviewViewCommand() const
{
	_navigation->GoTo<ReviewViewModel>([&](std::shared_ptr<ReviewViewModel> vm)
                                   {
	                                   vm->AdminUserName(_userName);
	                                   vm->LoadAllRequestCommand();
                                   }, true);
}
