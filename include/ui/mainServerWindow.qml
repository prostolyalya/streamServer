import QtQuick 2.0
import QtQuick.Controls 2.12

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
    Rectangle
    {
        id:mainTextArea
        anchors.top: mainText.bottom
        anchors.left: mainText.left
        width: 300
        height: 200
        border.color: "black"
        border.width: 1
        color: "#D9DDDC"
        Flickable
        {
            anchors.fill: parent
            flickableDirection: Flickable.VerticalFlick
            TextArea.flickable: TextArea
            {
                text: uiController.uiText
                color: "#311432"
                wrapMode: TextArea.Wrap

            }
            ScrollBar.vertical: ScrollBar { }
        }
    }

    Rectangle
    {
        id: recInputText
        anchors.top: mainTextArea.bottom
        anchors.left: mainTextArea.left
        anchors.topMargin: 20
        width: 300
        height: 200
        border.color: "black"
        border.width: 1
        color: "#D9DDDC"
        Flickable
        {
            anchors.fill: parent
            TextArea.flickable: TextArea
            {
                id: mainInput
                color: "#311432"
                wrapMode: TextArea.Wrap

            }
            ScrollBar.vertical: ScrollBar { }
        }
    }
    Rectangle
    {
       anchors.top: recInputText.top
       anchors.left: recInputText.right
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
                uiController.sendTextAllUsers(mainInput.text)
                mainInput.cursorPosition = 0
                mainInput.text = ""
            }
       }
    }
}
