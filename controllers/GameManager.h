//
// Created by particleg on 2022/11/20.
//

#pragma once

#include <QBitArray>
#include <QImage>
#include <QQueue>
#include <QQuickPaintedItem>

#include <models/Field.h>
#include <models/Mino.h>

namespace CuteMino::Controllers {
    class GameManager : public QQuickPaintedItem {
    Q_OBJECT
    public:
        explicit GameManager(QQuickPaintedItem *parent = nullptr);

        Q_INVOKABLE void loadSettings();

        Q_INVOKABLE void exportSettings();

        void paint(QPainter *painter) override;

        uint32_t _rowCount{}, _columnCount{}, _nextCount{};
        double _uiScale{}, _fieldHeight{}, _fieldWidth{}, _minoEdgeLength{};

        QHash<Types::Mino, QImage> _minoAssets{};

    protected:
        void keyPressEvent(QKeyEvent *event) override;

        void keyReleaseEvent(QKeyEvent *event) override;

    private:
        void _generateMinoQueue();

        void _paintFrame(QPainter *painter);

        void _paintField(QPainter *painter);

        void _paintMino(QPainter *painter);

        void _paintNexts(QPainter *painter);

        double _frameHeight{}, _frameWidth{}, _frameThickness{};
        std::unique_ptr<Models::Field> _field;
        std::unique_ptr<Models::Mino> _currentMino;
        QQueue<Models::Mino> _minoQueue;

    public slots:
        Q_INVOKABLE void onGameStart();
    };
}
