import QtQuick 2.15

Image {
    id: root

    signal clicked

    opacity: (mouseareaButton.containsMouse) ? 0.30 : 1

    mipmap: true

    MouseArea{
        id: mouseareaButton

        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            root.clicked()
        }
    }

}
