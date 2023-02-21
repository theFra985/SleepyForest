//
// Created by thefra985 on 14/02/23.
//

#ifndef SLEEPYFOREST_VIEW_H
#define SLEEPYFOREST_VIEW_H

#include <vector>
#include "Layer.h"

namespace Rendering {

    class View {
    public:
        void pushLayer(const Rendering::Layer *layer);

        virtual void update(float elapsedTime) {}

        virtual bool render(const Canvas &canvas, uint32_t width, uint32_t height) const;

        ~View();

    protected:
        std::vector<const Rendering::Layer *> _layers;
    };

} // Rendering

#endif //SLEEPYFOREST_VIEW_H
