
#include "server.h"
#include "common.h"
#include "simulation.h"
#include <unistd.h>


namespace
{
    float settingsHz = 60.0;
    int32 framePeriod = 5;
    Settings settings;
}

int server(int argc, char *argv[])
{
    settings.hz = settingsHz;
    Simulation simulation(&settings, NULL);

    while (true)
    {
        simulation.Step();

        sleep(framePeriod);
    }

    return 0;
}
