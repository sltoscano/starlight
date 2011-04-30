
#include "common.h"
#include "glmain.h"
#include "server.h"


int main(int argc, char* argv[])
{
    return (argc > 1) ? glmain(argc, argv) :
        server(argc, argv);
}
