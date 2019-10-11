import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Page {
    id: root
    property var node: null

    header: ToolBar {
        id: headMenu
        RowLayout {
            spacing: 0
            anchors.fill: parent

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/back.png"
                }
                onClicked: root.StackView.view.pop()
            }

            Label {
                id: titleLabel
                text: node.name.replace(":", "")
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            Label {
            }
        }
    }

    Pane {
        rightPadding: 0
        leftPadding: 0
        padding: 10
        anchors.fill: parent
        ListView {
            id: wrapper
            anchors.fill: parent
            model: node.children
            delegate: phoneDelegate
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

    Component {
        id: phoneDelegate
        Item {
            width: parent.width
            height: 50
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log(index)
                    wrapper.currentIndex = index
//                    console.log(model.isDisabled)
//                    if (model.isDisabled !== undefined && model.isDisabled)
//                        return
                    node.value=Number(index)
//                    var value = datas.get(wrapper.currentIndex).value
//                    if (!value) {
//                        value = wrapper.currentIndex
//                    }
//                    item.valueM = datas.get(wrapper.currentIndex).name
//                    item.value = value
//                    containqml.write(root.item.offset, value)
                    //root.StackView.view.pop()
                }
            }

            Item {
                width: parent.width
                height: parent.height
                Image {
                    anchors.leftMargin: 10
                    y: 13
                    anchors.left: parent.left
                    width: 24
                    height: 24
                    visible: wrapper.currentIndex == index
                    sourceSize.width: 24
                    sourceSize.height: 24
                    source: "qrc:/images/ok.png"
                }

                Text {
                    text: name
                    font.pixelSize: 20
                    font.bold: true
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    color: (model.isDisabled !== undefined
                            && model.isDisabled) ? "#ccc" : "black"
                }
            }

            Rectangle {
                color: "#ccc"
                height: 1
                width: parent.width
                anchors.bottom: parent.bottom
            }
        }
    }

    Component.onCompleted: {
          wrapper.currentIndex=node.value
    }
}
