import QtQuick 2.0
import QtQuick.Controls 2.0
import Proton.Datas 1.0

Page {
    title: "Page2"
    Label {
        id: name1
        text: "Page2"
    }
    Component.onCompleted: {
        name1.text = Caches.get("name1", "None", "SYSTEM")
    }
}
