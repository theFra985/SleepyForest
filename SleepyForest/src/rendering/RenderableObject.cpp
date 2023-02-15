//
// Created by thefra985 on 15/02/23.
//

#include "RenderableObject.h"

namespace Rendering {
    bool RenderableObject::render(RenderingCanvas &canvas) const {
        for (int x = 0; x < width; x++)
            for (int y = 0; y < height; y++)
                canvas.set(x, y, data[x + (y * width)]);
        return false;
    }
} // Rendering