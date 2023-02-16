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

    const Location *Layer::locateObject(const RenderableObject *object) {
        auto pair = _objectOrigin.find(object);
        if (pair == _objectOrigin.end())
            return nullptr;
        return &pair->second;
    }

    void Layer::setObject(const RenderableObject *object, const Location &location) {
        // Push object in location
        auto existing = _objects.find(location);
        if (existing == _objects.end()) {
            std::set<const RenderableObject *> data;
            data.insert(object);
            _objects.insert(std::make_pair(location, data));
        } else
            existing->second.insert(object);
        // Insert origin
        _objectOrigin.insert(std::make_pair(object, location));
    }

    bool Layer::moveObject(const RenderableObject *object, const Location &location) {
        auto pair = _objectOrigin.find(object);
        if (pair == _objectOrigin.end())
            return false;
        // Remove object from old location
        auto existing = _objects.find(pair->second);
        if (existing != _objects.end()) {
            existing->second.erase(object);
        }
        // Push object in new location
        existing = _objects.find(location);
        if (existing == _objects.end()) {
            std::set<const RenderableObject *> data;
            data.insert(object);
            _objects.insert(std::make_pair(location, data));
        } else
            existing->second.insert(object);
        // Update origin
        _objectOrigin.insert_or_assign(object, location);
        return true;
    }

    Layer::~Layer() {
        for (const auto &slot: _objects)
            for (const auto &obj: slot.second)
                delete obj;
    }
} // Rendering