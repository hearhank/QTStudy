import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Proton.Datas 1.0

Page {
    DataItems {
        id: binding_datas
        datas: [
            DataItem {
                name: "Count"
                value: 10
                store: true
            },
            DataItem {
                name: "On/Off"
                value: 1
                eletype: DataItem.SWitchButton
                desc: DataDesc {
                    offset: 0
                    dataType: DataDesc.UShort
                }
            },
            DataItem {
                name: "Last Name"
                value: "Hank"
                desc: DataDesc {
                    offset: 1
                    dataType: DataDesc.Int
                }
            },
            DataItem {
                name: "Full Name"
                refNames: ["On/Off", "Last Name"]
                value: ""
                enabled: true
                convertType: CH.NameC
                onValueChanged: {

                    //                    var v = binding_datas.getStore("Count")
                    //                    console.log(v.name)
                    //                    console.log(v.value)
                    //                    console.log(val)
                    //                    console.log(vals)
                }
            }
        ]
    }

    ListView {
        id: wrapper
        anchors.fill: parent
        model: binding_datas.datas
        delegate: PhoneItemDelegate {
            width: parent.width
            height: 50
            onItemClicked: {

            }
            onSwitchChanged: {

            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    wrapper.currentIndex = index
                }
            }
        }
        highlight: Rectangle {
            color: "lightsteelblue"
        }
        focus: true
        clip: true
        highlightFollowsCurrentItem: true
        highlightMoveDuration: 0
        highlightResizeDuration: 0
    }

    PageOperationTimer {
        id: operator
        interval: 10
    }

    Component.onCompleted: {
        operator.start(binding_datas)
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

