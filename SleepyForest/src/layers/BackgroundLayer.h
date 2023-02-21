//
// Created by thefra985 on 16/02/23.
//

#ifndef SLEEPYFOREST_BACKGROUNDLAYER_H
#define SLEEPYFOREST_BACKGROUNDLAYER_H


#include "../rendering/Layer.h"

class BackgroundLayer : public Rendering::Layer {
public:
    const Rendering::RenderableObject image;

    explicit BackgroundLayer(const Rendering::Size &size)
            : Rendering::Layer(size), image("/home/thefra985/Tools/pixray/data/a.png") {
        setObject(&image, Rendering::Location(25, 25));
    }
};


#endif //SLEEPYFOREST_BACKGROUNDLAYER_H
