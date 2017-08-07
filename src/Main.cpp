#include <memory>
#include "App.h"

using namespace std;

int main(int argc, char* argv[])
{
	// pass navigation service by injection
	unique_ptr<App> app = make_unique<App>();
	app->Start();
	return 0;
}
