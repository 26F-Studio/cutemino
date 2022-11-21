import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
//import CuteMino.Controllers

Page {
    Rectangle {
        id:_background
        anchors.fill:parent
        color: "dimgrey"
    }

//    GameManager {
//        id: main_gameManager
//        anchors.fill: parent
//    }

    Component.onCompleted: {
//        main_gameManager
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