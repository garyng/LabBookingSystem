#include "LoginViewModel.h"
#include "../user/UserViewModel.h"
#include "../storage/UserStorage.h"
#include <memory>
#include <picosha2.h>
#include <optional>
#include <coveo/linq.h>
#include "../admin/AdminViewModel.h"
#include "../command/UserLoginCommand.h"
#include "../query/GetUserByUserNameQuery.h"

using namespace std;

LoginViewModel::LoginViewModel(const shared_ptr<NavigationService>& navigation, const shared_ptr<UserStorage>& userStorage)
	: ViewModelBase(navigation), _userId(""),
	  _userPassword(""), _userStorage(userStorage)
{
}

bool LoginViewModel::LoginCommand(string userName, string userPassword) const
{
	string hash;
	picosha2::hash256_hex_string(userPassword, hash);

	Log->Debug("Logging in [Username: " + userName + " SHA2: " + hash + "]");

	UserLoginCommand command(_userStorage);
	bool loginResult = command.Execute(userName, hash);

	Log->Debug("Login result: " + to_string(loginResult));

	if (loginResult)
	{
		GetUserByUserNameQuery query(_userStorage);
		if (auto user = query.Execute(userName))
		{
			if (user->IsAdmin())
			{
				_navigation->GoTo<AdminViewModel>([&](shared_ptr<AdminViewModel> vm)
					{
						vm->UserName(user->Name());
					});
				return true;
			}
			else
			{
				_navigation->GoTo<UserViewModel>([&](shared_ptr<UserViewModel> vm)
					{
						vm->UserName(user->Name());
					});
				return true;
			}
		}
		else
		{
			// logged in user but not found?
			return false;
		}
	}
	else
	{
		return false;
	}
}
