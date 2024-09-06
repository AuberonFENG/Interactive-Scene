cmake_minimum_required(VERSION 3.10)
project(ParticleSystem)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(particle_system main.cpp particle_system.cpp)
target_link_libraries(particle_system PRIVATE GLEW::GLEW glfw ${OPENGL_LIBRARIES} glm::glm)
