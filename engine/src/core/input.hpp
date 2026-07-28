#ifndef INPUT_HPP
#define INPUT_HPP

#include <unordered_map>

#include <SDL3/SDL.h>

enum class Keys {
    None = 0,
    Backspace = SDL_SCANCODE_BACKSPACE,
    Tab = SDL_SCANCODE_TAB,
    Enter = SDL_SCANCODE_RETURN,
    Escape = SDL_SCANCODE_ESCAPE,
    Space = SDL_SCANCODE_SPACE,

    // Letters
    A = SDL_SCANCODE_A,
    B = SDL_SCANCODE_B,
    C = SDL_SCANCODE_C,
    D = SDL_SCANCODE_D,
    E = SDL_SCANCODE_E,
    F = SDL_SCANCODE_F,
    G = SDL_SCANCODE_G,
    H = SDL_SCANCODE_H,
    I = SDL_SCANCODE_I,
    J = SDL_SCANCODE_J,
    K = SDL_SCANCODE_K,
    L = SDL_SCANCODE_L,
    M = SDL_SCANCODE_M,
    N = SDL_SCANCODE_N,
    O = SDL_SCANCODE_O,
    P = SDL_SCANCODE_P,
    Q = SDL_SCANCODE_Q,
    R = SDL_SCANCODE_R,
    S = SDL_SCANCODE_S,
    T = SDL_SCANCODE_T,
    U = SDL_SCANCODE_U,
    V = SDL_SCANCODE_V,
    W = SDL_SCANCODE_W,
    X = SDL_SCANCODE_X,
    Y = SDL_SCANCODE_Y,
    Z = SDL_SCANCODE_Z,

    // Numbers
    D0 = SDL_SCANCODE_0,
    D1 = SDL_SCANCODE_1,
    D2 = SDL_SCANCODE_2,
    D3 = SDL_SCANCODE_3,
    D4 = SDL_SCANCODE_4,
    D5 = SDL_SCANCODE_5,
    D6 = SDL_SCANCODE_6,
    D7 = SDL_SCANCODE_7,
    D8 = SDL_SCANCODE_8,
    D9 = SDL_SCANCODE_9,

    // Function Keys
    F1 = SDL_SCANCODE_F1,
    F2 = SDL_SCANCODE_F2,
    F3 = SDL_SCANCODE_F3,
    F4 = SDL_SCANCODE_F4,
    F5 = SDL_SCANCODE_F5,
    F6 = SDL_SCANCODE_F6,
    F7 = SDL_SCANCODE_F7,
    F8 = SDL_SCANCODE_F8,
    F9 = SDL_SCANCODE_F9,
    F10 = SDL_SCANCODE_F10,
    F11 = SDL_SCANCODE_F11,
    F12 = SDL_SCANCODE_F12
};

class Input {
public:
    static void updateState();

    static bool isKeyDown(Keys key);
    static bool isKeyPressed(Keys key);
    static bool isKeyReleased(Keys key);

private:
    static inline std::unordered_map<int, bool> m_previousKeyboardState;
    static inline std::unordered_map<int, bool> m_currentKeyboardState;
};

#endif