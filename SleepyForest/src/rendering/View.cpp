//
// Created by thefra985 on 14/02/23.
//

#include "View.h"

namespace Rendering {
    void View::pushLayer(const Rendering::Layer *layer) {
        _layers.push_back(layer);
    }
} // Rendering