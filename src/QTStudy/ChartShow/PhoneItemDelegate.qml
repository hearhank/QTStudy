import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Proton.Datas 1.0

ItemDelegate {
    id: phoneDelegate
    signal itemClicked(var childIndex)
    signal editClicked(int t,var ele)
    property bool isItemReadOnly: false
    Item {
        anchors.fill: parent
        enabled: !model.disabled
        MouseArea {
            anchors.fill: parent
            onClicked: {
                itemClicked(index)
            }
        }

        Grid {
            id: grid
            anchors.fill: parent
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
                width: parent.width - lblTitle.width
                height: parent.height
                Layout.margins: 0
//                RowLayout {
//                    anchors.right: editFlag.left
//                    visible: model.control === DataNode.Button
//                    implicitWidth: btn.width + 2
//                    height: parent.height
//                    Button {
//                        id: btn
//                        text: model.value
//                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
//                        onClicked: {
//                            editClicked(1,model)
//                            itemClicked(index)
//                        }
//                        Layout.minimumWidth: 100
//                        Layout.margins: 0
//                    }
//                    Label {
//                        width: 2
//                    }
//                }
                RowLayout {
                    //anchors.right: editFlag.left
                    implicitWidth: lblValue.width + lblUnit.width + 2
                    height: parent.height

                    Label {
                        id: lblValue
                        height: parent.height
                        font.pixelSize: 16
                        text: model.value
                        verticalAlignment: Text.AlignRight
                        Layout.alignment: Qt.AlignVCenter
                    }
                    Label {
                        id: lblUnit
                        //visible: model.control !== DataNode.SWitchButton
                        text: model.unit
                        font.pixelSize: 16
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        Layout.minimumWidth: 20
                    }
                    Label {
                        width: 2
                    }
                }
//                RowLayout {
//                    //enabled: !isItemReadOnly
//                    anchors.right: editFlag.left
//                    implicitWidth: switchButton.width + 2
//                    height: parent.height
//                    SwitchDelegate {
//                        id: switchButton
//                        height: parent.height
//                        Layout.fillHeight: true
//                        padding: 0
//                        visible: model.control === DataNode.SWitchButton
//                        checked: Number(model.value) === 1
//                        onClicked: {
//                            model.value = checked ? 1 : 0
//                            editClicked(2,model)
//                            itemClicked(index)
//                        }
//                        //visible: !(model.isDisabled !== undefined && isDisabled)
//                    }
//                    Label {
//                        width: 2
//                    }
//                }
//                Item{
//                    id: editFlag
//                    anchors.right: parent.right
//                    anchors.rightMargin: 5
//                    width: 40
//                    height: parent.height
//                    visible: (model.control === DataNode.TextBox
//                              || model.control === DataNode.ComboBox)
//                    Image {
//                        width: 20
//                        height: 20
//                        anchors.verticalCenter: parent.verticalCenter
//                        anchors.horizontalCenter: parent.horizontalCenter
//                        sourceSize.width: 20
//                        sourceSize.height: 20
//                        source: "qrc:/images/rightgo.png"
//                    }
//                    MouseArea{
//                        anchors.fill: parent
//                        onClicked: {
//                            editClicked(0,model)
//                            itemClicked(index)
//                        }
//                    }
//                }


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

