//
// Created by particleg on 2022/11/20.
//

#pragma once

#include <QImage>
#include <QPoint>
#include <types/Mino.h>

namespace CuteMino::Models {
    class Mino {
    public:
        enum class Orientation {
            Down,
            Left,
            Right,
            Up,
        };

        Mino(
                Types::Mino type,
                QPoint position,
                Orientation orientation = Orientation::Up
        );

        Mino(const Mino &mino) : originalType(mino.originalType),
                                 currentType(mino.currentType),
                                 position(mino.position),
                                 orientation(mino.orientation) {}

        const Types::Mino originalType;
        Types::Mino currentType;
        QPoint position;
        Orientation orientation;
    };
}