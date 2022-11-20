//
// Created by particleg on 2022/11/20.
//

#pragma once

#include <QBitArray>
#include <QImage>
#include <QQueue>
#include <QQuickPaintedItem>
#include <QVector>

#include <models/Field.h>
#include <models/Mino.h>

namespace CuteMino::Controllers {
    class GameManager : public QQuickPaintedItem {
    Q_OBJECT
    public:
        explicit GameManager(QQuickPaintedItem *parent);

        Q_INVOKABLE void loadSettings();

        Q_INVOKABLE void exportSettings();

        uint32_t _rowCount{}, _columnCount{};
        double _screenHeight{}, _screenWidth{}, _uiScale{}, _fieldHeight{}, _fieldWidth{}, _minoEdgeLength{};

        QHash<Types::Mino, QImage> _minoAssets{};

    private:
        void _generateMinoQueue();

        double _frameHeight{}, _frameWidth{}, _frameThickness{};
        std::unique_ptr<Models::Field> _field;
        QVector<Models::Mino> _minoQueue;
        std::unique_ptr<Models::Mino> _currentMino;

    public slots:
        Q_INVOKABLE void onGameStart(GameManager *_gameManager);
    };
}
