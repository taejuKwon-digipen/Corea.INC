
#include "../../library/include/doodle/window.hpp"
#include "../../library/include/doodle/drawing.hpp"     // set_frame_of_reference, set_image_mode, clear_background
#include "Engine.h"
#include "Window.h"

void Window::Init(std::string windowName) {
    doodle::create_window(windowName, 1440, 810);
    doodle::set_frame_of_reference(doodle::FrameOfReference::RightHanded_OriginBottomLeft);
}

void Window::Resize(int newWidth, int newHeight) {
    windowSize.x = newWidth;
    windowSize.y = newHeight;
}

math::ivec2 Window::GetSize() {
    return windowSize;
}

void Window::Clear(unsigned int color) {
    doodle::clear_background(doodle::HexColor{ color });
}

void Window::Update() {
    doodle::update_window();
}

void on_window_resized(int new_width, int new_height) {
    Engine::GetLogger().LogEvent("Window Resized");
    Engine::GetWindow().Resize(new_width, new_height);
}