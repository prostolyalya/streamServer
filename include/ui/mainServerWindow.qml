import QtQuick 2.0
import QtQuick.Controls 1.0
ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Server")

    Text {
        id: mainText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 150
        anchors.topMargin: 30
        text: qsTr("Server")
    }
    TextArea
    {
        anchors.top: mainText.bottom
        anchors.left: mainText.left
        id: mainTextArea
        width: 300
        height: 200
        text: uiController.uiTextServer
    }
}
