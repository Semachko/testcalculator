import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Gui

ApplicationWindow {
    visible: true
    width: 500
    height: 500
    title: "Calculator"
    Component.onCompleted: {
        calculator.get_history()
    }
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        TextField {
            id: inputField
            placeholderText: "Input expression"
            font.pixelSize: 18
            Layout.fillWidth: true
        }

        Label {
            id: outputLabel
            Layout.fillWidth: true
            text: "Result:"
            font.pixelSize: 18
            color: "black"
            Connections {
                target: calculator
                function onNewResult(result) {
                    outputLabel.text = "Result: " + result
                }
                function onError(error) {
                    outputLabel.text = "Error: " + error
                }
            }
        }

        Button {
            id: calcButton
            Layout.fillWidth: true
            text: "Calculate"
            font.pixelSize: 16
            onClicked: {
                if (inputField.text.length > 0) {
                    calculator.calculate(inputField.text)
                }
            }
        }
        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 20
            Label {
                text: "History:"
                color: "black"
                font.pixelSize: 18
                font.italic: true
            }            
            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                TextArea {
                    id: historyText
                    anchors.fill: parent
                    wrapMode: Text.Wrap
                    text: ""
                    font.pixelSize: 16
                    Connections {
                        target: calculator
                        function onNewHistory(result) {
                            historyText.text = result
                        }
                    }
                }
            }
            // ScrollView {
            //     Layout.fillWidth: true
            //     Layout.fillHeight: true
            //     Rectangle {
            //         color: "#f0f0f0"
            //         radius: 6
            //         border.color: "#ccc"
            //         border.width: 1
            //         anchors.fill: parent
            //         TextArea {
            //             id: historyText
            //             anchors.fill: parent
            //             wrapMode: Text.Wrap
            //             text: ""
            //             font.pixelSize: 16
            //             Connections {
            //                 target: calculator
            //                 function onNewHistory(result) {
            //                     historyText.text = result
            //                 }
            //             }
            //         }
            //     }
            // }
            // Rectangle {
            //     Layout.fillWidth: true
            //     Layout.fillHeight: true
            //     color: "#f0f0f0"
            //     radius: 6
            //     border.color: "#ccc"
            //     border.width: 1
            //     ListView {
            //         id: historyView
            //         model: historyModel
            //         anchors.fill: parent
            //         delegate: Row {
            //             spacing: 8
            //             Text { text: model.expr }
            //             Text { text: "= " + model.res }
            //         }
            //     }
            // }
        }

    }
}
