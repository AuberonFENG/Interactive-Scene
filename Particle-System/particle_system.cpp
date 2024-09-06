#include "particle_system.h"
#include <iostream>

// Constructor
ParticleSystem::ParticleSystem(int maxParticles) : maxParticles(maxParticles) {
    particles.reserve(maxParticles);
    initBuffers();
}

// Initialize VAO and VBO
void ParticleSystem::initBuffers() {
    float quadVertices[] = {
        // Positions
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

// Update the particles
void ParticleSystem::update(float deltaTime) {
    for (auto& particle : particles) {
        particle.position += particle.velocity * deltaTime;
        particle.lifetime -= deltaTime;
    }

    particles.erase(std::remove_if(particles.begin(), particles.end(),
                                    [](const Particle& p) { return p.lifetime <= 0.0f; }),
                    particles.end());
}

// Render the particles
void ParticleSystem::render(GLuint shaderProgram) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    for (const auto& particle : particles) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), particle.position);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
}

// Add a new particle
void ParticleSystem::addParticle(const glm::vec3& position, const glm::vec3& velocity, float lifetime) {
    if (particles.size() < maxParticles) {
        particles.push_back({position, velocity, lifetime});
    }
}
