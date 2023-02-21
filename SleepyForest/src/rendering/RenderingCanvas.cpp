//
// Created by thefra985 on 15/02/23.
//

#include <algorithm>
#include "RenderingCanvas.h"

namespace Rendering {
    void RenderingCanvas::set(uint32_t x, uint32_t y, uint32_t color) const {
        if (x > _boundingBox.getWidth() || y > _boundingBox.getHeight())
            return;
//        _buffer[_boundingBox.getX() + x + ((_boundingBox.getY() + y) * _boundingBox.getGlobalWidth())] = color;
        _canvas[_boundingBox.getY() + y][_boundingBox.getX() + x] = color;
    }

    void RenderingCanvas::copy(const uint32_t *data, const BoundingBox &target) const {
        auto offsetY = _boundingBox.getY() + target.getY();
        auto maxSourceY = std::min(target.getHeight(), _boundingBox.getHeight());
        auto maxSourceWidth = std::min(target.getX() + target.getWidth(), _boundingBox.getWidth()) - target.getX();
        for (uint32_t y = 0; y < maxSourceY; y++)
            std::copy_n(data + (y * target.getWidth()), maxSourceWidth,
//                        _buffer + (_boundingBox.getX() + ((y + offsetY) * globalWidth)));
                        _canvas[y + offsetY] + _boundingBox.getX());
    }

    void RenderingCanvas::paint(uint32_t color, const BoundingBox &target) const {
        auto offsetY = _boundingBox.getY() + target.getY();
        auto offsetX = _boundingBox.getX() + target.getX();
        auto maxSourceY = std::min(target.getHeight(), _boundingBox.getHeight());
//        auto maxSourceX = std::min(target.getWidth(), _boundingBox.getWidth());
        auto maxSourceWidth = std::min(target.getX() + target.getWidth(), _boundingBox.getWidth()) - target.getX();
//        auto globalWidth = _boundingBox.getGlobalWidth();
        for (uint32_t y = 0; y < maxSourceY; y++) {
            auto row = _canvas[y + offsetY];
            for (uint32_t x = 0; x < maxSourceWidth; x++)
//                _buffer[(x + offsetX) + ((y + offsetY) * globalWidth)] = color;
                row[x + offsetX] = color;
        }
    }
} // Rendering