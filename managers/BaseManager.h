//
// Created by particleg on 2022/11/24.
//

#pragma once

#include <QObject>
#include <QQmlEngine>

namespace CuteMino::Managers {
    template<class Implementation>
    class BaseManager : public QObject {
    public:
        explicit BaseManager(QObject *parent = nullptr) : QObject(parent) {}

        static void registerTypes(const char *uri, const char *name) {
            qmlRegisterSingletonType<Implementation>(uri, 1, 0, name, singletonProvider);
        }

        static QObject *singletonProvider(QQmlEngine *, QJSEngine *) {
            if (!s_instance) {
                s_instance = new Implementation(reinterpret_cast<QObject *>(qmlEngine));
            }
            return s_instance;
        }

    private:
        static Implementation *s_instance = nullptr;
    };
}
