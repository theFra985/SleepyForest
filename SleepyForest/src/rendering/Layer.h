//
// Created by thefra985 on 14/02/23.
//

#ifndef SLEEPYFOREST_LAYER_H
#define SLEEPYFOREST_LAYER_H

#include "RenderableObject.h"
#include "RenderingCanvas.h"
#include <map>
#include <set>

namespace Rendering {

    class Layer {
    public:
        bool render(const RenderingCanvas &canvas) const; // NOLINT(modernize-use-nodiscard)

        const Location *locateObject(const RenderableObject *object);

        const Location *locateObject(const RenderableObject &object) { return locateObject(&object); }

        void setObject(const RenderableObject *object, const Location &location);

        void setObject(const RenderableObject &object, const Location &location) { setObject(&object, location); }

        bool moveObject(const RenderableObject *object, const Location &location);

        bool moveObject(const RenderableObject &object, const Location &location) {
            return moveObject(&object, location);
        }

        ~Layer();

    private:
        std::map<Location, std::set<const RenderableObject *>> _objects;
        std::map<const RenderableObject *, Location> _objectOrigin;
    };

} // Rendering

#endif //SLEEPYFOREST_LAYER_H
