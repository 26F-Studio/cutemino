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

        [[nodiscard]] Types::Mino type(bool original = false) const;

        QPoint position;
        Orientation orientation;
    private:
        Types::Mino _originalType, _currentType;
    };
}