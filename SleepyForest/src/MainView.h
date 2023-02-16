//
// Created by thefra985 on 16/02/23.
//

#ifndef SLEEPYFOREST_MAINVIEW_H
#define SLEEPYFOREST_MAINVIEW_H


#include "rendering/View.h"
#include "layers/BackgroundLayer.h"

class MainView : public Rendering::View {
public:
    MainView();

    void update(float elapsedTime) override;

protected:
    BackgroundLayer background;

private:
    void move(const Rendering::Size &amount);
};


#endif //SLEEPYFOREST_MAINVIEW_H
