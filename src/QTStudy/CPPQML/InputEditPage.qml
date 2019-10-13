import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Page {
    id:root
    property var node:null;
//    Component.onCompleted: {
//        titleLabel.text=node.name.replace(":","")
//        txtNumber.text=node.fValue
//        lblUnit.text=node.unit
//        console.log(node)
//    }

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
                text:node.name.replace(":", "")
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                id: btnSave
                contentItem: Label {
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter
                    text: "Save"
                    font.pixelSize: 20
                    color: "#0070c9"
                }
                onClicked: {
                    console.log(node.value)
                    node.value=Number(txtNumber.text)
                    root.StackView.view.pop()
                }
            } //end button
        }
    } //end header

    Pane {
        anchors.fill: parent
        padding: 10
        Text {
            id: lblInfo
            text: "" // {item.desc.replace("$$$$$",(65535*Math.pow(10,-factor)).toFixed(factor))}
            color: "gray"
            width: parent.width
            wrapMode: Text.Wrap
        }

        RowLayout {
            id: contentRow
            anchors.top: lblInfo.bottom
            width: parent.width
            height: 40
            Rectangle {
                property color borderColor: "#ccc"
                id: rectInput
                Layout.fillWidth: true
                height: 35
                radius: 5
                //smooth: true
                border.color: borderColor
                border.width: 1
                TextInput {
                    id: txtNumber
                    focus: true
                    anchors.fill: parent
                    anchors.margins: 5
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    //font.family: "MS UI Gothic"
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    text: node.fvalue
                    anchors.rightMargin: 10
                    onTextChanged: {
                        if (lblShow.text != "") {
                            lblShow.text = ""
                            rectInput.borderColor = "#ccc"
                        }
                    }
                    Keys.onEnterPressed: {
                    }
                    Keys.onReturnPressed: {
                    }
                }
            }

            Label {
                id:lblUnit
                text:node.unit
                font.pixelSize: 20
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                Layout.alignment: Qt.AlignCenter
            }
        }

        Label {
            id: lblShow
            Layout.alignment: Qt.AlignTop
            width: parent.width
            wrapMode: Text.WordWrap
            text: ""
            color: "red"
            font.bold: true
            Behavior on color {
                ColorAnimation {
                    from: "white"
                    to: "red"
                    duration: 1000
                }
            }
        }
    }
}


















/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:12;anchors_width:76}
}
 ##^##*/
