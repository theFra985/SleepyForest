//
// Created by thefra985 on 16/02/23.
//

#ifndef SLEEPYFOREST_BACKGROUNDLAYER_H
#define SLEEPYFOREST_BACKGROUNDLAYER_H


#include "../rendering/Layer.h"

class BackgroundLayer : public Rendering::Layer {
public:
    const Rendering::RenderableObject image;

    BackgroundLayer();
};


#endif //SLEEPYFOREST_BACKGROUNDLAYER_H
