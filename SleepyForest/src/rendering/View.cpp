//
// Created by thefra985 on 14/02/23.
//

#include "View.h"

namespace Rendering {
    void View::pushLayer(const Rendering::Layer *layer) {
        _layers.push_back(layer);
    }

    bool View::render(uint32_t *canvas, uint32_t width, uint32_t height) const {
        RenderingCanvas target(canvas, width, height);
        for (const auto &layer: _layers)
            layer->render(target);
        return true;
    }

    View::~View() {
        for (const auto &layer: _layers)
            delete layer;
    }
} // Rendering