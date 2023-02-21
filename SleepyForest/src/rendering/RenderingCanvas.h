//
// Created by thefra985 on 15/02/23.
//

#ifndef SLEEPYFOREST_RENDERINGCANVAS_H
#define SLEEPYFOREST_RENDERINGCANVAS_H

#include <cstdint>
#include "BoundingBox.h"
#include "Canvas.h"

namespace Rendering {

    class RenderingCanvas {
    public:
        RenderingCanvas(const Canvas &canvas, uint32_t width, uint32_t height)
                : _canvas(canvas), _boundingBox(0, 0, width, height) {}

        RenderingCanvas(const Canvas &canvas, const BoundingBox &boundingBox)
                : _canvas(canvas), _boundingBox(boundingBox) {}

        void copy(const uint32_t *data, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            copy(data, BoundingBox(x, y, width, height));
        }

        void copy(const uint32_t *data, const BoundingBox &target) const;

        void paint(uint32_t color, const BoundingBox &target) const;

        void set(uint32_t x, uint32_t y, uint32_t color) const;

        [[nodiscard]] BoundingBox getBoundingBox() const { return _boundingBox; }

        void updateOrigin(uint32_t x, uint32_t y) { _boundingBox.updateOrigin(x, y); }

        void setSize(const Size &smallerSize) { _boundingBox.setSize(smallerSize); }

        void restoreSize() { _boundingBox.restoreSize(); }

    private:
        const Canvas _canvas;
        TargetBox _boundingBox;
    };

} // Rendering

#endif //SLEEPYFOREST_RENDERINGCANVAS_H
