//
// Created by particleg on 2022/11/20.
//

#pragma once

#include <QVector>

namespace CuteMino::Models {
    class Field {
    public:
        explicit Field(uint64_t rowCount, uint64_t columnCount);

        std::atomic<uint64_t> rowCount, columnCount;
    };
}