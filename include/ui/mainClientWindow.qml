import QtQuick 2.0
import QtQuick.Controls 1.0

ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Client")

    Text {
        id: mainText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 150
        anchors.topMargin: 30
        text: qsTr("Client")
    }
    TextArea
    {
        anchors.top: mainText.bottom
        anchors.left: mainText.left
        id: mainTextArea
        width: 300
        height: 200
        text: uiController.uiText
    }

    TextArea
    {
        anchors.top: mainTextArea.bottom
        anchors.left: mainTextArea.left
        anchors.topMargin: 20
        id: mainInput
        width: 300
        height: 200
    }
    Rectangle
    {
       anchors.top: mainInput.top
       anchors.left: mainInput.right
       width: 50
       height: 20
       Text {
           anchors.fill: parent
           text: qsTr("Send")
       }
       anchors.rightMargin: 10
       MouseArea
       {
            anchors.fill: parent
            onClicked:
            {
                uiController.sendText(mainInput.text)
                mainInput.text = ""
            }

       }
    }

}
