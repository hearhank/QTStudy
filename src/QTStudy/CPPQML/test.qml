import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "../CPPQML/Controls/"

Item {
    SwitchButton {
        checked: true
        enabled: false
        width: 70
        height: 26
        spacing: 0
        leftPadding: 0
        rightPadding: 0
        text: checked ? "On" : "Off"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

