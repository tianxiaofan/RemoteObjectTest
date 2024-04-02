import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    // Column {
    //     Repeater {
    //         anchors.fill: parent
    //         model: $tugs.replical
    //         delegate: Row {
    //             Text {
    //                 text: objectname
    //             }
    //             Text {
    //                 text: object_name
    //             }
    //             Text {
    //                 text: object_id
    //             }
    //         }
    //     }
    // }
    Column {
        Repeater {
            anchors.fill: parent
            model: $tugs.replical
            delegate: Row {
                Text {
                    text: object.name
                }
                Text {
                    text: object.name
                }
            }
        }
    }
    // Column {
    //     Repeater {
    //         anchors.fill: parent
    //         model: $tugs.replical
    //         delegate: Row {
    //             Text {
    //                 text: object_pointer.name
    //             }
    //             Text {
    //                 text: object_pointer.id
    //             }
    //         }
    //     }
    // }
}
