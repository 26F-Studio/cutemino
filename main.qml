import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

ApplicationWindow {
    id: main_applicationWindow
    visible: true
    width: (Qt.platform.os === "windows" || Qt.platform.os === "linux" || Qt.platform.os === "osx") ? 1280 : 720
    height: (Qt.platform.os === "windows" || Qt.platform.os === "linux" || Qt.platform.os === "osx") ? 720 : 1280
    title: qsTr("Cute Mino")
    flags: Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint

    StackView {
        id: main_stackView
        initialItem: "views/TitleStackView.qml"
        anchors.fill: parent
    }

    Component.onCompleted: {
        main_gameManager.loadSettings()
    }
}
