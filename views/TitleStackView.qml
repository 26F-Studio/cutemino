import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Page {
    Button {
        anchors.centerIn: parent
        text: "Start Game"
        onClicked: {
            mainStackView.push("/views/SoloGameStackView.qml")
//            mainGameManager.exportSettings()
        }
    }
}
