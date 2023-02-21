//
// Created by thefra985 on 17/02/23.
//

#ifndef SLEEPYFOREST_CLEANUPLAYER_H
#define SLEEPYFOREST_CLEANUPLAYER_H

#include "../rendering/Layer.h"

class CleanupLayer : public Rendering::Layer {
public:
    const uint32_t _color;

    explicit CleanupLayer(uint32_t color = 0xFF000000)
            : Rendering::Layer(), _color(color) {
    }

    explicit CleanupLayer(const Rendering::Size &size, uint32_t color = 0xFF000000)
            : Rendering::Layer(size), _color(color) {
    }

    bool render(const Rendering::RenderingCanvas &canvas) const override {
        if (size.getWidth() == 0 && size.getHeight() == 0)
            canvas.paint(_color, Rendering::BoundingBox(canvas.getBoundingBox().getSize()));
        else
            canvas.paint(_color, Rendering::BoundingBox(size));
        return true;
    }
};

#endif //SLEEPYFOREST_CLEANUPLAYER_H
