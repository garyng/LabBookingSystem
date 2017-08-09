#include <memory>
#include "App.h"
#include "services/NavigationService.h"
#include "login/LoginView.h"
#include "login/LoginViewModel.h"
#include "user/UserView.h"
#include "user/UserViewModel.h"
#include "admin/AdminView.h"

using namespace std;

template <class TView, class TViewModel,
          enable_if_t<is_base_of<IView, TView>::value && is_base_of<ViewModelBase, TViewModel>::value>* = nullptr>
void MakeViewsAndViewModels(const shared_ptr<NavigationService>& navigation)
{
	shared_ptr<TViewModel> viewModel = make_shared<TViewModel>(navigation);
	shared_ptr<TView> view = make_shared<TView>(viewModel);
	navigation->Register<TViewModel, TView>(viewModel, view);
}

int main(int argc, char* argv[])
{
	shared_ptr<NavigationService> navigation = make_shared<NavigationService>();

	/*shared_ptr<LoginViewModel> loginViewModel = make_shared<LoginViewModel>(navigation);
	shared_ptr<LoginView> loginView = make_shared<LoginView>(loginViewModel);

	shared_ptr<UserViewModel> userViewModel = make_shared<UserViewModel>(navigation);
	shared_ptr<UserView> userView = make_shared<UserView>(userViewModel);


	navigation->Register<LoginViewModel, LoginView>(loginViewModel, loginView);
	navigation->Register<UserViewModel, UserView>(userViewModel, userView);*/

	MakeViewsAndViewModels<LoginView, LoginViewModel>(navigation);
	MakeViewsAndViewModels<UserView, UserViewModel>(navigation);
	MakeViewsAndViewModels<AdminView, AdminViewModel>(navigation);

	navigation->NavigateTo<LoginViewModel>();

	shared_ptr<App> app = make_shared<App>(navigation);

	app->Start();
	return 0;
}
