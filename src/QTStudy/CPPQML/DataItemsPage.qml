import QtQuick 2.0
import QtQuick.Controls 2.0
import Proton.Datas 1.0

Page {
    width: parent.width
    height: parent.height
    DataItems {
        id: binding_datas
        datas: [
            DataItem {
                name: "On/Off"
                value: "1"
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
            }
        ]
    }

    ListView {
        id: wrapper
        anchors.fill: parent
        model: binding_datas.datas
        delegate: PhoneItemDelegate {
            onItemClicked: {

            }
            onSwitchChanged: {

            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    wrapper.currentIndex = index
                    console.log(model)
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

    Component.onCompleted: {
        binding_datas.update()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

