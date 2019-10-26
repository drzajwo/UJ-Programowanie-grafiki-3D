#include "sampleapp.h"

SampleApp::SampleApp() : OGLAppFramework::OGLApplication(1366u, 768u, "OGLSample 0 - Empty Screen", 3u, 3u)
{
}

SampleApp::~SampleApp()
{
}

void SampleApp::reshapeCallback(std::uint16_t width, std::uint16_t height)
{
    std::cout << "Reshape..." << std::endl;
    std::cout << "New window size: " << width << " x " << height << std::endl;

    gl::glViewport(0, 0, width, height);
}

void SampleApp::keyCallback(int key, int scancode, int action, int mods)
{
    std::cout << "Key pressed" << std::endl;
}

void SampleApp::cursorPosCallback(double xpos, double ypos)
{
    //std::cout << "Cursor pos: " << xpos << ", " << ypos << std::endl;
}

void SampleApp::mouseButtonCallback(int button, int action, int mods)
{
    //std::cout << "Mouse button pressed" << std::endl;
}

bool SampleApp::init()
{
    std::cout << "Init..." << std::endl;

    // ustalamy domyślny kolor ekranu
    gl::glClearColor(0.f, 0.f, 0.f, 1.f);

	return true;
}

bool SampleApp::frame(float delta_time)
{
	return true;
}

void SampleApp::release()
{
    std::cout << "Release..." << std::endl;
}
