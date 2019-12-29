import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    title: qsTr("Home")
    Column {
        id: column
        spacing: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        TextField {
            id: textField
            text: qsTr("Text Field")
        }
        Button {
            text: "Send From C2"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                bcode.send(text + ":" + textField.text)
                textField.text = ""
            }
        }
        Label {
            id: lblMsg
            text: "Receive"
        }
    }

    Connections {
        target: bcode
        onReceiveMsg: {
            lblMsg.text = msg
        }
    }
}

/*##^##
Designer {
    D{i:0;height:400;width:600}
}
##^##*/

