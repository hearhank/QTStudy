import QtQuick 2.0
import QtQuick.Controls 2.0
import Proton.Datas 1.0

Page {
    DataItems {
        id: binding_datas
        datas: [
            DataItem {
                name: "First Name"
                value: "Chen"
                desc: DataDesc {
                    offset: 0
                    dataType: DataDesc.UShort
                }
            },
            DataItem {
                name: "Last Name"
                value: "Hank"
            },
            DataItem {
                name: "Full Name"
                refNames: ["First Name", "Last Name"]
                value: ""
                convertType: ConverterType.NameC
            }
        ]
    }

    ListView {
        id: wrapper
        anchors.fill: parent
        model: binding_datas.datas
        delegate: ItemDelegate {
            Item {
                width: parent.width
                height: 35

                //color: index % 2 == 0 ? "white" : "silver"
                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    id: name
                    text: model.value
                }

                //                Rectangle {
                //                    color: index % 2 == 0 ? "white" : "silver"
                //                    height: 1
                //                    anchors.fill: parent
                //                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        wrapper.currentIndex = index
                    }
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
