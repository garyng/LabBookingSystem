#include <memory>
#include "App.h"
#include "services/NavigationService.h"
#include "login/LoginView.h"
#include "login/LoginViewModel.h"
#include "user/UserView.h"
#include "user/UserViewModel.h"

using namespace std;
int main(int argc, char* argv[])
{
	shared_ptr<NavigationService> navigation = make_shared<NavigationService>();

	shared_ptr<LoginViewModel> loginViewModel = make_shared<LoginViewModel>(navigation);
	shared_ptr<LoginView> loginView = make_shared<LoginView>(loginViewModel);

	shared_ptr<UserViewModel> userViewModel = make_shared<UserViewModel>(navigation);
	shared_ptr<UserView> userView = make_shared<UserView>(userViewModel);


	navigation->Register<LoginViewModel, LoginView>(loginViewModel, loginView);
	navigation->Register<UserViewModel, UserView>(userViewModel, userView);

	navigation->NavigateTo<LoginViewModel>();

	shared_ptr<App> app = make_shared<App>(navigation);

	app->Start();
	return 0;
}
