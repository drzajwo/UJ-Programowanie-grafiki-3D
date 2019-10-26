#include "sampleapp.h"

SampleApp::SampleApp() : OGLAppFramework::OGLApplication(1366u, 768u, "OGLSample 2 - IB VBO", 3u, 3u), simple_program(0u), vbo_handle(0u), index_buffer_handle(0u), vao_handle(0u)
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
    //std::cout << "Key pressed" << std::endl;
}

void SampleApp::cursorPosCallback(double xpos, double ypos)
{
    //std::cout << "Cursor pos: " << xpos << ", " << ypos << std::endl;
}

void SampleApp::mouseButtonCallback(int button, int action, int mods)
{
    //std::cout << "Mouse button pressed" << std::endl;
}

bool SampleApp::init(void)
{
    std::cout << "Init..." << std::endl;

    // ustalamy domyślny kolor ekranu
    gl::glClearColor(0.2f, 0.2f, 0.2f, 1.f);

    // wlaczmy renderowanie tylko jednej strony poligon-ow
//    gl::glEnable(gl::GL_CULL_FACE);
    // ustalamy, ktora strona jest "przodem"
//    gl::glFrontFace(gl::GL_CCW);
    // ustalamy, ktorej strony nie bedziemy renderowac
//    gl::glCullFace(gl::GL_BACK);

    std::cout << "Shaders compilation..." << std::endl;
    // wczytanie z plikow i skompilowanie shaderow oraz utworzenie programu (VS + FS)
    std::string vs_path = "../../../shaders/simple_vs.glsl";
    std::string fs_path = "../../../shaders/simple_fs.glsl";
#if WIN32
    vs_path = "../../../../shaders/simple_vs.glsl";
    fs_path = "../../../../shaders/simple_fs.glsl";
#endif
    if (auto create_program_result = OGLAppFramework::createProgram(vs_path, fs_path))
    {
        simple_program = create_program_result.value();
    }
    else
    {
        std::cerr << "Error - can't create program..." << std::endl;
        return false;
    }

    // ustawienie informacji o lokalizacji atrybutu pozycji w vs (musi sie zgadzac z tym co mamy w VS!!!)
    const gl::GLuint vertex_position_loction = 0u;

    // ustawienie programu, ktory bedzie uzywany podczas rysowania
    gl::glUseProgram(simple_program);

    // stworzenie tablicy z danymi o wierzcholkach 3x (x, y, z)
    std::array<gl::GLfloat, 42u> vertices = {
        -0.5f, 0.f, 0.f,
        1.0f, 0.f, 0.f,

        0.5f, 0.f, 0.f,
        0.0f, 1.0f, 0.f,

        0.f, 0.5f, 0.f,
        0.f, 0.f, 1.0f,

        -0.4f, 0.f, 0.f,
        1.0f, 0.f, 0.f,

        -0.4f, -0.5f, 0.f,
        0.0f, 1.0f, 0.f,

        0.4f, -0.5f, 0.f,
        0.0f, 0.f, 1.0f,

        0.4f, 0.f, 0.f,
        0.0f, 1.0f, 0.f,
    };

    // stworzenie tablicy z danymi o indeksach
    std::array<gl::GLushort, 9u> indices = { 0, 1, 2, 3, 4, 5, 3, 5, 6};

    std::cout << "Generating buffers..." << std::endl;
    // stworzenie bufora
    gl::glGenBuffers(1, &vbo_handle);
    // zbindowanie bufora jako VBO
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo_handle);
    // alokacja pamieci dla bufora zbindowanego jako VBO i skopiowanie danych z tablicy "vertices"
    gl::glBufferData(gl::GL_ARRAY_BUFFER, vertices.size() * sizeof(gl::GLfloat), vertices.data(), gl::GL_STATIC_DRAW);
    // odbindowanie buffora zbindowanego jako VBO (zeby przypadkiem nie narobic sobie klopotow...)
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);

    // stworzenie bufora
    gl::glGenBuffers(1, &index_buffer_handle);
    // zbindowanie bufora jako IB
    gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, index_buffer_handle);
    // alokacja pamieci dla bufora zbindowanego jako IB i skopiowanie danych z tablicy "indeices"
    gl::glBufferData(gl::GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(gl::GLushort), indices.data(), gl::GL_STATIC_DRAW);
    // odbindowanie buffora zbindowanego jako IB (zeby przypadkiem nie narobic sobie klopotow...)
    gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, 0);

    // stworzenie VAO
    gl::glGenVertexArrays(1, &vao_handle);
    // zbindowanie VAO
    gl::glBindVertexArray(vao_handle);

    // zbindowanie VBO do aktualnego VAO
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo_handle);
    // ustalenie jak maja byc interpretowane dane z VBO
    gl::glVertexAttribPointer(vertex_position_loction, 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(float)* 6, nullptr);
    // odblokowanie mozliwosci wczytywania danych z danej lokalizacji
    gl::glEnableVertexAttribArray(vertex_position_loction);

    gl::glVertexAttribPointer(1, 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(float)* 6, (const void *)12);
    // odblokowanie mozliwosci wczytywania danych z danej lokalizacji
    gl::glEnableVertexAttribArray(1);

    // zbindowanie IB do aktualnego VAO
    gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, index_buffer_handle);
    // odbindowanie VAO (ma ono teraz informacje m.in. o VBO + IB, wiec gdy zajdzie potrzeba uzycia VBO + IB, wystarczy zbindowac VAO)
    gl::glBindVertexArray(0u);

    // odbindowanie buffora zbindowanego jako VBO (zeby przypadkiem nie narobic sobie klopotow...)
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
    // odbindowanie buffora zbindowanego jako bufor indeksow (zeby przypadkiem nie narobic sobie klopotow...)
    gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, 0);

    // na tym mozna zakonczyc
    // w tej prostej aplikacji bedziemy rysowac tylko 1 (powyzej stworzony) model, dlatego mozemy juz teraz ustawic odpowiednie dane dla naszych shaderow (nie beda sie one zmieniac co klatke...)
    // zeby narysowac nasz model musimy ustawic odpowiednie VBO + IB (a dzieki temu ze VAO ma o nich iformacje sprowadza sie to do ustawienia odpowiedniego VAO, a przez to reszte buforow)
    // Czyli znowu bindujemy VAO
    gl::glBindVertexArray(vao_handle);

	return true;
}

bool SampleApp::frame(float delta_time)
{
    // rozpoczynamy rysowanie uzywajac ustawionego programu (shader-ow) i ustawionych buforow
    gl::glDrawElements(gl::GL_TRIANGLES, 9, gl::GL_UNSIGNED_SHORT, nullptr);

	return true;
}

void SampleApp::release(void)
{
    std::cout << "Release..." << std::endl;

    // odbindowanie VAO
    gl::glBindVertexArray(0);
    if (vao_handle)
    {
        // usuniecie VAO
        gl::glDeleteVertexArrays(1, &vao_handle);
        vao_handle = 0u;
    }

    // odbindowanie VBO
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
    if (vbo_handle)
    {
        // usuniecie VBO
        gl::glDeleteBuffers(1, &vbo_handle);
        vbo_handle = 0u;
    }

    // odbindowanie IB
    glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, 0);
    if (index_buffer_handle)
    {
        // usuniecie IB
        gl::glDeleteBuffers(1, &index_buffer_handle);
        index_buffer_handle = 0u;
    }

    // ustawienie aktywnego programu na 0 (zaden)
    gl::glUseProgram(0);

    // usuniecie programu
    gl::glDeleteProgram(simple_program);
}
