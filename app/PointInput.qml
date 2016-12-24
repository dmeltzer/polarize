import QtQuick 2.0
import QtQuick.Controls 1.4 as Controls
import QtQuick.Layouts 1.1

Rectangle {
    color: "red"
    property string title

    function values() {
        return [source_xField.displayText, source_yField.displayText, source_zField.displayText];
    }

    ColumnLayout {
        id: sourceLayout
        x: 8
        y: 8
        spacing: 1

        Text {
            id: source_inputLabel
            text: title
            font.bold: true
            font.pixelSize: 18
        }

        RowLayout {

            Text {
                id: source_xText
                text: qsTr("X:")
                font.pixelSize: 12
            }

            Controls.TextField {
                id: source_xField
                placeholderText: qsTr("X")
            }
        }

        RowLayout {

            Text {
                id: source_yText
                text: qsTr("Y:")
                font.pixelSize: 12
            }

            Controls.TextField {
                id: source_yField
                placeholderText: qsTr("Y")
            }
        }

        RowLayout {

            Text {
                id: source_zText
                text: qsTr("Z:")
                font.pixelSize: 12
            }

            Controls.TextField {
                id: source_zField
                placeholderText: qsTr("Z")
            }
        }

    }
}
