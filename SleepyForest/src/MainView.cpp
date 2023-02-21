//
// Created by thefra985 on 16/02/23.
//

#include "MainView.h"
#include "Walnut/Input/Input.h"

MainView::MainView()
        : bg(0xFF9E9E9E),
          clear(Rendering::Size(1500, 500), 0xFF0E0E0E),
          background(Rendering::Size(1500, 500)) {
    pushLayer(&bg);
    pushLayer(&clear);
    pushLayer(&background);
}

void MainView::update(float elapsedTime) {
    View::update(elapsedTime);
    if (!Walnut::Input::IsKeyDown(Walnut::KeyCode::W)
        && !Walnut::Input::IsKeyDown(Walnut::KeyCode::D)
        && !Walnut::Input::IsKeyDown(Walnut::KeyCode::S)
        && !Walnut::Input::IsKeyDown(Walnut::KeyCode::A))
        return;
    int amount = (int) (std::min(elapsedTime, 0.125F) * 750); // Capping lag at 8FPS of delay
    if (Walnut::Input::IsKeyDown(Walnut::KeyCode::W)) {
        move(Rendering::Size(0, amount), false);
    } else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::D)) {
        move(Rendering::Size(amount, 0), true);
    } else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::S)) {
        move(Rendering::Size(0, amount), true);
    } else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::A)) {
        move(Rendering::Size(amount, 0), false);
    }
}

void MainView::move(const Rendering::Size &amount, bool positive) {
    auto current = background.locateObject(background.image);
    background.moveObject(background.image, positive ? *current + amount : *current - amount);
}
