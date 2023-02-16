//
// Created by thefra985 on 16/02/23.
//

#include "MainView.h"
#include "Walnut/Input/Input.h"

MainView::MainView() {
    pushLayer(&background);
}

void MainView::update(float elapsedTime) {
    const int amount = 25;
    View::update(elapsedTime);
    if (Walnut::Input::IsKeyDown(Walnut::KeyCode::W)) {
        move(Rendering::Size(0, -amount));
    } else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::D)) {
        move(Rendering::Size(amount, 0));
    } else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::S)) {
        move(Rendering::Size(0, amount));
    } else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::A)) {
        move(Rendering::Size(-amount, 0));
    }
}

void MainView::move(const Rendering::Size &amount) {
    auto current = background.locateObject(background.image);
    background.moveObject(background.image, *current + amount);
}
