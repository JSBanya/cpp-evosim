#include "main.h"

int main() {
    if(initGLFW() == -1) {
        return -1;
    }

    if(initOpenGL() == -1) {
        return -1;
    }

    // Seed the PRNG
    srand(time(NULL));

    // Create world objects
    Camera defaultCamera(WORLD_WIDTH / 2, WORLD_HEIGHT / -2, 80, 70, SCR_WIDTH, SCR_HEIGHT, 0.01, 300);
    main_camera = &defaultCamera;

    World world(WORLD_WIDTH, WORLD_HEIGHT, WORLD_MAX_CELLS, main_camera);

    // Timing variables
    const double CONVERSION_FACTOR = 1000.0 / 30.0; // Conversion number: 1x10^3 milliseconds (1 second) = 60 ticks per second
    int ticksPerSecond = 0, framesPerSecond = 0;
    double delta = 0.0, secondsDelta = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    auto dur = end - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    // Main lopp
    while (!glfwWindowShouldClose(main_window)) {
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        delta += (ms / CONVERSION_FACTOR);
        secondsDelta += ms;
        start = std::chrono::high_resolution_clock::now();

        // Print performance data
        if(secondsDelta >= 1000.0) {
            std::cout << "[ Ticks per second: " << ticksPerSecond << " | Frames per second: " << framesPerSecond << " ]" << std::endl;
            ticksPerSecond = 0;
            framesPerSecond = 0;
            secondsDelta -= 1000.0;
        }

        // Tick events when tick is due
        if(delta >= 1.0) {
            world.tick();
            glfwPollEvents();
            processInput(main_window, main_camera);
            ticksPerSecond++;
            delta--;
        }

        // Render world
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        world.render();
        glfwSwapBuffers(main_window);
        framesPerSecond++;
    }

    glfwTerminate();
    return 0;
}

int initOpenGL() {
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << "OpenGL version" << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    main_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Evosim", NULL, NULL);
    if(main_window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(main_window);
    glfwSwapInterval(1);
    glfwSetScrollCallback(main_window, scrollCallback);
}

void scrollCallback(GLFWwindow* window, double xpos, double ypos) {
    const float SCROLL_SPEED = 0.5f;
    if(ypos < 0) {
        main_camera->addPos(0.0f, 0.0f, -1.0f * SCROLL_SPEED);
    } else if(ypos > 0) {
        main_camera->addPos(0.0f, 0.0f, SCROLL_SPEED);
    }
}

