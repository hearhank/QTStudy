import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Proton.Datas 1.0

Page {
    DataNodes {
        id: hidden_datas
        name: "hidden_datas"
        nodes: [
            DataNode {
                name: "Count"
                value: 10
                onValueChanged: console.log(value)
            }
        ]
    }

    DataNodes {
        id: binding_datas
        name: "binding_datas"
        nodes: [
            DataNode {
                name: "Group 1"
                children: [
                    DataNode {
                        name: "On/Off"
                        value: 1
                        pControlType: DataNode.SWitchButton
                        desc: DataDesc {
                            offset: 0
                            dataType: DataDesc.UShort
                        }
                        calc: DataCalc {
                            type: DataCalc.Zoom
                            value: 1
                        }
                    }
                ]
            },
            DataNode {
                name: "Group 2"
                children: [
                    DataNode {
                        name: "Last Name"
                        value: "Hank"
                        desc: DataDesc {
                            offset: 1
                            dataType: DataDesc.Int
                        }
                    },
                    DataNode {
                        name: "Full Name"
                        refNames: ["On/Off", "Last Name"]
                        value: ""
                        enabled: true
                        convertType: CH.NameC
                        onValueChanged: {
                            console.log(val)
                            console.log(vals)
                            value = vals[1] + "." + vals[0]
                        }
                    }
                ]
            }
        ]
    }

    ListView {
        id: wrapper
        anchors.fill: parent
        model: binding_datas.nodes
        delegate: GroupSettings {
            width: parent.width
            onTitleClicked: {
                wrapper.currentIndex = group
                var i = 0
                for (; i < wrapper.model.length; i++) {
                    wrapper.model[i].selected = (i === group)
                }
            }
        }
    }

    PageOperationTimer {
        id: operator
        interval: 10
    }

    Component.onCompleted: {
        operator.setDataItems(hidden_datas)
        operator.setDataItems(binding_datas)
        operator.start()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

