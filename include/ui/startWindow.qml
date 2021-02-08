import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

ApplicationWindow
{
    function checkLogin()
    {
        if ( textLogin.text.length < 5 || textLogin.text.length > 20)
            return false
        return true;
    }

    function checkPassword()
    {
        if (textPass.text.length < 6 || textPass.text.length > 32)
            return false;
        return true;
    }
    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }
    id: logPassWindow
    width: 200
    height: 200
    visible: true
    background: Rectangle {
        color: "gray"
    }

    Text
    {
        anchors.left: textLogin.left
        anchors.leftMargin: -10
        anchors.top: parent.top
        font.family: "Helvetica"
        font.pointSize: 18
        color: "yellow"
        text: qsTr("Server")
    }
    Text
    {
        id: textLoginLabel
        anchors.right: textLogin.left
        anchors.rightMargin: 10
        anchors.top: textLogin.top
        anchors.topMargin: 5
        font.family: "Helvetica"
        font.pointSize: 10
        color: "white"
        text: qsTr("Username:")
    }
    TextField
    {
        id: textLogin
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 80
        anchors.topMargin: 40
        width: 100
        height: 35
        validator: RegularExpressionValidator { regularExpression: /^[a-z0-9]+$/i }
    }
    Text
    {
        anchors.left: textLoginLabel.left
        anchors.top: textPass.top
        font.family: "Helvetica"
        font.pointSize: 10
        color: "white"
        text: qsTr("Password:")
    }
    TextField
    {
        id: textPass
        echoMode:TextInput.Password
        //             textColor: "black"
        anchors.left: textLogin.left
        anchors.top: textLogin.bottom
        anchors.topMargin: 30
        width: 100
        height: 35
        validator: RegularExpressionValidator { regularExpression: /^[a-z0-9]+$/i }
    }

    Rectangle
    {
        border.color: "yellow"
        border.width: 1
        anchors.top: textPass.bottom
        anchors.left: textPass.left
        anchors.topMargin: 30
        color: "gray"
        width: 55
        height: 22
        Text
        {
            anchors.centerIn: parent
            color: "white"
            text: qsTr("Sign in")
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                if (!checkLogin() || !checkPassword())
                {
                    popup.open()
                }
                else
                {
                    uiController.init(textLogin.text , textPass.text)
                    logPassWindow.close()
                }

            }
        }
    }
    Rectangle
    {
        width: 20
        height: 20
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 5
        anchors.bottomMargin: 5
        border.color: "white"
        border.width: 1
        color: "gray"
        Text {
            anchors.centerIn: parent
            color: "yellow"
            font.bold: true
            text: qsTr("<")
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                textLogin.text = ""
                textPass.text = ""
                logPassWindow.close()
                startWindow.show()
            }
        }
    }
    Popup
    {
        id: popup
        width: 150
        height: 100
        clip: true

        contentItem: Text {
            wrapMode: Text.WordWrap
            text: "Username lenght > 5 and < 20. Password lenght > 6 and < 32"
        }
        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutside
    }
}



