//
// Created by thefra985 on 15/02/23.
//

#include "RenderingCanvas.h"

namespace Rendering {
    void RenderingCanvas::set(uint32_t x, uint32_t y, uint32_t color) {
        if (_boundingBox.getX() + x > _boundingBox.getWidth()
            || _boundingBox.getY() + y > _boundingBox.getHeight())
            return;
        _buffer[_boundingBox.getX() + x + ((_boundingBox.getY() + y) * _boundingBox.getGlobalWidth())] = color;
    }
} // Rendering