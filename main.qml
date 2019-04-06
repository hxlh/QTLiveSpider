import QtQuick 2.9
import QtQuick.Controls 2.4
import InteractionClass 1.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
ApplicationWindow {

    visible: true
    width: 1200
    height: 600
    id:mainWindow
    title: qsTr("Scroll")
    flags:Qt.FramelessWindowHint | Qt.WindowSystemMenuHint | Qt.WindowMinimizeButtonHint| Qt.Window;
   Rectangle{
       anchors.fill: parent
       border.width: 1
       Rectangle{
           id:title
           width: parent.width
           height: 35
           color: "#EAE3D1"
           Image {
               id: myIco
               source: "file:///"+applicationDirPath+"/myIco.ico"
               width: 35
               height: 35
           }

           MouseArea
           {
               anchors.fill: parent
               acceptedButtons: Qt.LeftButton //只处理鼠标左键
               property point clickPos: "0,0"
               onPressed: { //接收鼠标按下事件
                   clickPos  = Qt.point(mouse.x,mouse.y)
               }
               onPositionChanged: { //鼠标按下后改变位置
                   //鼠标偏移量
                   var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)

                   //如果mainwindow继承自QWidget,用setPos
                   mainWindow.setX(mainWindow.x+delta.x)
                   mainWindow.setY(mainWindow.y+delta.y)
               }



           }
           Button{
               id:closeButton
               anchors.right: parent.right
               width: 35
               height: 35
               background:Image {
                   source: "file:///"+applicationDirPath+"/closeButtonP.png"
               }
               onClicked: Qt.quit()
           }
           Button{
               id:minButton
               anchors.right: closeButton.left
               width: 35
               height: 35
               background:Image {
                   source: "file:///"+applicationDirPath+"/minButtonP.png"
               }
               onClicked: mainWindow.showMinimized()

           }
          Rectangle{
              id:addTaskButton
              x:parent.width/2-100
              width:200
              height: 35
              color: "#CBBBA1"
              radius: 10
              Text {
                  font.pointSize: 15
                  anchors.centerIn: parent
                  text: qsTr("添加任务")
              }
              MouseArea{
                  anchors.fill: parent
                  onClicked: {
                      dialogLoader.sourceComponent=myDialog
                  }
                  onPressed: addTaskButton.color="#B4A68F"
                  onReleased: addTaskButton.color="#CBBBA1"
              }

          }
       }

       Loader{
           id:tableViewLoader
           width: parent.width
           height: parent.height-35
           anchors.top:title.bottom
           source: "myTableView.qml"

       }
       Connections{
           target: tableViewLoader.item
           ignoreUnknownSignals:true
           onStopTask:{
               interactionClass.stopTask(value)
           }
           onContinueTask:{
               interactionClass.continueTask(value)
           }
           onStopTimer:{
               interactionClass.stopTimer()
           }
           onContinueTimer:{
               interactionClass.continueTimer()
           }
           onDeleteTask:{
               interactionClass.deleteTask(value)
           }
       }

       Loader{
           id:dialogLoader
           anchors.top:title.bottom
           width: 600
           height: 300
       }
       InteractionClass{
           id:interactionClass
           onSlot_upData: {
               tableViewLoader.item.myModel.clear()
               var array=JSON.parse(result)
               for(var i=0;i<array.length;++i)
               {
                   var jsonObj=JSON.parse(array[i])
                   tableViewLoader.item.myModel.append({"fileNameText":jsonObj.fileNameText,"totalSizeText":jsonObj.totalSizeText,"speedText":jsonObj.speedText,"platformText":jsonObj.platformText,"statusText":jsonObj.statusText})
               }
               tableViewLoader.item.tableViewUpdate()
           }
       }
       Component{
           id:myDialog
           Rectangle{
               id:rect
               color: "#EAE3D1"
               border.width: 1
               Button{
                   anchors.right: parent.right
                   width: 30
                   height: 30
                   background:Image {
                       source: "file:///"+applicationDirPath+"/closeButtonP.png"
                   }
                   onClicked: dialogLoader.setSource("")
               }

               Column{
                   spacing: 7
                   width: parent.width
                   y:20
                   Text {
                       text: qsTr("直播网址")
                       font.pointSize: 13
                       width: 50
                   }
                   TextField{
                       id:urlInput
                       font.pointSize: 13
                       width: parent.width
                       placeholderText: "请输入直播网址"

                   }
                   Text {
                       text: qsTr("文件名")
                       font.pointSize: 13
                       width: 50
                   }
                   TextField{
                       id:fileNameInput
                       font.pointSize: 13
                       width: parent.width
                       placeholderText: "请输入文件名"
                   }
                   Text{
                       text:qsTr("保存位置")
                       font.pointSize: 13
                       width: 70
                   }

                   TextField{
                       id:filePathInput
                       font.pointSize: 13
                       width: parent.width-35
                       placeholderText: "请保存位置或点击右边的按钮"
                       Button{
                           anchors.left: filePathInput.right
                           width: 30
                           font.pointSize: 13
                           text:"....."
                           onClicked: fileDialog.open()
                       }
                   }
                   Row{
                       anchors.right: parent.right
                       spacing: 5
                       Button{
                           font.pointSize: 13
                           text: "确定"
                           width: 100
                           height: 50
                           onClicked:  {
                               interactionClass.addTask(urlInput.text+","+fileNameInput.text+","+filePathInput.text)
                               dialogLoader.setSource("")
                           }
                       }
                       Button{
                           font.pointSize: 13
                           text: "取消"
                           width: 100
                           height: 50
                           onClicked: {
                               dialogLoader.setSource("")

                           }
                       }

                   }


               }

               function setFilePath(value){
                   filePathInput.text=value
               }
           }
       }
       FileDialog {
         id: fileDialog
         title: qsTr("请选择目录")
         selectFolder: true
         onAccepted: {
             dialogLoader.item.setFilePath(fileDialog.folder.toString().substring(8))
         }
        }

   }

}
