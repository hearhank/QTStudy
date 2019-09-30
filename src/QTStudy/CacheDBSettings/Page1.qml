import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Proton.Datas 1.0

Page {
    title: "Page1"
    RowLayout {
        width: parent.width
        height: 50
        Label {
            text: "input test:"
        }
        TextInput {
            id: input
            width: 200
            text: "Hank"
        }
        Button {
            text: "Test"
            onClicked: {
                Caches.set("interval", 100, "SYSTEM")
                //                Caches.set("Name","SLminiMK3", "SLmini")
                //                Caches.set("name1", input.text, "SYSTEM")
            }
        }
    }
}
