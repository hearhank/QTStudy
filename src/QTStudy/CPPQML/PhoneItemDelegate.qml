import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Proton.Datas 1.0

ItemDelegate {
    id: phoneDelegate
    signal itemClicked(var childIndex)
    signal switchChanged(var ele)
    signal itemButtonClicked(var ele)
    property bool isItemReadOnly: false
    Item {
        anchors.fill: parent
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log(index)
                itemClicked(index)
            }
        }

        Grid {
            id: grid
            anchors.fill:parent
            columns: 2
            rows: 1
            spacing: 0
            //标题
            Label {
                id: lblTitle
                text: name
                leftPadding: 10
                font.pixelSize: 16
                font.bold: true
                height: parent.height
                verticalAlignment: Text.AlignVCenter
            }

            Item {
                id: element
                width: parent.width-lblTitle.width
                height: parent.height
                Layout.margins: 0
                RowLayout {
                    anchors.right: editFlag.left
                    visible: model.pControlType === DataNode.Button
                    implicitWidth: btn.width+10
                    height: parent.height
                    Button {
                        id:btn
                        text: model.value
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        onClicked: itemButtonClicked(model)
                        Layout.minimumWidth: 100
                        Layout.margins: 0
                    }
                    Label{
                        width: 10
                    }
                }
                RowLayout {
                    anchors.right: editFlag.left
                    visible: (model.pControlType === DataNode.Label||model.pControlType === DataNode.ComboBox)
                    implicitWidth: lblValue.width + lblUnit.width + 10
                    height: parent.height

                    Label {
                        id: lblValue
                        height: parent.height
                        font.pixelSize: 16
                        text: model.fValue
                        verticalAlignment: Text.AlignRight
                        Layout.alignment: Qt.AlignVCenter
                    }
                    Label {
                        id: lblUnit
                        visible: model.pControlType !== DataNode.SWitchButton
                        text: model.unit
                        font.pixelSize: 16
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        Layout.minimumWidth: 20
                    }
                    Label{
                        width: 10
                    }
                }
                RowLayout {
                    //enabled: !isItemReadOnly
                    anchors.right: editFlag.left
                    implicitWidth: switchButton.width + 10
                    height: parent.height
                    SwitchDelegate {
                        id: switchButton
                        visible: model.pControlType === DataNode.SWitchButton
                        checked: Number(model.value) === 1
                        height: parent.height
                        onClicked: {
                            model.value = checked ? 1 : 0
                            console.log(model.value)
                            switchChanged(model)
                        }
                        //visible: !(model.isDisabled !== undefined && isDisabled)
                    }
                    Label{
                        width:  10
                    }
                }
                Image {
                    id:editFlag
                    anchors.right: parent.right
                    //                    visible: !(model.type === 1 || model.type === 4
                    //                               || model.type === 6) && !isItemReadOnly
                    width: 35
                    height: 35
                    anchors.verticalCenter: parent.verticalCenter
                    sourceSize.width: 35
                    sourceSize.height: 35
                    source: "qrc:/images/rightgo.png"
                }
            }
        }

        //顶线
        Rectangle {
            visible: index > 0
            color: "#ccc"
            height: 1
            width: parent.width
            anchors.top: parent.top
        }
    }
}

/*##^##
Designer {
    D{i:0;height:45;width:500}
}
##^##*/
















































































































/*##^## Designer {
    D{i:0;width:400}
}
 ##^##*/
