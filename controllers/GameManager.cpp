#include <algorithm>
//#include <magic_enum.hpp>
#include <random>

#include <QPainter>
#include <QSettings>

#include <controllers/GameManager.h>

using namespace CuteMino::Controllers;
using namespace CuteMino::Types;
using namespace std;

GameManager::GameManager(QQuickPaintedItem *parent) : QQuickPaintedItem(parent) {
    qDebug() << "Initializing GameManager...";

    QSettings qSettings;
    _frameThickness = qSettings.value("QtMino_FrameThickness", 10).toUInt();

    qDebug() << "GameManager Initialized.";
}

void GameManager::loadSettings() {
    qDebug() << "Loading settings...";

    QSettings qSettings;

    _rowCount = qSettings.value("QtMino_FieldHeight", 20).toUInt();
    _columnCount = qSettings.value("QtMino_FieldWidth", 10).toUInt();
    _uiScale = qSettings.value("QtMino_uiScale", 0.8).toDouble();
    _frameThickness = qSettings.value("QtMino_FrameThickness", 10.0).toDouble();

    const auto boxHeight = height();
    const auto boxWidth = width();

    if (boxHeight * _columnCount >= boxWidth * _rowCount) {
        _fieldWidth = boxWidth * _uiScale - _frameThickness * 2.0;
        _fieldHeight = _fieldWidth * static_cast<double>(_rowCount) / static_cast<double>(_columnCount);
        _frameWidth = _fieldWidth + _frameThickness;
        _frameHeight = _fieldHeight + _frameThickness;
        _minoEdgeLength = _fieldWidth / static_cast<double>(_columnCount);
    } else {
        _fieldHeight = boxHeight * _uiScale - _frameThickness * 2.0;
        _fieldWidth = _fieldHeight * static_cast<double>(_columnCount) / static_cast<double>(_rowCount);
        _frameHeight = _fieldHeight + _frameThickness;
        _frameWidth = _fieldWidth + _frameThickness;
        _minoEdgeLength = _fieldHeight / static_cast<double>(_rowCount);
    }

    _minoAssets[Mino::I].load(":/assets/skins/normal/skyblue.png");
    _minoAssets[Mino::J].load(":/assets/skins/normal/blue.png");
    _minoAssets[Mino::L].load(":/assets/skins/normal/orange.png");
    _minoAssets[Mino::O].load(":/assets/skins/normal/yellow.png");
    _minoAssets[Mino::S].load(":/assets/skins/normal/green.png");
    _minoAssets[Mino::T].load(":/assets/skins/normal/pink.png");
    _minoAssets[Mino::Z].load(":/assets/skins/normal/red.png");

    qDebug() << "settings loaded.";
}

void GameManager::exportSettings() {
    qDebug() << "Exporting settings...";

    QSettings qSettings;

    qSettings.setValue("QtMino_FieldHeight", _rowCount);
    qSettings.setValue("QtMino_FieldWidth", _columnCount);
    qSettings.setValue("QtMino_uiScale", _uiScale);
    qSettings.setValue("QtMino_FrameThickness", _frameThickness);

    qDebug() << "settings exported.";
}

void GameManager::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing, true);
    _paintFrame(painter);
    _paintField(painter);
    _paintMino(painter);
    _paintNexts(painter);
}

void GameManager::keyPressEvent(QKeyEvent *event) {
    QQuickPaintedItem::keyPressEvent(event);
}

void GameManager::keyReleaseEvent(QKeyEvent *event) {
    QQuickPaintedItem::keyReleaseEvent(event);
}

void GameManager::_generateMinoQueue() {
    qDebug() << "Generating mino queue...";

    _minoQueue.clear();
    for (int i = 0; i < 7; i++) {
        _minoQueue.enqueue(Models::Mino{static_cast<Mino>(i), QPoint(0, 0)});
    }
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(_minoQueue.begin(), _minoQueue.end(), g);
    qDebug() << "Mino queue generated.";
}

void GameManager::onGameStart(GameManager *_gameManager) {
    qDebug() << "GameManager received settings signal.";
    _currentMino = make_unique<Models::Mino>(_minoQueue.dequeue());
    _field = make_unique<Models::Field>(_rowCount, _columnCount);
}

void GameManager::_paintFrame(QPainter *painter) {
    const auto boxHeight = height();
    const auto boxWidth = width();
    QPointF topLeft(boxWidth / 2.0 - _frameWidth / 2.0, boxHeight / 2.0 - _frameHeight / 2.0);
    QPointF topRight(boxWidth / 2.0 + _frameWidth / 2.0, boxHeight / 2.0 - _frameHeight / 2.0);
    QPointF bottomLeft(boxWidth / 2.0 - _frameWidth / 2.0, boxHeight / 2.0 + _frameHeight / 2.0);
    QPointF bottomRight(boxWidth / 2.0 + _frameWidth / 2.0, boxHeight / 2.0 + _frameHeight / 2.0);
    painter->save();
    painter->setPen(QPen(QColor("gray"), 1));
    for (int row = 1; row < _rowCount; ++row) {
        QPointF tempLeft(topLeft.x() + _frameThickness / 2.0, topLeft.y() + _frameThickness / 2.0 + row * _minoEdgeLength);
        QPointF tempRight(topRight.x() + _frameThickness / 2.0, topRight.y() + _frameThickness / 2.0 + row * _minoEdgeLength);
        painter->drawLine(tempLeft, tempRight);
    }

    for (int column = 1; column < _columnCount; ++column) {
        QPointF tempTop(topLeft.x() + _frameThickness / 2.0 + column * _minoEdgeLength, topLeft.y() + _frameThickness / 2.0);
        QPointF tempBottom(bottomLeft.x() + _frameThickness / 2.0 + column * _minoEdgeLength, bottomLeft.y() + _frameThickness / 2.0);
        painter->drawLine(tempTop, tempBottom);
    }

    painter->setPen(QPen(QColor("white"), 10, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter->setBrush(QColor("transparent"));
    painter->drawRect(QRectF(topLeft, bottomRight));
    painter->restore();
}

void GameManager::_paintField(QPainter *painter) {

}

void GameManager::_paintMino(QPainter *painter) {

}

void GameManager::_paintNexts(QPainter *painter) {

}

