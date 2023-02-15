//
// Created by thefra985 on 15/02/23.
//

#ifndef SLEEPYFOREST_RENDERABLEOBJECT_H
#define SLEEPYFOREST_RENDERABLEOBJECT_H

#include <iostream>
#include "RenderingCanvas.h"
#include "Walnut/Image.h"
#include "stb_image.h"

namespace Rendering {

    class RenderableObject {
    public:
        explicit RenderableObject(const std::string_view imagePath)
                : data(reinterpret_cast<uint32_t *>(
                               stbi_load(std::string(imagePath).c_str(), &width, &height, nullptr, 4))) {
            if (!data)
                std::cerr << "Failed to load asset " << imagePath << std::endl;
        }

        bool render(RenderingCanvas &canvas) const; // NOLINT(modernize-use-nodiscard)

        ~RenderableObject() {
            stbi_image_free(data);
        }

    private:
        uint32_t *data;
        int width, height;
    };

} // Rendering

#endif //SLEEPYFOREST_RENDERABLEOBJECT_H
