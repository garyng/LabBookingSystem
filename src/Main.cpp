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

	MakeViewsAndViewModels<LoginView, LoginViewModel>(navigation);
	MakeViewsAndViewModels<UserView, UserViewModel>(navigation);
	MakeViewsAndViewModels<AdminView, AdminViewModel>(navigation);
	MakeViewsAndViewModels<RequestView, RequestViewModel>(navigation);

	navigation->NavigateTo<LoginViewModel>();

	
	// todo: should generic renderer render a menu for selecting which view to render?
	shared_ptr<GenericViewsRenderer> genericRenderer = std::make_shared<GenericViewsRenderer>();
	shared_ptr<AppColorsTestView> appColorsTestView = std::make_shared<AppColorsTestView>();

	genericRenderer->Register(appColorsTestView);

	shared_ptr<App> app = make_shared<App>(navigation, genericRenderer);

	UserStorage us;
	us.Load();
	LabStorage ls;
	ls.Load();
	RequestStorage rs;
	rs.Load();

	app->Start();

	return 0;
}
