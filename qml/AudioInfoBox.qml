import QtQuick 2.15
import com.company.PlayerController 1.0
import com.company.AudioInfo 1.0
import QtGraphicalEffects 1.15

Item {
    id: root
    anchors.centerIn: parent

    height: parent.height
    width: parent.width

    property string imgUrl: songImg.source

    anchors.margins: 20

    visible: !!PlayerController.currentSong

    Image{
        id:songImg

        anchors{
            centerIn: parent
            margins: 50
        }

        height: 240
        width: 240
        mipmap: true

        source: !!PlayerController.currentSong ? PlayerController.currentSong.songImg : ""

        layer.enabled: true
        layer.effect: DropShadow{
            radius: 10
            samples: 2 * radius + 1
        }
    }

    Flickable{
        id: audioNameFlickable

        anchors{
            left: songImg.left
            top: songImg.bottom
            topMargin: 10
            leftMargin: 5
        }

        width: songImg.width
        height: songName.height

        contentWidth: songName.width
        contentHeight: songName.height

        Text{
            id: songName

            font{
                pixelSize: 20
                bold: true
            }

            text: !!PlayerController.currentSong ? PlayerController.currentSong.songName : ""

            horizontalAlignment: Text.AlignLeft

            wrapMode: Text.WrapAtWordBoundaryOrAnywhere

            color: "white"

            layer.enabled: true
            layer.effect: DropShadow{
                radius: 10
                samples: 2 * radius + 1
            }
        }

        Timer{
            interval: 25
            repeat: true
            running: true

            onTriggered: {
                if(songName.width > audioNameFlickable.width && audioNameFlickable.contentX <= 1.3 * songName.width){
                    audioNameFlickable.contentX += 1
                }

                if(audioNameFlickable.contentX >= 1.3 * songName.width){
                    audioNameFlickable.contentX = -songName.width
                }
            }
        }
    }

    Flickable{
        id: authorNameFlickable

        anchors{
            left: songImg.left
            top: audioNameFlickable.bottom
            topMargin: 5
            leftMargin: 5
        }

        width: songImg.width
        height: authorName.height

        contentWidth: authorName.width
        contentHeight: authorName.height

        Text{
            id: authorName

            font{
                bold: true
                pixelSize: 15
            }

            text: !!PlayerController.currentSong ? PlayerController.currentSong.authorName : ""

            horizontalAlignment: Text.AlignLeft

            wrapMode: Text.WrapAtWordBoundaryOrAnywhere

            color: "white"

            layer.enabled: true
            layer.effect: DropShadow{
                radius: 10
                samples: 2 * radius + 1
            }
        }

        Timer{
            repeat: true
            running: true
            interval: 25

            onTriggered: {
                if(authorName.width > authorNameFlickable.width && authorNameFlickable.contentX <= 1.3 * authorName.width){
                    authorNameFlickable.contentX += 1
                }

                if(authorNameFlickable.contentX >= 1.3 * authorName.width){
                    authorNameFlickable.contentX = -authorName.width
                }
            }
        }
    }
}
