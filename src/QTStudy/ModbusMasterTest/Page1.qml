import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Page {
    id: root
    property bool isConnected: false
    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        GroupBox {
            width: parent.width
            Layout.fillWidth: true
            RowLayout {
                width: parent.width
                height: 50
                TextInput {
                    id: ipInput
                    text: "127.0.0.1"
                }
                RowLayout {
                    Layout.alignment: Qt.AlignRight
                    Button {
                        text: "Connect"
                        onClicked: {
                            if (isConnected) {
                                bCode.stop()
                                isConnected = false
                            } else {
                                bCode.start(ipInput.text)
                                isConnected = true
                            }
                        }
                    }
                }
            }
        }
        GroupBox {
            Layout.fillWidth: true
            RowLayout {
                width: parent.width
                TextEdit {
                    id: rowNum
                    text: "1"
                    Layout.minimumWidth: 100
                }
                TextEdit {
                    id: rowVal
                    text: "12"
                    Layout.minimumWidth: 100
                }

                RowLayout {
                    Layout.alignment: Qt.AlignHCenter
                    Button {
                        text: "Write"
                        onClicked: {
                            var v = Number(rowVal.text)
                            if (v <= 0) {
                                v = 255
                            }
                            bCode.write(Number(rowNum.text), v)
                            rowVal.text = String(--v)
                        }
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;height:300;width:600}
}
##^##*/

