//
// Created by thefra985 on 15/02/23.
//

#include <algorithm>
#include "RenderingCanvas.h"

namespace Rendering {
    void RenderingCanvas::set(uint32_t x, uint32_t y, uint32_t color) {
        if (x > _boundingBox.getWidth() || y > _boundingBox.getHeight())
            return;
        _buffer[_boundingBox.getX() + x + ((_boundingBox.getY() + y) * _boundingBox.getGlobalWidth())] = color;
    }

    void RenderingCanvas::copy(const uint32_t *data, const BoundingBox &target) {
        /*auto offsetX = _boundingBox.getX() + target.getX();
        auto maxX = _boundingBox.getX()
                    + std::min(target.getWidth() + target.getX(), _boundingBox.getWidth() + target.getX());*/
        auto offsetY = _boundingBox.getY() + target.getY();
        auto maxY = _boundingBox.getY()
                    + std::min(target.getHeight() + target.getY(), _boundingBox.getHeight() + target.getY());
        auto maxSourceWidth = std::min(target.getX() + target.getWidth(), _boundingBox.getWidth()) - target.getX();
        auto globalWidth = _boundingBox.getGlobalWidth();
//        memcpy()
        for (uint32_t y = _boundingBox.getY() + target.getY(); y < maxY; y++)
//            for (uint32_t x = _boundingBox.getX() + target.getX(); x < maxX; x++)
//                _buffer[x + (y * globalWidth)] = data[(x - offsetX) + ((y - offsetY) * target.getWidth())];
//            std::copy_n(data[((y - offsetY) * target.getWidth())], maxX - offsetX,);
            /*std::copy_n(data + ((y - offsetY) * target.getWidth()), target.getWidth(),
                        _buffer + (_boundingBox.getX() + (y * globalWidth)));*/
            std::copy_n(data + ((y - offsetY) * target.getWidth()), maxSourceWidth,
                        _buffer + (_boundingBox.getX() + (y * globalWidth)));
    }
} // Rendering