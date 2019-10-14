import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Proton.Datas 1.0

Page {
    id:root
    property var current:null
    function write(val)
    {
        current.value=val;
    }

    DataNodes {
        id: hidden_datas
        name: "hidden_datas"
        children: [
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
        children: [
            NodeBase {
                name: "Group 1"
                selected: true
                children: [
                    DataNode{
                        name: "Reset"
                        value: "reset length"
                        control: DataNode.Button
                    },
                    DataNode{
                        name: "Mode"
                        value: 0
                        control: DataNode.SWitchButton
                    }
                ]
            },
            NodeBase {
                name: "Group 2"
                selected: false
                children: [
                    DataNode {
                        name: "On/Off"
                        value: 1
                        control: DataNode.SWitchButton
                        desc: DataDesc {
                            offset: 0
                            dataType: DataDesc.UShort
                        }
                        targets: ["Speed"]
                        calc: DataCalc {
                            type: DataCalc.Zoom
                            value: 1
                        }
                    },
                    DataNode{
                      name: "Speed"
                      value: "101"
                      unit: "m/s"
                      control: DataNode.TextBox
                      onTargetUpdated: {
//                          console.log(target)
                          console.log(target.value)
                          disabled =Number(target.value)===0
                      }
                    },

                    DataNode {
                        name: "Gauge mode"
                        value: 0
                        desc: DataDesc {
                            offset: 1
                            dataType: DataDesc.Int
                        }
                        //refNames: "On/Off"
                        control: DataNode.ComboBox
                        children: [
                            NodeBase{
                                name: "Average"
                            },
                            NodeBase{
                                name: "In Time"
                            }
                        ]
                    },
                    DataNode {
                        name: "Other"
                        sources: ["On/Off", "Gauge mode"]
                        value: "1"
                        converter: CH.NameC
                        onSourceUpdated: {
//                            console.log(datas)
                            fvalue=datas[0]+"+"+datas[1]
                        }
                    }
                ]
            }
        ]
    }

    ListView {
        id: wrapper
        anchors.fill: parent
        model: binding_datas.children
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
                if(ele.control===DataNode.TextBox){
                    root.StackView.view.push("qrc:/InputEditPage.qml",{node:ele})
                }else if(ele.control===DataNode.ComboBox)
                {
                    root.StackView.view.push("qrc:/SelectEditPage.qml",{node:ele})
                }else{
                    console.log("control:not support")
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

