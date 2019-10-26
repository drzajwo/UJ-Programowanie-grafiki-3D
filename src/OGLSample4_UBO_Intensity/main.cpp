#include "libs.h"
#include "sampleapp.h"

int main(void)
{
    try {
        SampleApp app;
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception catched: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Exception catched..." << std::endl;
    }

#if WIN32
    std::cin.ignore();
#endif

    return 0;
}
