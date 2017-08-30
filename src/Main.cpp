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
#include "ViewsRenderer.h"
#include "test/AppColorsTestView.h"
#include "test/AppFontsTestView.h"
#include "tests/ImGuiStyleEditorView.h"
#include "tests/DataStorageTestsView.h"

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

	shared_ptr<RequestViewModel> requestViewModel = make_shared<RequestViewModel>(navigation, userStorage, requestStorage);
	shared_ptr<RequestView> requestView = make_shared<RequestView>(requestViewModel);
	navigation->Register<RequestViewModel, RequestView>(requestViewModel, requestView);

	navigation->GoTo<LoginViewModel>();


	shared_ptr<ViewsRenderer> renderer = make_shared<ViewsRenderer>(navigation);
	shared_ptr<AppColorsTestView> appColorsTestView = make_shared<AppColorsTestView>();
	shared_ptr<AppFontsTestView> appFontsTestView = make_shared<AppFontsTestView>();
	shared_ptr<ImGuiStyleEditorView> imGuiStyleEditorView = make_shared<ImGuiStyleEditorView>();
	shared_ptr<DataStorageTestsView> dataStorageTestsView = make_shared<DataStorageTestsView>(vector<shared_ptr<IStorage>>{userStorage, requestStorage, labStorage});

	renderer->RegisterToDebugMenu<AppColorsTestView>(appColorsTestView);
	renderer->RegisterToDebugMenu<AppFontsTestView>(appFontsTestView);
	renderer->RegisterToDebugMenu<ImGuiStyleEditorView>(imGuiStyleEditorView);
	renderer->RegisterToDebugMenu<DataStorageTestsView>(dataStorageTestsView);

	shared_ptr<App> app = make_shared<App>(renderer);

	app->Start();


	return 0;
}
