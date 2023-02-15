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

    private:
        std::vector<const Rendering::Layer *> _layers;
    };

} // Rendering

#endif //SLEEPYFOREST_VIEW_H
