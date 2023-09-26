import QtQuick 2.15
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: root

    signal accepted(string value)
    property alias text: searchTextInput.text

    color: "#FFFFFF"
    opacity: enabled ? 1.0 : 0.6
    radius: 25
    antialiasing: true

    TextField{
        id: searchTextInput

        anchors.fill: parent
        font.pixelSize: 20
        color: "#212121"
        leftPadding: searchImage.width + 30
        verticalAlignment: TextInput.AlignVCenter

        placeholderText: "Search"

        background: Rectangle{
            color: "#FFFFFF"
            radius: 25
        }

        Image{
            id: searchImage

            anchors{
                left: parent.left
                leftMargin: 15
                verticalCenter: parent.verticalCenter
            }

            source: "qrc:/images/search_icon.png"
            width: 24
            height: 24
            mipmap: true
        }

        onAccepted: {
            root.accepted(searchTextInput.text)
        }
    }

    layer.enabled: true

    layer.effect: DropShadow{
        id: searchfieldShadow
        radius: 5
        samples: 2 * radius + 1
        color: "white"
    }

}
