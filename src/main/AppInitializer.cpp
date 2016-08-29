#include <iostream>
#include "LincedInServerConfig.h"

using namespace std;

/**
* Launchs the application server.<BR>
* Prints the app-server version.
*/
int main(int argc, char **argv)
{
    cout << LincedInServer_VERSION_MAJOR << "." << LincedInServer_VERSION_MINOR << endl;
    return 0;
}
