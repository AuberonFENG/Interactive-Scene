#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Define the particle structure
struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    float lifetime;
};

// Define the particle system class
class ParticleSystem {
public:
    ParticleSystem(int maxParticles);
    void update(float deltaTime);
    void render(GLuint shaderProgram);
    void addParticle(const glm::vec3& position, const glm::vec3& velocity, float lifetime);

private:
    std::vector<Particle> particles;
    GLuint VAO, VBO;
    int maxParticles;
    void initBuffers();
};

#endif
