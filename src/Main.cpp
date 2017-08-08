#include <memory>
#include "App.h"
#include "services/NavigationService.h"
#include "views/LoginView.h"

using namespace std;

int main(int argc, char* argv[])
{	
	shared_ptr<NavigationService> navigation = make_shared<NavigationService>();
	shared_ptr<LoginView> loginView = make_shared<LoginView>();

	navigation->Register<LoginView>(loginView);
	navigation->NavigateTo<LoginView>();

	shared_ptr<App> app = make_shared<App>(navigation);

	app->Start();
	return 0;
}
