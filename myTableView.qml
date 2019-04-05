import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
Item
{
    property alias myModel: myModel
    property int tableViewIndex: -1
    signal stopTask(string value);
    anchors.fill: parent
    ListModel{
        id:myModel
    }
    Row{
        id:head
        height: 25
        width: parent.width
        Rectangle{
            border.width: 1
            width: parent.width*2/5
            height: parent.height
            Text {
                anchors.centerIn: parent
                text: qsTr("文件名")
                font.pointSize: 12
            }
        }
        Rectangle{
            border.width: 1
            width: parent.width*3/20
            height: parent.height
            Text {
                anchors.centerIn: parent
                text: qsTr("已下载大小")
                font.pointSize: 12
            }
        }
        Rectangle{
            border.width: 1
            width: parent.width*3/20
            height: parent.height
            Text {
                anchors.centerIn: parent
                text: qsTr("进度")
                font.pointSize: 12
            }
        }
        Rectangle{
            border.width: 1
            width: parent.width*3/20
            height: parent.height
            Text {
                anchors.centerIn: parent
                text: qsTr("速度")
                font.pointSize: 12
            }
        }
        Rectangle{
            border.width: 1
            width: parent.width*3/20
            height: parent.height
            Text {
                anchors.centerIn: parent
                text: qsTr("平台")
                font.pointSize: 12
            }
        }
    }

    ListView
    {
        id:myView
        height: parent.height-35
        width: parent.width
        anchors.top:head.bottom
        model: ListModel{
            ListElement{
                fileNameText:"1111"
                totalSizeText:"1111"
                statusText:"1111"
                speedText:"1111"
                platformText:"11111"

            }
            ListElement{
                fileNameText:"2222"
                totalSizeText:"2222"
                statusText:"2222"
                speedText:"2222"
                platformText:"2222"

            }
            ListElement{
                fileNameText:"3333"
                totalSizeText:"3333"
                statusText:"3333"
                speedText:"3333"
                platformText:"3333"

            }
            ListElement{
                fileNameText:"4444"
                totalSizeText:"4444"
                statusText:"4444"
                speedText:"4444"
                platformText:"4444"

            }
            ListElement{
                fileNameText:"5555"
                totalSizeText:"5555"
                statusText:"5555"
                speedText:"5555"
                platformText:"5555"

            }
        }

        delegate:
            Component {
            Rectangle{
                height: 25
                width: parent.width
                Row{
                    height: 25
                    width: parent.width
                    Rectangle{
                        border.width: 1
                        width: parent.width*2/5
                        height: parent.height
                        Text {
                            id:fileName
                            anchors.centerIn: parent
                            text: qsTr(fileNameText)
                            font.pointSize: 12
                            elide: Text.ElideRight
                        }
                    }
                    Rectangle{
                        border.width: 1
                        width: parent.width*3/20
                        height: parent.height
                        Text {
                            id:totalSize
                            anchors.centerIn: parent
                            text: qsTr(totalSizeText)
                            font.pointSize: 12
                        }
                    }
                    Rectangle{
                        border.width: 1
                        width: parent.width*3/20
                        height: parent.height
                        Text {
                            id:status
                            anchors.centerIn: parent
                            text: qsTr(statusText)
                            font.pointSize: 12
                        }
                    }
                    Rectangle{
                        border.width: 1
                        width: parent.width*3/20
                        height: parent.height
                        Text {
                            id:speed
                            anchors.centerIn: parent
                            text: qsTr(speedText)
                            font.pointSize: 12
                        }
                    }
                    Rectangle{
                        border.width: 1
                        width: parent.width*3/20
                        height: parent.height
                        Text {
                            id:platform
                            anchors.centerIn: parent
                            text: qsTr(platformText)
                            font.pointSize: 12
                        }
                    }
                }
                MouseArea
                {
                    hoverEnabled: true
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onEntered: {
                        myView.currentIndex=index
                        var array=myView.currentItem.children
                        var firstchild=array[0].children
                        for(var i  in firstchild)
                        {
                            if(firstchild[i].color!="#b5afa2")
                            {
                                 firstchild[i].color="#EAE3D1"
                            }

                        }
                    }
                    onExited: {
                        myView.currentIndex=index
                        var array=myView.currentItem.children
                        var firstchild=array[0].children
                        for(var i  in firstchild)
                        {
                            if(firstchild[i].color!="#b5afa2")
                            {
                                firstchild[i].color="transparent";
                            }
                        }
                    }
                    onClicked: {
                        var array=myView.children
                        var firstchild=array[0].children
                        var firstchild2=firstchild[0].children
                        var firstchild3=firstchild2[0].children

                        for(var i  in firstchild)
                        {
                            var temp=firstchild[i].children
                            for(var j in temp)
                            {
                                var childs=temp[j].children
                                for(var k in childs)
                                {
                                    childs[k].color="transparent"
                                }
                            }
                        }

                        myView.currentIndex=index
                        var array2=myView.currentItem.children
                        var rect=array2[0].children
                        for(var d  in rect)
                        {
                            rect[d].color="#B5AFA2"
                        }
                        console.log(index)
                        if(mouse.button==Qt.RightButton)
                        {
                            contentMenu.popup()
                        }
                    }


                }
                Menu { // 右键菜单
                        //title: "Edit"
                        id: contentMenu

                        MenuItem {
                            text: "暂停任务"
                            onTriggered:
                            {
                                emit:stopTask(fileName.text)
                            }
                        }

                        MenuItem {
                            text: "继续任务"
                            shortcut: "Ctrl+C"
                            onTriggered: {}
                        }

                        MenuItem {
                            text: "Paste"
                            shortcut: "Ctrl+V"
                            onTriggered: {console.log("Paste")}
                        }
                }

            }

        }

    }


}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
