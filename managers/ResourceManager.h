//
// Created by particleg on 2022/11/24.
//

#pragma once

#include <QImage>

#include <managers/BaseManager.h>
#include <types/Mino.h>

namespace CuteMino::Managers {
    class ResourceManager : public BaseManager<ResourceManager> {
    public:
        explicit ResourceManager(QObject *parent = nullptr);

        static void registerTypes(const char *uri, const char *name);

        static QObject *singletonProvider(QQmlEngine *, QJSEngine *);

    private:
        QHash<Types::Mino, QImage> _minoAssets{};

    public slots:
        Q_INVOKABLE void loadResources();
    };
}
