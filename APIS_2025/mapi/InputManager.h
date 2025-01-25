#pragma once
#include <map>

class InputManager {
protected:
    std::map<int, bool> keyState;

public:
    // Constructor
    InputManager() = default;

    // Destructor
    virtual ~InputManager() = default;

    // Métodos
    virtual void init() = 0;
    virtual bool isPressed(int key) const;
};
