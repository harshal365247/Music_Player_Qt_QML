import QtQuick 2.15
import com.company.PlayerController 1.0
import QtGraphicalEffects 1.15
import QtQml 2.3
import QtQuick.Layouts 1.3

Rectangle{
    id: root

    property bool hidden : true

    signal searchRequested

    height: parent.height - topbar.height
    width: parent.width / 1.5

    color: "#212121"

    Rectangle{
        id: listTopBar

        anchors{
            left: parent.left
            top: parent.top
            bottomMargin: 20
            leftMargin: 10
            rightMargin: 10
        }

        width: parent.width - 2 * anchors.leftMargin
        height: 50
        color: "#FFFFFF"
        radius: 15

        Text{
            id: playlistText

            anchors{
                centerIn: parent
            }

            text: "PlayList"
            color: "#212121"

            font{
                bold: true
                pixelSize: 20
            }
        }

        layer.enabled: true
        layer.effect: DropShadow{
            radius: 10
            samples: 2 * radius + 1
        }
    }

    ListView{
        id: playlistView

        anchors{
            left: parent.left
            right: parent.right
            top: listTopBar.bottom
            bottom: addButton.top
            margins: 5
        }

        width: parent.width
        height: parent.height

        spacing: 10
        model: PlayerController
        clip: true

        delegate: Rectangle{
            id: element

            required property string audioTitle
            required property string audioAuthorName
            required property string audioImageSource
            required property string audioSource
            required property int index

            width: playlistView.width
            height: 60
            radius: 10

            color:{
                if(elementMouseArea.containsMouse){
                    return "#90A4AE"
                }
                else return "#212121"
            }


            Item{
                id: elementColumn
                width: parent.width
                height: parent.height

                anchors {
                    top: parent.top
                    left: parent.left
                    right: deleteButton.left
                    margins: 5
                }

                Flickable{
                    id: titleFlickable

                    anchors{
                        left: parent.left
                        top: parent.top
                        margins: 5
                    }

                    width: parent.width
                    height: audioTitle.height

                    contentWidth: audioTitle.width
                    contentHeight: audioTitle.height

                    Text{
                        id: audioTitle
                        text: element.audioTitle
                        color : "white"
                        font{
                            bold: true
                            pixelSize: 20
                        }
                    }

                    Timer{
                        interval: 25
                        repeat: true
                        running: true
                        onTriggered: {

                            if(audioTitle.width > titleFlickable.width && titleFlickable.contentX <= 1.3 * audioTitle.width){
                                titleFlickable.contentX += 1
                            }

                            if(titleFlickable.contentX >= 1.3 * audioTitle.width){
                                titleFlickable.contentX = -audioTitle.width
                            }
                        }
                    }
                }

                Flickable{
                    id: authorFlickable

                    anchors{
                        left: parent.left
                        top: titleFlickable.bottom
                        margins:5
                    }

                    width: parent.width
                    height: audioAuthor.height

                    contentWidth: audioAuthor.width
                    contentHeight: audioAuthor.height

                    Text{
                        id: audioAuthor
                        text: element.audioAuthorName
                        color: "white"
                        font{
                            pixelSize: 15
                        }
                    }

                    Timer{
                        interval: 25
                        repeat: true
                        running: true
                        onTriggered: {
                            if(audioAuthor.width > authorFlickable.width && authorFlickable.contentX <= 1.3 * audioAuthor.width){
                                authorFlickable.contentX += 1
                            }

                            if(authorFlickable.contentX >= 1.3 * audioAuthor.width){
                                authorFlickable.contentX = -audioAuthor.width
                            }
                        }
                    }
                }
            }


            MouseArea{
                id: elementMouseArea
                anchors.fill: parent
                onClicked: PlayerController.switchToAudioByIndex(element.index)
                hoverEnabled: true
            }

            TextButton{
                id: deleteButton

                anchors{
                    right: parent.right
                    bottom: parent.bottom
                    margins: 5
                }

                width: 16
                height: 16
                mipmap: true

                source: "qrc:/images/trash_icon.png"

                onClicked: PlayerController.removeAudio(element.index)

            }
        }
    }

    TextButton{
        id: addButton

        anchors {
            left: parent.left
            bottom: parent.bottom
            margins: 20
        }

        width: 32
        height: 32

        source: "qrc:/images/add_icon.png"

        onClicked: {
            root.searchRequested()
            root.hidden = true
        }
    }

    Behavior on x {
        PropertyAnimation {
            easing.type: Easing.InOutQuad
            duration: 200
        }
    }

    layer.enabled: true
    layer.effect: DropShadow{
        radius: 10
        samples: 2 * radius + 1
    }
}
