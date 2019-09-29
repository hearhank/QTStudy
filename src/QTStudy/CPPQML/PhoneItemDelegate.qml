import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Proton.Datas 1.0

ItemDelegate {
    id: phoneDelegate
    signal itemClicked(var index)
    signal switchChanged(var ele)
    signal itemButtonClicked(var ele)
    property bool isItemReadOnly: false
    Item {
        anchors.fill: parent
        RowLayout {
            width: parent.width
            height: parent.height

            //标题
            Label {
                id: lblTitle
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: model.name
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

                //                Button {
                //                    visible: model.elementType == CH.Button
                //                    text: model.valueM
                //                    onClicked: itemButtonClicked(model)
                //                    Layout.minimumWidth: 150
                //                }
                Label {
                    //                    visible: !(type == 1 || type == 6)
                    //                    text: model.preValue !== undefined ? (model.preValue
                    //                                                          + model.valueM) : model.valueM
                    //                    visible: type === 0
                    height: parent.height
                    font.pixelSize: 16
                    text: model.value
                    enabled: false
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    //                    color: parent.getColor()
                    //                    echoMode: type == 5 ? TextInput.Password : TextInput.Normal
                }

                //                Label {
                //                    //                    visible: model.elementType !== CH.SWitchButton
                //                    text: model.unit
                //                    font.pixelSize: 16
                //                    height: parent.height
                //                    verticalAlignment: Text.AlignVCenter
                //                    //                    color: (model.isDisabled !== undefined
                //                    //                            && isDisabled) ? "#ccc" : "black"
                //                }
                RowLayout {
                    visible: model.getEletype == 1
                    //enabled: !isItemReadOnly
                    width: 120
                    height: parent.height
                    SwitchDelegate {
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

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log(index)
                itemClicked(index)
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;height:45;width:500}
}
##^##*/

