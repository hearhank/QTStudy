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

        RowLayout {
            width: parent.width
            height: parent.height

            //标题
            Label {
                id: lblTitle
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: name
                font.pixelSize: 16
                font.bold: true
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                //                color: (model.isDisabled !== undefined
                //                        && isDisabled) ? "#ccc" : "black"
            }

            RowLayout {
                //                function getColor() {
                //                    if (model.fColor !== undefined) {
                //                        return model.fColor
                //                    } else {
                //                        return (model.isDisabled !== undefined
                //                                && isDisabled) ? "#ccc" : "#0070c9"
                //                    }
                //                }
                height: parent.height
                anchors.right: parent.right
                anchors.rightMargin: 10

                Button {
                    visible: model.pControlType === DataNode.Button
                    text: model.value
                    onClicked: itemButtonClicked(model)
                    Layout.minimumWidth: 150
                }
                RowLayout {
                    anchors.right: parent.right
                    visible: model.pControlType === DataNode.Label
                    implicitWidth: lblValue.width + lblUnit.width + 10
                    height: parent.height
                    Label {

                        //                    visible: !(type == 1 || type == 6)
                        //                    text: model.preValue !== undefined ? (model.preValue
                        //                                                          + model.valueM) : model.valueM
                        id: lblValue
                        height: parent.height
                        font.pixelSize: 16
                        text: model.value
                        enabled: false
                        verticalAlignment: Text.AlignRight
                        anchors.verticalCenter: parent.verticalCenter
                        //                    color: parent.getColor()
                        //                    echoMode: type == 5 ? TextInput.Password : TextInput.Normal
                    }
                    Label {
                        visible: model.elementType !== CH.SWitchButton
                        id: lblUnit
                        text: unit
                        font.pixelSize: 16
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        //                    color: (model.isDisabled !== undefined
                        //                            && isDisabled) ? "#ccc" : "black"
                    }
                }
                RowLayout {
                    //enabled: !isItemReadOnly
                    implicitWidth: switchButton.width + 10
                    height: parent.height
                    SwitchDelegate {
                        id: switchButton
                        visible: model.pControlType === DataNode.SWitchButton
                        checked: Number(model.value) === 1
                        onClicked: {
                            model.value = checked ? "1" : "0"
                            switchChanged(model)
                        }
                        //visible: !(model.isDisabled !== undefined && isDisabled)
                    }
                }

                //                Image {
                //                    anchors.right: parent.right
                //                    //                    visible: !(model.type === 1 || model.type === 4
                //                    //                               || model.type === 6) && !isItemReadOnly
                //                    width: 40
                //                    height: 40
                //                    sourceSize.width: 40
                //                    sourceSize.height: 40
                //                    source: "qrc:/images/rightgo.png"
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

