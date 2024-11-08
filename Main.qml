import QtQuick
import QtQuick.Controls
import Sudoku

Window {
    id: sudo
    width: 600
    height: 450
    visible: true
    title: qsTr("Sudoku Solver")

    Backend{
            id: sudoku
        }

    property var sudokuData: sudoku.sudokuData

    component Box : Rectangle{
        id:box
        width:50
        height:50
        border.color: "black"
        border.width: 1
        color: box.highlight ? "lightblue" : "white"

        property int row: 0
        property int col: 0
        property bool highlight: false

        TextInput{
            id:fill
            anchors.fill: parent
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            validator: IntValidator{bottom: 1; top: 9}
            maximumLength: 1
            text: sudo.sudokuData[row][col] > 0 ? sudo.sudokuData[row][col].toString() : ""

            onEditingFinished: {
                if(text !== ""){
                    sudoku.setSudokuData(row,col,parseInt(fill.text))
                }
            }
        }
    }

    Grid{
        id: grid
        width: 450
        height: 450
        anchors.left: parent.left
        anchors.top: parent.top
        columns: 9
        rows: 9
        Repeater{
            model: 81
            Box{
                width: 450 / 9
                height: parent.height / 9
                row: Math.floor(index / 9)
                col: index % 9
                highlight: (row === sudoku.highlightRow && col === sudoku.highlightCol)
            }
        }
    }

    component SudokuButton: Button{
        height: parent.height * 0.4
        anchors.right: parent.right;
        anchors.rightMargin: 40
        anchors.left: grid.right
        anchors.leftMargin: 40
    }

    SudokuButton{
        id: solve
        text: qsTr("Solve")
        anchors.bottom: parent.verticalCenter
        onClicked: sudoku.solve(0,0)

    }

    SudokuButton{
        id: reset
        text: qsTr("Clear")
        anchors.top: solve.bottom
        anchors.horizontalCenter: solve.horizontalCenter
        onClicked: sudoku.setReset()

    }
}
