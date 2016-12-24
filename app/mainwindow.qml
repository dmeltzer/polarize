import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4 as Controls
import QtQuick.Window 2.2
import QtQuick.Templates 2.0

Controls.ApplicationWindow {
    id: window
    width: 400
    height: 400
    title: "Test App"
    visible: true
    minimumWidth:  250
    minimumHeight: 250
    maximumWidth:  40000
    maximumHeight: 40000

    signal calculate(variant source, variant target)

    MessageDialog {
        id: aboutDialog
        icon: StandardIcon.Information
        title: "About"
        text: "Qt Quick Controls Gallery"
        informativeText: "This example demonstrates most of the available Qt Quick Controls."
    }

    menuBar : Controls.MenuBar {
        Controls.Menu {
            title: "&File"
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit()
            }
        }
        Controls.Menu {
            title: "&Help"
            MenuItem {
                text: qsTr("H&elp")
                onTriggered: aboutDialog.open()
            }
        }
    }

    ColumnLayout {
        spacing: 1
//        width: 450
//        height: 400

        RowLayout {
            Layout.preferredHeight: 100
            Layout.preferredWidth: 300
            id: inputLayout
            PointInput {
                id: "sourceInput"
                objectName: "sourceInput"
                title: "Source"
                width: 200
                height: 100
            }

            PointInput {
                id: "targetInput"
                objectName: "targetInput"
                title: "Target"
                width: 200
                height: 100
            }
        }

        Controls.Button {
            id: calculate
            text: qsTr("Calculate")
            checkable: false
//            onClicked: window.calculate(sourceInput.values(),
//                                        targetInput.values())
            onClicked: _demo.output(sourceInput.values(), targetInput.values());
        }

        ColumnLayout {
            id: bigOutputLayout
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100


            Text {
                id: output_text
                text: qsTr("Result")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 18
            }
            RowLayout {
                id: outputLayout
                width: 306
                height: 100

                ColumnLayout {
                    id: panLayout
                    width: 100
                    height: 100

                    Text {
                        id: output_panLabel
                        text: qsTr("Pan")
                        font.pixelSize: 12
                    }

                    TextEdit {
                        id: output_panEdit
                        width: 80
                        height: 20
                        text: qsTr("Text Edit")
                        font.pixelSize: 12
                    }
                }

                ColumnLayout {
                    id: tiltLayout
                    width: 100
                    height: 100
                    Text {
                        id: output_tiltLabel
                        text: qsTr("Tilt")
                        font.pixelSize: 12
                    }

                    TextEdit {
                        id: output_tiltEdit1
                        width: 80
                        height: 20
                        text: qsTr("Text Edit")
                        font.pixelSize: 12
                    }
                }
            }
        }
    }

    Connections {
        target: calculate
        onClicked: print("clicked")
    }

}
