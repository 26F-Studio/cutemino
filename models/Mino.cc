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
) : _originalType(type),
    _currentType(type),
    position(position),
    orientation(orientation) {}

Types::Mino Mino::type(bool original) const {
    return original ? _originalType : _currentType;
}
