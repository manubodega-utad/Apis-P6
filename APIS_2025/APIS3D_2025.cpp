#define GLAD_BIN

#include "mapi/common.h"
#include "mapi/System.h"
#include "mapi/Factory.h"
#include "mapi/CameraFPS.h"
#include "mapi/Object3D.h"
#include "mapi/Light.h"
#include "mapi/OrbitalLight.h"
using namespace std;

int main() {
    // 1.- Inicializar el backend de la clase “FactoryEngine” para poder usar OpenGL 4.0 y el input manager por defecto.
    Factory::setSelectedGraphicsBackend(GraphicsBackend::GL4);
    Factory::setSelectedInputBackend(InputBackend::GLFW);

    // 2.- Inicializar la clase System
    System::initSystem();

    // 3.- Crear un objeto de tipo Camera
    CameraFPS* camera = new CameraFPS(
        projectionType_e::PERSPECTIVE,
        glm::vec3(0.0f, 5.0f, 25.0f),       // position (Elevada un poco en Y para ver bien el humo)
        glm::vec3(0.0f, 1.0f, 0.0f),        // up
        glm::vec3(0.0f, 0.0f, -1.0f),       // lookAt (Hacia el centro)
        1.0f,
        0.01f
    );

	// 4.- Agregar la cámara al mundo y establecerla como cámara activa
    System::getWorld()->addCamera(camera);
    System::getWorld()->setActiveCamera(0);


    // 4) Ambient (P5)
    System::getWorld()->setAmbient(0.1f);

    // 5) LUCES
    Light* pointLight = new Light(
        Light::Type::POINT,
        glm::vec4(1.0f, 0.9f, 0.7f, 1.0f),
        glm::vec4(0.0f, 5.0f, 5.0f, 1.0f) 
    );
    System::getWorld()->addLight(pointLight);
    // 6) CARGAR EL TÓTEM
    auto totemFile = "data/column/column.msh";
    Object3D* totem = new Object3D(totemFile);
    totem->setScale(glm::vec4(0.01f, 0.01f, 0.01f, 1.0f)); // Escala uniforme de 0.01 exigida
    totem->computeModelMatrix();
    System::getWorld()->addObject(totem);

    // 7) CREAR EMISORES DE PARTÍCULAS

    // --- EMISOR DE HUMO ---
    // Asumimos que tienes un quad_smoke.msh que apunta a "smoke.png", blendMode="alpha", depthWrite="false", light="false"
    Emitter* smoke = new Emitter("data/column/smoke.msh", 5.0f, glm::vec4(0.0f, 8.0f, 0.0f, 1.0f), true);
    smoke->setRateRange(5.0f, 10.0f);
    smoke->setLifetimeRange(1.0f, 5.0f);
    smoke->setVelocityRange(glm::vec3(-0.1f, 1.0f, -0.1f), glm::vec3(0.1f, 4.0f, 0.1f));
    smoke->setSpinVelocityRange(30.0f, 60.0f);
    smoke->setScaleRange(0.05f, 0.1f);
    smoke->setColorRange(glm::vec4(1.0f), glm::vec4(1.0f));

    System::getWorld()->addEmitter(smoke);

    // --- EMISOR DE FUEGO ---
    // Asumimos que tienes un quad_flame.msh que apunta a "flame.png", blendMode="add", depthWrite="false", light="false"
    Emitter* fire = new Emitter("data/column/flame.msh", 10.0f, glm::vec4(0.0f, 8.0f, 0.0f, 1.0f), true);
    fire->setRateRange(10.0f, 25.0f);
    fire->setLifetimeRange(0.5f, 0.5f);
    fire->setVelocityRange(glm::vec3(-1.0f, 5.0f, -1.0f), glm::vec3(1.0f, 10.0f, 1.0f));
    fire->setSpinVelocityRange(0.0f, 0.0f);
    fire->setScaleRange(0.025f, 0.1f);
    fire->setColorRange(glm::vec4(1.0f), glm::vec4(1.0f));

    System::getWorld()->addEmitter(fire);

    // 7) Loop
    System::mainLoop();

    return 0;
}

