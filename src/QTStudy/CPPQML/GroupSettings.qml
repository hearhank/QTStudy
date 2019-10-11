import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ItemDelegate {
    id: delegate
    padding: 0
    property int itemHeight: 50
    checked: selected
    checkable: true

    signal titleClicked(int group)
    signal doEditClicked(int t,var ele)
    onCheckedChanged: {
        delegate.state = checked ? "expanded" : "normal"
    }
    //visible: (model.isDisabled === undefined || !model.isDisabled)
    height: {
        if (!visible)
            return 0
    }
    property var nodes: model.children
    contentItem: ColumnLayout {
        spacing: 0
        Rectangle {
            Layout.fillWidth: true
            implicitHeight: itemHeight - line1.height
            Rectangle {
                id: backgorund
                color: checked ? "gray" : "#ccc"
                anchors.fill: parent
            }
            ToolButton {
                anchors.fill: parent
                id: headerButton
                padding: 0
                Label {
                    font.bold: true
                    font.pixelSize: 20
                    text: model.name
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: checked ? "white" : (model.isDisabled === true ? "silver" : "black")
                }
                onClicked: {
                    titleClicked(index)
                }
            }
        }
        Rectangle {
            id: line1
            color: "gray"
            visible: !checked
            height: 1
            width: parent.width
            Layout.fillWidth: true
        }
        ListView {
            id: listView
            Layout.fillWidth: true
            visible: true
            model: nodes
            height: nodes.length * itemHeight
            delegate: PhoneItemDelegate {
                width: parent.width
                height: itemHeight
                isItemReadOnly: false
                onItemClicked: {
                    listView.currentIndex = childIndex
                }
                onEditClicked: {
                    doEditClicked(t,ele)
                }
            }
            focus: true
            clip: true //去多余！
            highlight: Rectangle {
                color: "lightsteelblue"
            }
            highlightFollowsCurrentItem: true
            highlightMoveDuration: 0
            highlightResizeDuration: 0
        }
    }
    states: [
        State {
            name: "normal"
            when: !delegate.checked
            PropertyChanges {
                target: listView
                visible: false
            }
        },
        State {
            name: "expanded"
            when: delegate.checked

            PropertyChanges {
                target: listView
                visible: true
            }

            PropertyChanges {
                target: headerButton
                highlighted: false
            }
        }
    ]
}
