#include "stdafx.h"
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
#include "test/ImGuiStyleEditorView.h"
#include "test/DataStorageTestsView.h"
#include "test/ImGuiDateChooserTestView.h"
#include "test/TimeRangeCalculationTestsView.h"
#include "request/SelectLabViewModel.h"
#include "request/SelectLabView.h"
#include "test/ImGuiMetricsView.h"
#include "test/DateLibraryTestsView.h"
#include "request/SelectTimeView.h"
#include "test/PocoDateTestView.h"

using namespace std;

template <class TView, class TViewModel, class... TViewModelArgs,
          enable_if_t<
	          is_base_of<ViewModelBase, TViewModel>::value &&
	          is_base_of<IView, TView>::value
          >* = nullptr>
void RegisterMVVM(const shared_ptr<NavigationService>& navigation, TViewModelArgs&&... viewModelArgs)
{
	shared_ptr<TViewModel> viewModel = make_shared<TViewModel>(navigation, forward<TViewModelArgs>(viewModelArgs)...);
	shared_ptr<TView> view = make_shared<TView>(viewModel);
	navigation->Register<TViewModel, TView>(viewModel, view);
}

template <class TView, class... TViewArgs,
          enable_if_t<is_base_of<IView, TView>::value>* = nullptr>
void RegisterDebug(const shared_ptr<ViewsRenderer>& renderer, TViewArgs&&... viewArgs)
{
	shared_ptr<TView> view = make_shared<TView>(forward<TViewArgs>(viewArgs)...);
	renderer->RegisterToDebugMenu<TView>(view);
}

void AutomateGui(const shared_ptr<NavigationService>& navigation)
{
	navigation->GoTo<LoginViewModel>([](shared_ptr<LoginViewModel> vm)
	{
		vm->LoginCommand("1", "1");
	});
	navigation->GoTo<AdminViewModel>([](shared_ptr<AdminViewModel> vm)
                                 {
	                                 vm->UserName("1");
                                 }, true);
	navigation->GoTo<RequestViewModel>([](shared_ptr<RequestViewModel> vm)
                                   {
	                                   vm->UserName("1");
	                                   vm->LoadUserRequestCommand();
                                   }, true);
	navigation->GoTo<SelectLabViewModel>([](shared_ptr<SelectLabViewModel> vm)
                                     {
	                                     vm->UserName("1");
	                                     vm->LoadAllLabsCommand();
                                     }, true);
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

	RegisterMVVM<LoginView, LoginViewModel>(navigation, userStorage);
	RegisterMVVM<UserView, UserViewModel>(navigation);
	RegisterMVVM<AdminView, AdminViewModel>(navigation);
	RegisterMVVM<RequestView, RequestViewModel>(navigation, userStorage, requestStorage);
	RegisterMVVM<SelectLabView, SelectLabViewModel>(navigation, labStorage);
	RegisterMVVM<SelectTimeView, SelectTimeViewModel>(navigation, requestStorage, userStorage);

	navigation->GoTo<LoginViewModel>();

	shared_ptr<ViewsRenderer> renderer = make_shared<ViewsRenderer>(navigation);

	RegisterDebug<AppColorsTestView>(renderer);
	RegisterDebug<AppFontsTestView>(renderer);
	RegisterDebug<ImGuiStyleEditorView>(renderer);
	RegisterDebug<DataStorageTestsView>(renderer, vector<shared_ptr<IStorage>>{userStorage, requestStorage, labStorage});
	RegisterDebug<ImGuiDateChooserTestView>(renderer);
	RegisterDebug<ImGuiMetricsView>(renderer);
	RegisterDebug<TimeRangeCalculationTestsView>(renderer);
	RegisterDebug<DateLibraryTestsView>(renderer);
	RegisterDebug<PocoDateTestView>(renderer);

	shared_ptr<App> app = make_shared<App>(renderer);

	// automate gui
	AutomateGui(navigation);

	app->Start();
	return 0;
}
