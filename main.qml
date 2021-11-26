import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    id: window

    header: ToolBar{
            ToolButton{
                id: menuButton
                anchors.left : parent.left
                anchors.verticalCenter: parent.verticalCenter
                icon.source: "images/menu.png"
              //  onClicked: drawer.open()
            }
            Label {
                anchors.centerIn: parent
                text: "File Manager"
                font.pixelSize: 20
                elide: Label.ElideRight
            }
            TextField{
                id:textfield
                placeholderText: qsTr("Search....")
                anchors.right: parent.right
                anchors.rightMargin: 10
                background: Rectangle{
                    implicitWidth: 200
                    implicitHeight: menuButton.height
                    radius: 5
                    border.color: "aqua"
                    border.width: 2
                }
                onAccepted: {
                    console.log( textfield.displayText) ;
                    myManager.find(textfield.displayText);
                }
            }
        }
   // footer: rowLayout

    ListView{
        currentIndex: 1
        id: listViewRoot
        anchors.fill: parent
        spacing: 5
        model: myManager
        delegate: folderDelegate
        highlight: Rectangle {color: "lightsteelblue";radius: 5}
        focus: true

    }
    Component{
            id: folderDelegate
            Item{
                width : parent.width
                height: 60
                Rectangle{
                    id: rectangleImage
                    width: 40
                    height: 40
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 50

                    color: "blue"

                    Image {
                        anchors.fill: parent
                        anchors.verticalCenter:parent.verticalCenter
                        source: model.manager_image
                    }
                }

                Text{
                      anchors.left: rectangleImage.left
                      anchors.verticalCenter: parent.verticalCenter
                      anchors.leftMargin: 60
                      text: model.manager_name
                    }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                       listViewRoot.currentIndex = index
                    }
                    onDoubleClicked:
                    {
                        myManager.changeData(model.index)
                    }
            }
        }
    }
    RowLayout{
      id: rowLayout
      anchors.fill: parent
       height: 50
       width: 480
     // anchors.bottom: listViewRoot.bottom
     // Layout.alignment: parent.bottom
    //  anchors.right: listViewRoot.right
        spacing: 5

        Button{
            //id: back
            height: 50
            //Layout.fillWidth: true
            width : 70
            //Layout.alignment: remove.right
           // Layout.alignment: Qt.AlignRight
            Layout.alignment: Qt.AlignBottom
            text: qsTr("Back")

           // onClicked:
        }

        Button{
          id: remove
            height: 50
            width: 70
            //Layout.fillWidth: true
            //Layout.alignment: parent.right
           // Layout.alignment: Qt.AlignRight
            Layout.alignment: Qt.AlignBottom
            text: qsTr("Remove/Delete")
        }
     }


//    StatusBar{
//        id: statusbar
//        style: StatusBarStyle {
//            padding {
//                left: 8
//                right: 8
//                top: 3
//                bottom: 3
//            }
//            background: Rectangle {
//                implicitHeight: 16
//                implicitWidth: 200
//                gradient: Gradient{
//                    GradientStop{color: "#eee" ; position: 0}
//                    GradientStop{color: "#ccc" ; position: 1}
//                }
//                Rectangle {
//                    anchors.top: parent.top
//                    width: parent.width
//                    height: 1
//                    color: "#999"
//                }
//            }
//        }
//    }

}
