//
// Created by thefra985 on 21/02/23.
//

#ifndef SLEEPYFOREST_CANVAS_H
#define SLEEPYFOREST_CANVAS_H

#include <cstdint>

namespace Rendering {

    class Canvas {
    public:
        Canvas(uint32_t *buffer, uint32_t width) : _buffer(buffer), _width(width) {}

//        Canvas(const Canvas &source) : _buffer(source._buffer), _width(source._width) {}

        uint32_t *operator[](uint32_t y) { return _buffer + (y * _width); }

        uint32_t *operator[](uint32_t y) const { return _buffer + (y * _width); }

    private:
        uint32_t *_buffer = nullptr;
        uint32_t _width;
    };

} // Rendering

#endif //SLEEPYFOREST_CANVAS_H
