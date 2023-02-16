//
// Created by thefra985 on 16/02/23.
//

#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer() : image("/home/thefra985/Tools/pixray/data/a.png") {
    setObject(&image, Rendering::Location(10, 10));
}
