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
        width: 400
        height: 400
        spacing: 1
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Layout.preferredWidth: 400
            PointInput {
                id: sourceinput
                objectName: "sourceInput"
                title: "Source"
                width: 200
                height: 100
            }

            PointInput {
                id: targetinput
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
            onClicked: _demo.output(sourceinput.values(), targetinput.values());
        }

        ColumnLayout {
            id: bigOutputLayout
            Layout.fillHeight: false
            Layout.fillWidth: true
            width: parent.width
            spacing: 0
            Layout.preferredHeight: parent.height / 2
            Layout.preferredWidth: parent.width


            Text {
                id: output_text
                text: qsTr("Result")
                Layout.fillWidth: true
                Layout.fillHeight: false
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 18
            }
            RowLayout {
                id: outputLayout
                width: parent.width
                height: parent.height
                Layout.fillWidth: true
                Layout.rowSpan: 1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 10
                Layout.fillHeight: true

                ColumnLayout {
                    id: panLayout
                    width: parent.width
                    height: 100
                    Layout.preferredWidth: -1
                    Layout.fillWidth: false

                    Text {
                        id: output_panLabel
                        text: qsTr("Pan")
                        font.pixelSize: 12
                    }

                    Controls.TextField {
                        id: output_panEdit
                        text: _demo.pan.toFixed(2)
                        readOnly: true
                        font.pixelSize: 12
                    }
                }

                ColumnLayout {
                    id: tiltLayout
                    Text {
                        id: output_tiltLabel
                        text: qsTr("Tilt")
                        font.pixelSize: 12
                    }

                    Controls.TextField {
                        id: output_tiltEdit1
                        text: _demo.tilt.toFixed(2)
                        Layout.columnSpan: 1
                        Layout.preferredWidth: -1
                        readOnly: true
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
