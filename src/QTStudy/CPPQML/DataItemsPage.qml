import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Proton.Datas 1.0

Page {
    id:root
    property var current:null
    function write(val)
    {
        current.value   =val;
    }

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
                    DataNode{
                        name: "Reset"
                        value: "reset length"
                        pControlType: DataNode.Button
                    },
                    DataNode{
                        name: "Mode"
                        value: 0
                        pControlType: DataNode.SWitchButton
                    }
                ]
            },
            DataNode {
                name: "Group 2"
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
                    },
                    DataNode{
                      name: "Speed"
                      value: "101"
                      unit: "m/s"
                      pControlType: DataNode.TextBox
                    },

                    DataNode {
                        name: "Gauge mode"
                        value: 0
                        desc: DataDesc {
                            offset: 1
                            dataType: DataDesc.Int
                        }
                        //refNames: "On/Off"
                        pControlType: DataNode.ComboBox
                        children: [
                            DataNode{
                                name: "Average"
                            },
                            DataNode{
                                name: "In Time"
                            }
                        ]
                    },
                    DataNode {
                        name: "Other"
                        refNames: ["On/Off", "Gauge mode"]
                        value: "1"
                        enabled: true
                        convertType: CH.NameC
                        onValueChanged: {
//                            console.log(val)
//                            console.log(vals)
                            fValue = vals[1] + "." + vals[0]
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
            onDoEditClicked: {
                if(ele.pControlType===DataNode.TextBox){
                    root.StackView.view.push("qrc:/InputEditPage.qml",{node:ele})
                }else if(ele.pControlType===DataNode.ComboBox)
                {
                    root.StackView.view.push("qrc:/SelectEditPage.qml",{node:ele})
                }else{
                    console.log("not support")
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

