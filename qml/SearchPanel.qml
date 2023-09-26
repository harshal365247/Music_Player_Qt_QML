import QtQuick 2.15
import QtGraphicalEffects 1.15
import com.company.AudioSearchModel 1.0
import com.company.PlayerController 1.0
import QtQuick.Controls 2.5

Rectangle{
    id: root
    width: parent.width
    height: parent.height / 2
    radius: 10
    anchors{
        leftMargin: 30
        rightMargin: 64
    }

    color: "#212121"

    property bool hidden: true


    ListView{
        id: searchListView

        anchors{
            fill: parent
            margins: 20
        }

        model: AudioSearchModel
        visible : !AudioSearchModel.isSearching
        clip: true
        spacing: 10

        delegate: Rectangle{
            id: elementSearchList
            width: searchListView.width
            height: 70
            anchors.margins: 10
            radius: 10

            color:{
                if(elementMouseArea.containsMouse){
                    return "#90A4AE"
                }
                else return "#212121"
            }

            required property string audioTitle
            required property string audioAuthorName
            required property string audioImageSource
            required property string audioSource
            required property int audioDuration

            Image {
                id: songImage

                anchors{
                    left: parent.left
                    top: parent.top
                    verticalCenter: parent.verticalCenter
                    margins: 10
                }

                source: elementSearchList.audioImageSource

                width: 32
                height: 32
                mipmap: true
                z:1
            }

            Item{
                id: elementColumn

                anchors{
                    left: songImage.right
                    right: parent.right
                    top: elementSearchList.top
                    margins: 10
                }

                Flickable{
                    id: songNameFlickable

                    anchors{
                        left: parent.left
                        top: parent.top
                        margins: 5
                    }

                    width: parent.width
                    height: songName.height

                    contentWidth: songName.width
                    contentHeight: songName.height

                    Text{
                        id: songName
                        text: elementSearchList.audioTitle

                        color: "white"

                        font{
                            pixelSize: 20
                            bold: true
                        }
                    }

                    Timer{
                        repeat: true
                        running: true
                        interval: 25

                        onTriggered: {
                            if(songName.width > songNameFlickable.width && songNameFlickable.contentX <= 1.3 * songName.width){
                                songNameFlickable.contentX += 1
                            }

                            if(songNameFlickable.contentX >= 1.3 * songName.width){
                                songNameFlickable.contentX = -songName.width
                            }
                        }

                    }
                }

                Flickable{
                    id: authorNameFlickable

                    anchors{
                        left: parent.left
                        top: songNameFlickable.bottom
                        margins: 5
                    }

                    width: parent.width
                    height: authorName.height

                    contentWidth: authorName.width
                    contentHeight: authorName.height

                    Text{
                        id: authorName

                        text: elementSearchList.audioAuthorName
                        color: "white"
                        font.pixelSize: 15
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

            MouseArea{
                id: elementMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    root.hidden = true
                    PlayerController.addAudio(elementSearchList.audioTitle, elementSearchList.audioAuthorName,
                                              elementSearchList.audioSource, elementSearchList.audioImageSource, elementSearchList.audioDuration)
                }
            }
        }
    }

    AnimatedImage{
        id: loadingGif

        source: "qrc:/images/loading_gif.gif"
        width: 32
        height: 32
        mipmap: true
        anchors.centerIn: parent
        visible: AudioSearchModel.isSearching
    }



    Text{
        id: centralText

        anchors{
            centerIn: parent
        }

        visible: searchListView.count === 0 && !AudioSearchModel.isSearching

        font{
            pixelSize: 30
            bold: true
        }

        color : "white"

        text: "No Results"
    }


    Behavior on y{
        PropertyAnimation{
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
