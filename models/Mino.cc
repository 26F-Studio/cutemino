//
// Created by particleg on 2022/11/20.
//

#include <models/Mino.h>

using namespace CuteMino;
using namespace CuteMino::Models;

Mino::Mino(
        Types::Mino type,
        QPoint position,
        Orientation orientation
) : originalType(type),
    currentType(type),
    position(position),
    orientation(orientation) {}