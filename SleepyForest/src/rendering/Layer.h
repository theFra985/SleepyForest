//
// Created by thefra985 on 14/02/23.
//

#ifndef SLEEPYFOREST_LAYER_H
#define SLEEPYFOREST_LAYER_H

#include <vector>
#include "RenderableObject.h"
#include "RenderingCanvas.h"
#include <map>

namespace Rendering {

    class Layer {
    public:
        bool render(const RenderingCanvas &canvas) const; // NOLINT(modernize-use-nodiscard)

        void setObject(const Location &location, const RenderableObject *object);

    private:
        std::map<Location, std::vector<const RenderableObject *>> _objects;
    };

} // Rendering

#endif //SLEEPYFOREST_LAYER_H
