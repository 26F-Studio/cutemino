#include <algorithm>
#include <random>

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

    _screenHeight = height();
    _screenWidth = width();

    if (_screenHeight * _columnCount >= _screenWidth * _rowCount) {
        _fieldWidth = _screenWidth * _uiScale - _frameThickness * 2.0;
        _fieldHeight = _fieldWidth * static_cast<double>(_rowCount) / static_cast<double>(_columnCount);
        _frameWidth = _fieldWidth + _frameThickness;
        _frameHeight = _fieldHeight + _frameThickness;
        _minoEdgeLength = _fieldWidth / static_cast<double>(_columnCount);
    } else {
        _fieldHeight = _screenHeight * _uiScale - _frameThickness * 2.0;
        _fieldWidth = _fieldHeight * static_cast<double>(_columnCount) / static_cast<double>(_rowCount);
        _frameHeight = _fieldHeight + _frameThickness;
        _frameWidth = _fieldWidth + _frameThickness;
        _minoEdgeLength = _fieldHeight / static_cast<double>(_rowCount);
    }

    _minoAssets[Mino::I].load(":/skins/normal/skyblue.png");
    _minoAssets[Mino::J].load(":/skins/normal/blue.png");
    _minoAssets[Mino::L].load(":/skins/normal/orange.png");
    _minoAssets[Mino::O].load(":/skins/normal/yellow.png");
    _minoAssets[Mino::S].load(":/skins/normal/green.png");
    _minoAssets[Mino::T].load(":/skins/normal/pink.png");
    _minoAssets[Mino::Z].load(":/skins/normal/red.png");

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

void GameManager::_generateMinoQueue() {
    qDebug() << "Generating mino queue...";

    _minoQueue.clear();
    for (int i = 0; i < 7; i++) {
        _minoQueue.append(Models::Mino{static_cast<Mino>(i), QPoint(0, 0)});
    }
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(_minoQueue.begin(), _minoQueue.end(), g);
    qDebug() << "Mino queue generated.";
}

void GameManager::onGameStart(GameManager *_gameManager) {
    qDebug() << "GameManager received settings signal.";
    _currentMino = std::make_unique<Models::Mino>(_gameManager);
}