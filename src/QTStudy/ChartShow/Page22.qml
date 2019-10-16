import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    color: "pink"

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
        onTouchUpdated: {
            console.log(point1.y - point1.startY)
        }
    }
}
