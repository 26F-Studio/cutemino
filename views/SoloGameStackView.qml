import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import CuteMino.Controllers

Page {
    Rectangle {
        id:_background
        anchors.fill:parent
        color: "dimgrey"
    }

    GameController {
        id: main_gameController
        anchors.fill: parent
    }

    Button {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20
        text: qsTr("Get next mino")
        onClicked: {
            console.log("Pressed")
        }
    }

    Component.onCompleted: {
        main_gameController.loadSettings()
    }

    Keys.onPressed: (event) => {
        console.log(event.key);
        switch(event.key){
            case Qt.Key_W:
                break;
            case Qt.Key_D:
                break;
            case Qt.Key_S:
                break;
            case Qt.Key_A:
                break;
        }
    }
}
