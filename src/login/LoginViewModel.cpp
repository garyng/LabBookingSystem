#include "LoginViewModel.h"
#include "../user/UserViewModel.h"

LoginViewModel::LoginViewModel(const std::shared_ptr<NavigationService>& navigation): ViewModelBase(navigation)
{
}

void LoginViewModel::LoginCommand(std::string userId, std::string userPassword) const
{
	if (userId == "1" && userPassword == "1")
	{
		_navigation->NavigateTo<UserViewModel>([](std::shared_ptr<UserViewModel> vm)
			{
				vm->_userId = "123123";
			});
	}
}
