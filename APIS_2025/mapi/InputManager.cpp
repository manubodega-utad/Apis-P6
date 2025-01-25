#include "InputManager.h"


bool InputManager::isPressed(int key) const {
    auto it = keyState.find(key);
    if (it != keyState.end()) {
        return it->second;
    }
    return false;
}