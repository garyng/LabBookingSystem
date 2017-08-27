#include <memory>
#include "App.h"
#include "services/NavigationService.h"
#include "login/LoginView.h"
#include "login/LoginViewModel.h"
#include "user/UserView.h"
#include "user/UserViewModel.h"
#include "admin/AdminView.h"
#include "request/RequestViewModel.h"
#include "request/RequestView.h"
#include "storage/JsonStorage.h"
#include "storage/UserStorage.h"
#include "storage/LabStorage.h"
#include "storage/RequestStorage.h"
#include "GenericViewsRenderer.h"
#include "test/AppColorsTestView.h"
#include <coveo/linq/linq.h>

using namespace std;
using namespace coveo::linq;

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

	//MakeViewsAndViewModels<LoginView, LoginViewModel>(navigation);
	shared_ptr<UserStorage> userStorage = make_shared<UserStorage>();
	userStorage->Load();
	shared_ptr<LabStorage> labStorage = make_shared<LabStorage>();
	labStorage->Load();
	shared_ptr<RequestStorage> requestStorage = make_shared<RequestStorage>();
	requestStorage->Load();


	shared_ptr<LoginViewModel> loginViewModel = make_shared<LoginViewModel>(navigation, userStorage);
	shared_ptr<LoginView> loginView = make_shared<LoginView>(loginViewModel);
	navigation->Register<LoginViewModel, LoginView>(loginViewModel, loginView);


	MakeViewsAndViewModels<UserView, UserViewModel>(navigation);
	MakeViewsAndViewModels<AdminView, AdminViewModel>(navigation);
	MakeViewsAndViewModels<RequestView, RequestViewModel>(navigation);

	navigation->NavigateTo<LoginViewModel>();


	// todo: should generic renderer render a menu for selecting which view to render?
	shared_ptr<GenericViewsRenderer> genericRenderer = make_shared<GenericViewsRenderer>();
	shared_ptr<AppColorsTestView> appColorsTestView = make_shared<AppColorsTestView>();

	genericRenderer->Register(appColorsTestView);

	shared_ptr<App> app = make_shared<App>(navigation, genericRenderer);

	app->Start();


	return 0;
}
