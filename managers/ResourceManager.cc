//
// Created by particleg on 2022/11/24.
//

#include <managers/ResourceManager.h>

using namespace CuteMino::Managers;

static ResourceManager *s_instance = nullptr;

ResourceManager::ResourceManager(QObject *parent) : BaseManager(parent) {}

void ResourceManager::registerTypes(const char *uri, const char *name) {
    qmlRegisterSingletonType<ResourceManager>(
            uri,
            1,
            0,
            name,
            singletonProvider
    );
}

QObject *ResourceManager::singletonProvider(QQmlEngine *, QJSEngine *) {
    if (!s_instance) {
        s_instance = new ResourceManager(reinterpret_cast<QObject *>(qmlEngine));
    }
    return s_instance;
}

void ResourceManager::loadResources() {

}
