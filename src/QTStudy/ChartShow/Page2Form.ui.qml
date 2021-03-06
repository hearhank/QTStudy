import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 600
    height: 400

    title: qsTr("Page 2")

    Label {
        text: qsTr("You are on Page 2.")
        anchors.centerIn: parent
    }

    MultiPointTouchArea {
        anchors.fill: parent
        mouseEnabled: true
        minimumTouchPoints: 1
        maximumTouchPoints: 2
        touchPoints: [
            TouchPoint {
                id: point1
            },
            TouchPoint {
                id: point2
            }
        ]
        Rectangle {
            width: 30
            height: 30
            color: "green"
            x: point1.x
            y: point1.y
        }

        Rectangle {
            width: 30
            height: 30
            color: "yellow"
            x: point2.x
            y: point2.y
        }
        onTouchUpdated: console.log(point1.y - point1.startY)
    }
}
