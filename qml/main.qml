import QtQuick 2.15
import QtQuick.Window 2.15
import com.company.PlayerController 1.0
import com.company.AudioSearchModel 1.0
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.5

Window {
    id: root
    width: 480
    height: 640
    visible: true
    title: qsTr("Music Player")

    Rectangle{
        id: topbar
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }

        height: 70
        color: "#212121"
        z: 1

        SearchField{
            id: searchfield

            anchors{
                left: parent.left
                right: menuButton.left
                top: parent.top
                bottom: parent.bottom
                topMargin: 15
                bottomMargin: 15
                rightMargin: 20
                leftMargin: 20
            }

            visible: !SearchPanel.hidden
            enabled: !AudioSearchModel.isSearching

            onAccepted: value =>{
                            searchPanel.hidden = false
                            AudioSearchModel.searchSong(value)
                            topbar.forceActiveFocus()
                        }
        }


        TextButton{
            id: menuButton

            anchors{
                right: parent.right
                verticalCenter: parent.verticalCenter
                margins: 20
            }

            width: 24
            height: 24

            source: "qrc:/images/menu_icon.png"
            mipmap: true

            onClicked: {
                playlistPanel.hidden = !playlistPanel.hidden
            }
        }

        TextButton{
            id: closeSearchField

            anchors{
                right: searchfield.right
                verticalCenter: searchfield.verticalCenter
                rightMargin: 15
            }

            width: 24
            height: 24
            mipmap: true
            source: "qrc:/images/remove_icon.png"

            onClicked:{
                searchPanel.hidden = true
                searchfield.text = ""
            }
        }

        layer.enabled: true
        layer.effect: DropShadow{
            radius: 15
            samples: 2 * radius + 1
        }
    }

    Rectangle{
        id: mainRect
        anchors{
            left: parent.left
            right: parent.right
            top: topbar.bottom
            bottom: bottombar.top
        }

        color: "#424242"

        Image{
            id: mainRectImg
            source: songBox1.imgUrl
            anchors.fill: parent
            z: 0
        }

        FastBlur{
            source: mainRectImg
            anchors.fill: mainRectImg
            radius: 32
        }

        AudioInfoBox{
            id: songBox1

            anchors{
                centerIn: parent
            }
        }

    }

    Rectangle{
        id: bottombar

        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        height: 100
        color: "#212121"

        Row{
            anchors.centerIn: parent
            spacing: 40

            TextButton{
                id: preButton

                anchors.verticalCenter: parent.verticalCenter

                width: 24
                height: 24
                mipmap: true

                source: "qrc:/images/previous_icon.png"

                onClicked: PlayerController.playPreviousSong()

                layer.enabled: true
                layer.effect: DropShadow{
                    radius: 5
                    samples: 2 * radius + 1
                }
            }


            TextButton{
                id: playButton

                anchors.verticalCenter: parent.verticalCenter

                width: 64
                height: 64
                mipmap: true

                source: (PlayerController.playing)? "qrc:/images/pause_icon.png" : "qrc:/images/play_icon.png"

                onClicked: PlayerController.playPause()

                layer.enabled: true
                layer.effect: DropShadow{
                    radius: 5
                    samples: 2 * radius + 1
                }
            }

            TextButton{
                id: nextButton

                anchors.verticalCenter: parent.verticalCenter

                width: 24
                height: 24
                mipmap: true

                source: "qrc:/images/next_icon.png"

                onClicked: PlayerController.playNextSong()

                layer.enabled: true
                layer.effect: DropShadow{
                    radius: 5
                    samples: 2 * radius + 1
                }
            }

        }

        Slider{
            id: musicSlider

            visible: !!PlayerController.currentSong

            from: 0
            to: !!PlayerController.currentSong ? PlayerController.currentSong.duration : 0
            value: !!PlayerController.currentSong ? PlayerController.sliderPosition : 0

            anchors{
                verticalCenter: parent.top
                left: parent.left
                right:parent.right
                leftMargin: 7
                rightMargin: 7
            }

            onMoved:{
                PlayerController.moveSlider(musicSlider.value)
            }
        }

        Text{
            id: startTime

            anchors{
                top: parent.top
                left: parent.left
                topMargin: 7
                leftMargin: 7
            }

            visible: musicSlider.visible

            text:{
                var seconds = Math.floor(musicSlider.value % 60)
                var minutes = Math.floor(musicSlider.value / 60)
                return minutes + ":" + (seconds < 10 ? "0" : "") + seconds
            }

            font.pixelSize: 15
            color: "#FFFFFF"
        }

        Text{
            id: endTime

            anchors{
                top: parent.top
                right: parent.right
                topMargin: 5
                rightMargin: 5
            }

            visible: musicSlider.visible

            text:{
                var seconds = Math.floor(musicSlider.to % 60)
                var minutes = Math.floor(musicSlider.to / 60)
                return minutes + ":" + (seconds < 10 ? "0" : "") + seconds
            }

            font.pixelSize: 15
            color: "#FFFFFF"
        }

    }

    PlayListPanel {
        id: playlistPanel

        anchors {
            top: topbar.bottom
        }

        x: hidden ? parent.width : parent.width - width
        z:2

        onSearchRequested: {
            searchPanel.hidden = false
        }
    }

    SearchPanel{
        id: searchPanel

        anchors{
            left: parent.left
            right: parent.right
        }

        y: hidden ? parent.height - 2 * parent.height : topbar.height - 10
        z: 0
    }

}
