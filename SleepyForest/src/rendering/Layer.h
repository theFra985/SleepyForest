//
// Created by thefra985 on 14/02/23.
//

#ifndef SLEEPYFOREST_LAYER_H
#define SLEEPYFOREST_LAYER_H

#include <vector>
#include "RenderableObject.h"

namespace Rendering {

    class Layer {
    public:
        bool render();
    private:
        std::vector<Rendering::RenderableObject> _objects;
    };

} // Rendering

#endif //SLEEPYFOREST_LAYER_H
