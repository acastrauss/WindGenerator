#include "MainWindow.h"

float MainWindow::getXChange()
{
    float x = this->x_change;
    this->x_change = 0;
    return x;
}

float MainWindow::getYChange()
{
    float y = this->y_change;
    this->y_change = 0;
    return y;
}

MainWindow::MainWindow(const std::string& title, GLint width, GLint height)
{
	this->glfw_window_handle = nullptr;
	this->buffer_height = 0;
	this->buffer_width = 0;
	this->width = width;
	this->height = height;
	this->title = title;
    this->is_initial_movement = true;
    this->is_right_down = false;

	if (!initialize())
	{
		glfwTerminate();
		throw std::exception("Failed to initialize GLFW window");
	}

    keyboard = Keyboard::getInstance();
}

MainWindow::~MainWindow()
{
    glfwDestroyWindow(glfw_window_handle);
    glfwTerminate();
}

bool MainWindow::initialize()
{

    if (!RestartGLlog()) {
        return false;
    }

    GLlog("Starting GLFW\n%s\n", glfwGetVersionString());
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        glfwTerminate();
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_SAMPLES, 4);    

    /*GLFWmonitor* mon = glfwGetPrimaryMonitor();
    const GLFWvidmode* vmode = glfwGetVideoMode(mon);
    */
    this->glfw_window_handle = glfwCreateWindow(
        width, height, title.c_str(), NULL, NULL
    );


    if (!glfw_window_handle) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return false;
    }


    glfwGetFramebufferSize(glfw_window_handle, &buffer_width, &buffer_height);
    glfwMakeContextCurrent(glfw_window_handle);
    
    attachCallbacks();


    IMGUI_CHECKVERSION();
    imguiContext = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(glfw_window_handle, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    // start GLEW extension handler
    glewExperimental = GL_TRUE;


    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwDestroyWindow(glfw_window_handle);
        glfwTerminate();
        return false;
    }

    LogGLParams();

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"


    glViewport(0, 0, buffer_width, buffer_height);

    // sets a pointer to the current window 
    // so it can be retrieved in callbacks
    glfwSetWindowUserPointer(glfw_window_handle, this);



    return true;
}

void MainWindow::attachCallbacks()
{
    glfwSetFramebufferSizeCallback(glfw_window_handle, handleWindowSizeChangedCallback);
    glfwSetMouseButtonCallback(glfw_window_handle, handleMouseClickCallback);
    glfwSetCursorPosCallback(glfw_window_handle, handleMouseMovementCallback);
    glfwSetKeyCallback(glfw_window_handle, handleKeyPressCallback);
}


MainWindow* MainWindow::getCurrentWindowHandle(GLFWwindow* window)
{
    return static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
}

void MainWindow::handleWindowSizeChangedCallback(GLFWwindow* window, int width, int height)
{
    MainWindow* curr_window = MainWindow::getCurrentWindowHandle(window);

    curr_window->buffer_width  = width;
    curr_window->buffer_height = height;

    glViewport(0, 0, curr_window->buffer_width, curr_window->buffer_height);
}

void MainWindow::handleMouseMovementCallback(GLFWwindow* window, double xPos, double yPos)
{
    MainWindow* curr_window = MainWindow::getCurrentWindowHandle(window);

    if (!curr_window->is_right_down)
        return;

    if (curr_window->is_initial_movement)
    {
        curr_window->last_x = xPos;
        curr_window->last_y = yPos;

        curr_window->is_initial_movement= false;
    }

    curr_window->x_change= xPos - curr_window->last_x;
    curr_window->y_change = curr_window->last_y - yPos;

    curr_window->last_x = xPos;
    curr_window->last_y = yPos;

}

void MainWindow::handleMouseClickCallback(GLFWwindow* window, int button, int action, int mode)
{
    MainWindow* curr_window = MainWindow::getCurrentWindowHandle(window);
    
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        curr_window->is_right_down = true;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        curr_window->is_right_down= false;
}

void MainWindow::handleKeyPressCallback(GLFWwindow* window, int key, int code, int action, int mode)
{
    MainWindow* curr_window = MainWindow::getCurrentWindowHandle(window);
    curr_window->keyboard->handleKeyPress(key, action);

    if (curr_window->keyboard->checkKeySet(GLFW_KEY_ESCAPE))
        curr_window->setShouldClose(GL_TRUE);
    
}

void glfw_error_callback(int error, const char* desc) {
    GLlogError("GLFW ERROR: code %i msg:%s\n", error, desc);
}
