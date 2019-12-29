import QtQuick 2.6
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

SwitchDelegate {
    id: control
    text: qsTr("ON")
    checked: false
    leftPadding: 0
    rightPadding: 0
    //    contentItem: Text {
    //        //rightPadding: control.indicator.width + control.spacing
    //        rightPadding: 0
    //        leftPadding: 0
    //        contentWidth: control.width
    //        contentHeight: control.height
    //        text: control.text
    //        horizontalAlignment: Text.AlignRight
    //        font: control.font
    //        opacity: enabled ? 1.0 : 0.3
    //        //color: control.down ? "#17a81a" : "#21be2b"
    //        color: "black"
    //        //elide: Text.ElideRight
    //        wrapMode: Text.Wrap
    //        verticalAlignment: Text.AlignVCenter
    //    }
    indicator: Rectangle {
        id: rectangle
        implicitWidth: 60
        implicitHeight: 26
        x: control.width - width - control.rightPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#17a81a" : "silver"
        border.color: control.checked ? "#17a81a" : "#cccccc"

        Text {
            id: name
            leftPadding: control.checked ? 10 : 32
            verticalAlignment: Text.AlignVCenter
            text: control.text
            anchors.verticalCenter: parent.verticalCenter
        }
        Rectangle {
            x: control.checked ? parent.width - width : 0
            width: 26
            height: 26
            radius: 13
            color: control.down ? "#cccccc" : "#ffffff"
            border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
        }
    }

    //    background: Rectangle {
    //        implicitWidth: 100
    //        implicitHeight: 40
    //        visible: control.down || control.highlighted
    //        color: control.down ? "#bdbebf" : "#eeeeee"
    //    }
}

/*##^##
Designer {
    D{i:0;width:60}
}
##^##*/

