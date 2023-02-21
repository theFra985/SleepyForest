//
// Created by thefra985 on 16/02/23.
//

#ifndef SLEEPYFOREST_MAINVIEW_H
#define SLEEPYFOREST_MAINVIEW_H


#include "rendering/View.h"
#include "layers/BackgroundLayer.h"
#include "layers/CleanupLayer.h"

class MainView : public Rendering::View {
public:
    MainView();

    void update(float elapsedTime) override;

protected:
    CleanupLayer clear;
    CleanupLayer bg;
    BackgroundLayer background;

private:
    void move(const Rendering::Size &amount, bool positive);
};


#endif //SLEEPYFOREST_MAINVIEW_H
