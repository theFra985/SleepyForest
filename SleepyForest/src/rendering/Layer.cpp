//
// Created by thefra985 on 14/02/23.
//

#include "Layer.h"

namespace Rendering {
    bool Layer::render(const RenderingCanvas &canvas) const {
        auto s = size;
        if (s.getHeight() == 0 && s.getWidth() == 0)
            s = canvas.getBoundingBox().getSize();
        RenderingCanvas target(canvas);
//        auto target = TargetBox(canvas.getBoundingBox());
        for (const auto &slot: _objects) {
            target.updateOrigin(slot.first.getX(), slot.first.getY());
//            target.updateOrigin(slot.first.first, slot.first.second);
            for (const auto &obj: slot.second) {
                if ((slot.first/* + obj->size*/) > canvas.getBoundingBox())
                    continue;
                auto alteredSize = (slot.first + obj->size) > s;
                if (alteredSize)
                    target.setSize(s - slot.first);
                obj->render(target);
                if (alteredSize)
                    target.restoreSize();
            }
        }
        return false;
    }

    const Location *Layer::locateObject(const RenderableObject *object) {
        auto pair = _objectOrigin.find(object);
        if (pair == _objectOrigin.end())
            return nullptr;
        return &pair->second;
    }

    bool Layer::setObject(const RenderableObject *object, const Location &location) {
        if (location > size) {
            // Do I want to snap it to the border instead of blocking it?
            std::cerr << "Prevented placement of object at invalid location "
                      << location << " out of layer bounds [size: " << size << "]" << std::endl;
            return false;
        }
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
        return true;
    }

    bool Layer::moveObject(const RenderableObject *object, const Location &location) {
        if (location > size) {
            // Do I want to snap it to the border instead of blocking it?
            std::cerr << "Prevented invalid move out of layer bounds [location: "
                      << location << ", size: " << size << "]" << std::endl;
            return false;
        }
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