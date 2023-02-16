//
// Created by thefra985 on 15/02/23.
//

#ifndef SLEEPYFOREST_RENDERINGCANVAS_H
#define SLEEPYFOREST_RENDERINGCANVAS_H

#include <cstdint>
#include "BoundingBox.h"

namespace Rendering {

    class RenderingCanvas {
    public:
        RenderingCanvas(uint32_t *buffer, uint32_t width, uint32_t height)
                : _buffer(buffer), _boundingBox(0, 0, width, height) {}

        RenderingCanvas(uint32_t *buffer, const BoundingBox &boundingBox)
                : _buffer(buffer), _boundingBox(boundingBox) {}

        void copy(const uint32_t *data, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            copy(data, BoundingBox(x, y, width, height));
        }

        void copy(const uint32_t *data, const BoundingBox &target);

        void set(uint32_t x, uint32_t y, uint32_t color);

        [[nodiscard]] BoundingBox getBoundingBox() const { return _boundingBox; }

        void updateOrigin(uint32_t x, uint32_t y) { _boundingBox.updateOrigin(x, y); }

    private:
        uint32_t *_buffer = nullptr;
        TargetBox _boundingBox;
    };

} // Rendering

#endif //SLEEPYFOREST_RENDERINGCANVAS_H
