#pragma once
#include "Billboard.h"
#include <string>
#include <glm/glm.hpp>

class Particle : public Billboard {
private:
    glm::vec4 vel;
    double lifeTime;
    double remainingLifeTime;
    bool autoFade;

public:
    // Constructor
    Particle(std::string mshFile, const glm::vec3& vel, float spinVel, double lifetime, bool autofade);

    // Destructor
    virtual ~Particle();

    // Getters
    float getRemainingLifetime() const;

    // Métodos
    virtual void step(float deltaTime) override;
};