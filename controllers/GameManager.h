//
// Created by particleg on 2022/11/20.
//

#pragma once

#include <QBitArray>
#include <QImage>
#include <QQuickItem>
#include <models/Field.h>
#include <models/Mino.h>

namespace CuteMino::Controllers {
    class GameManager : public QQuickItem {
    Q_OBJECT
    public:
        explicit GameManager(QQuickItem *parent = nullptr);

        Q_INVOKABLE void loadSettings();

        Q_INVOKABLE void exportSettings();

        uint32_t _rowCount{}, _columnCount{};
        double _screenHeight{}, _screenWidth{}, _uiScale{}, _fieldHeight{}, _fieldWidth{}, _minoEdgeLength{};

        QVector<QVector<int>> _data{};
        QVector<QBitArray> _occupancy{};
        QHash<Types::Mino, QImage> _minoAssets{};

    private:
        double _frameHeight{}, _frameWidth{}, _frameThickness{};

    signals:

        void gameStart(GameManager *self);
    };
}
