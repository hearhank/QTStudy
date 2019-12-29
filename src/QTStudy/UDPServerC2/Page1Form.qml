import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 600
    height: 400

    title: qsTr("Page 1")

    Label {
        text: qsTr("You are on Page 1.")
        anchors.centerIn: parent
    }

    Button {
        id: button
        x: 250
        y: 212
        text: qsTr("Send From C2")
        onClicked: {
            bcode.send("C2 Send")
        }
    }
}
