//
// Created by particleg on 2022/11/20.
//

#pragma once

#include <QImage>
#include <types/Mino.h>

namespace CuteMino::Models {
    class Mino {
    public:
        explicit Mino(Types::Mino type);

        [[nodiscard]] Types::Mino type() const;

        [[nodiscard]] QImage image() const;

        [[nodiscard]] int rotation() const;

        [[nodiscard]] int x() const;

        [[nodiscard]] int y() const;

        void rotate();

        void move(int x, int y);

    private:
        Types::Mino _type;
        QImage _minoQImage{};
    };
}