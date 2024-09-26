#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GameEngine.h"

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "Ошибка при инициализации GLFW" << std::endl;
        return -1;
    }

    // Создание окна
    GLFWwindow *window = glfwCreateWindow(800, 600, "The BoyJack Party Pack", NULL, NULL);
    if (!window) {
        std::cerr << "Ошибка при создании окна" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Инициализация GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Ошибка при инициализации GLEW" << std::endl;
        return -1;
    }

    // Инициализация игрового движка
    GameEngine gameEngine;
    gameEngine.initialize();

    // Основной цикл игры
    while (!glfwWindowShouldClose(window)) {
        // Обработка ввода
        processInput(window);

        // Очистка буфера
        glClear(GL_COLOR_BUFFER_BIT);

        // Обновление состояния игры
        gameEngine.update();

        // Отрисовка игры
        gameEngine.render();

        // Обновление экрана
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Освобождение ресурсов
    gameEngine.cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
