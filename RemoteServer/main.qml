import QtQuick 2.15
import QtQuick.Window 2.15
import HostTest 1.0
import ActorO 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    HostTest {
        id: host
        Component.onCompleted: {
            for (var h in host) {
                console.log(h)
            }
            console.log("---------")
            console.log(actor)
            console.log(actor.name)
            console.log("---------")
            console.log(actorO)
            console.log(actorO.name)
        }
    }
    Column {
        Repeater {
            model: host.customMode
            delegate: Row {
                Text {
                    text: objectname
                }
                Text {
                    text: object_name
                }
                Text {
                    text: object_id
                }
                Rectangle {
                    height: parent.height
                    width: 2
                    color: "red"
                }
            }
        }
    }
}
