#include "sampleapp.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SampleApp::SampleApp() : OGLAppFramework::OGLApplication(1366u, 768u, "OGLSample 9", 3u, 3u), simple_program(0u), vbo_handle(0u), index_buffer_handle(0u), vao_handle(0u)
{
}

SampleApp::~SampleApp()
{
}

// do zad 12.
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

glm::mat4 camera(float Translate, glm::vec2 const & Rotate)
{
    // do zad 12
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
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
    std::string vs_path = "../../../shaders/simple_uniform_vs.glsl";
    std::string fs_path = "../../../shaders/simple_fs_textura.glsl";
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

    // zad 8. Załadowanie obrazka
    int width, height, bpp;
    uint8_t *texture_img = stbi_load("/Users/wojci/Desktop/Studia UJ/Grafika/cw/src/OGLSample8_Textury/multicolor.png", &width, &height, &bpp, 0);
    // tworzenie i bidnowanie testury
    gl::GLuint color_texture;
    gl::glGenTextures(1, &color_texture);
    gl::glBindTexture(gl::GL_TEXTURE_2D,color_texture);
    // ustawienie parametrów
    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);
    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);
    // załadowanie do niej obrazka
    gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, gl::GL_RGBA,width, height, 0,
            gl::GL_RGB, gl::GL_UNSIGNED_BYTE,  texture_img );

    // stworzenie tablicy z danymi o wierzcholkach 3x (x, y, z)
    // oraz kolorach
    // zad 6. Każdy trójkąt musi być unikalny alby mieć swój kolor.
    std::array<gl::GLfloat, 96u> vertices = {
        // Podstawa 1 trójkąt
        -0.5f, 0.5f, 0.f,
        0.191f, 0.5f, 0.f,

        -0.5f, -0.5f, 0.f,
        0.5f, 0.191f, 0.f,

        0.5f, -0.5f, 0.f,
        0.809f, 0.5f, 0.f,

        // Podstawa 2 trójkąt
        0.5f, 0.5f, 0.f,
        0.5f, 0.809f, 0.f,

        // bok 1 RED
        -0.5f, 0.5f, 0.f,
        0.191f, 0.5f, 0.f,

        -0.5f, -0.5f, 0.f,
        0.5f, 0.191f, 0.f,

        0.f,  0.f, 1.f,
        0.f, 0.f, 0.f,

        // bok 2 BLUE
        -0.5f, 0.5f, 0.f,
        0.191f, 0.5f, 0.f,

        0.f,  0.f, 1.f,
        0.f, 1.f, 0.f,

        0.5f, 0.5f, 0.f,
        0.5f, 0.809f, 0.f,

        // bok 3 CYAN
        0.f,  0.f, 1.f,
        1.f, 1.f, 0.f,

        0.5f, -0.5f, 0.f,
        0.809f, 0.5f, 0.f,

        0.5f, 0.5f, 0.f,
        0.5f, 0.809f, 0.f,

        // bok 4 YELLOW
        -0.5f, -0.5f, 0.f,
        0.5f, 0.191f, 0.f,

        0.5f, -0.5f, 0.f,
        0.809f, 0.5f, 0.f,

        0.f,  0.f, 1.f,
        1.f, 0.f, 0.f,
    };

    // stworzenie tablicy z danymi o indeksach
    std::array<gl::GLushort, 18u> indices = { 0, 1, 2, // podstawa 1
                                              0, 2, 3, // podstawa 2
                                              4, 5, 6, // RED
                                              13, 14, 15, // YELLOW
                                              10, 11, 12, // CYAN
                                              7, 8, 9 // BLUE
    };

    std::cout << "Generating buffers..." << std::endl;

    // zad 8.
    auto  color_sampler_location = gl::glGetUniformLocation(simple_program,"color");
    if(color_sampler_location == -1)  {
        std::cout<<"cannot get uniform color location\n";
    }
    gl::glUniform1i(color_sampler_location, 0);

    // zad 4.
    gl::GLuint ubo_handle(0u);
    gl::glGenBuffers(1,&ubo_handle);
    gl::glBindBuffer(gl::GL_UNIFORM_BUFFER, ubo_handle);
    gl::GLfloat intensity = 1.0;

    // Mac glsl convert to opengl410
    gl::GLuint intensity_ubo_index = gl::glGetUniformBlockIndex(simple_program, "Intensity");
    gl::glUniformBlockBinding(simple_program, intensity_ubo_index, 1);

    gl::glBindBufferBase(gl::GL_UNIFORM_BUFFER, 1, ubo_handle);
    gl::glBufferData(gl::GL_UNIFORM_BUFFER,sizeof(float), &intensity,gl::GL_STATIC_DRAW);
    gl::glBindBuffer(gl::GL_UNIFORM_BUFFER, 0);

    // zad 5.
    gl::GLuint ubo_transform;
    gl::glGenBuffers(1, &ubo_transform);
    gl::glBindBuffer(gl::GL_UNIFORM_BUFFER, ubo_transform);

    gl::GLuint transform_ubo_index = gl::glGetUniformBlockIndex(simple_program, "Transform");
    gl::glUniformBlockBinding(simple_program, transform_ubo_index, 0);

    glm::mat4 Model(1.0f);
    // lookat(camera position, what am i looking for, where up is)
    // zad 6. ważnym aspektem jest góra, jeżeli pozycja kamery na osi z jest większa niż 1 to góra wtedy była niżej
    glm::mat4 View = glm::lookAt(glm::vec3(-0.5f,-0.5f,2.5f), glm::vec3(0,0,0), glm::vec3(0,1,1));

    glm::mat4 Projection = glm::perspective(1.08f, (16.f/9.f), 0.1f, 20.f);

    // create transform matrix
    glm::mat4 camera = Projection * View * Model;

    // Apply transformation
    gl::glBufferData(gl::GL_UNIFORM_BUFFER, 16*sizeof(float), &camera, gl::GL_STATIC_DRAW);
    gl::glBindBuffer(gl::GL_UNIFORM_BUFFER, 0u);
    gl::glBindBufferBase(gl::GL_UNIFORM_BUFFER, 0, ubo_transform);

    // koniec zad. 5

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

    // zad. 7
    gl::glEnable(gl::GL_CULL_FACE);
    gl::glFrontFace(gl::GL_CCW);
    gl::glCullFace(gl::GL_BACK);

    // koniec zad. 7

	return true;
}

bool SampleApp::frame(float delta_time)
{
    // rozpoczynamy rysowanie uzywajac ustawionego programu (shader-ow) i ustawionych buforow
    for (int i = 0; i < 10; i++){
        gl::glDrawElements(gl::GL_TRIANGLES, 18, gl::GL_UNSIGNED_SHORT, nullptr);
    }

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
