//
// Created by thefra985 on 14/02/23.
//

#include "Layer.h"

namespace Rendering {
    bool Layer::render(const RenderingCanvas &canvas) const {
        RenderingCanvas target(canvas);
//        auto target = TargetBox(canvas.getBoundingBox());
        for (const auto &slot: _objects) {
            target.updateOrigin(slot.first.getX(), slot.first.getY());
//            target.updateOrigin(slot.first.first, slot.first.second);
            for (const auto &obj: slot.second)
                obj->render(target);
        }
        return false;
    }

    void Layer::setObject(const Location &location, const RenderableObject *object) {
        auto existing = _objects.find(location);
        if (existing == _objects.end()) {
            std::vector<const RenderableObject *> data;
            data.push_back(object);
            _objects.insert(std::make_pair(location, data));
        } else
            existing->second.push_back(object);
    }
} // Rendering