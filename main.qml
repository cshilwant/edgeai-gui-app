import QtQml 2.1
import QtQuick 2.14
import QtMultimedia
import QtQuick.Window 2.15
import QtQuick.Controls 2.1
import Qt.labs.folderlistmodel 2.4
import org.freedesktop.gstreamer.Qt6GLVideoItem 1.0

Window {
    visible: true
    visibility: "FullScreen"
    title: qsTr("Edge AI gallery")
    property var bgColor: "#111517"
    property var whiteColor: "#FEFFFF"
    property var buttonStopColor: "#c2324a"
    property var buttonIdleColor: "#1de0bf"
    property var buttonHoverColor: "#7dffe9"

    MouseArea {
        id: globalMouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    Rectangle {
        id: appBackground
        color: bgColor
        width: parent.width
        height: parent.height

        Rectangle {
            id: topBar
            width: parent.width
            height: parent.height * 0.08
            anchors.top: parent.top
            anchors.left: parent.left
            color: bgColor

            Image {
                id: topBarLogo
                scale: Qt.KeepAspectRatio
                height: parent.height / 2
                width: height * 8 // To maintain the aspect ratio of the image
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: (parent.height - height)/2
                anchors.leftMargin: 10
                source: "images/Texas-Instruments.png"

                Button {
                id: easterEggButton
                height: parent.height
                width: parent.width * 0.15

                anchors.left: parent.left
                anchors.top: parent.top

                background: Rectangle {
                    color: "#00000000"
                }

                Timer {
                    id: timer
                }

                function delay(delayTime, cb) {
                    timer.interval = delayTime;
                    timer.repeat = false;
                    timer.triggered.connect(cb);
                    timer.start();
                }

                onClicked: {
                    backend.increase_easter_egg_click_cnt();
                    var click_cnt = backend.get_easter_egg_click_cnt();
                    if (click_cnt == '0') {
                        popup_easter_egg_content.text = backend.get_random_content()
                        popup_easter_egg.open()
                        delay(5000, function() {
                            popup_easter_egg.close()
                            timer.stop()
                        })
                    }
                }

                MouseArea {
                    width: parent.width
                    height: parent.height
                    cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                    enabled: false
                    readonly property bool containsMouse: {
                        var relativePos = mapFromItem(globalMouseArea, globalMouseArea.mouseX, globalMouseArea.mouseY);
                        return contains(Qt.point(relativePos.x, relativePos.y));
                    }
                }
            }

            }

            Text {
                id: topBarHead
                objectName: "topBarHead"
                text: qsTr("Edge AI gallery")

                width: parent.width * 0.8
                height: parent.height
                anchors.left: topBarLogo.right
                anchors.top: parent.top

                color: whiteColor
                font.family: "Ubuntu"
                font.bold: true
                font.pointSize: 35
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                id: topBarExitButton
                onClicked: Qt.quit()
                height: parent.height * 0.3
                width: height

                anchors.right: parent.right
                anchors.rightMargin: width * 0.5
                anchors.top: parent.top
                anchors.topMargin: height * 0.5

                background: Rectangle {
                    Text {
                        text: "X"
                        font.pointSize: 12
                        color: whiteColor
                        anchors.centerIn: parent
                        font.bold: true
                    }
                    color: "#FF0000"
                    radius: parent.height
                }

                MouseArea {
                    width: parent.width
                    height: parent.height
                    cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                    enabled: false
                    readonly property bool containsMouse: {
                        var relativePos = mapFromItem(globalMouseArea, globalMouseArea.mouseX, globalMouseArea.mouseY);
                        return contains(Qt.point(relativePos.x, relativePos.y));
                    }
                }
            }
        }
        Rectangle {
            id: leftMenu

            width: parent.width * 0.15
            height: parent.height * 0.85
            anchors.top: topBar.bottom
            anchors.left: parent.left

            color: bgColor

            Rectangle {
                id: leftSubMenu

                width: parent.width * 0.9
                height: parent.height * 0.7
                anchors.horizontalCenter: leftMenu.horizontalCenter
                anchors.verticalCenter: leftMenu.verticalCenter
                color: "#1c2326"

                border.color: whiteColor
                border.width: 1
                radius: 2

                CheckBox {
                    id: leftMenuButton1
                    height:  (parent.height - (0.2 * parent.height)) / 5
                    width: parent.width * 0.85
                    anchors.top: parent.top
                    anchors.topMargin:(0.2 * parent.height) / 6
                    anchors.horizontalCenter: parent.horizontalCenter
                    indicator: Rectangle {}
                    background: Rectangle {
                        id: leftMenuButton1BG
                        color: !parent.enabled ? bgColor : (parent.checkState===Qt.Checked? buttonStopColor : (mouseArea1.containsMouse ? buttonHoverColor : buttonIdleColor))
                        border.color: whiteColor
                        border.width: 1
                        radius: 5
                    }
                    onCheckStateChanged: {
                        if (leftMenuButton1.checked) {
                            backend.leftMenuButtonPressed(1, leftMenu.width + (alignVideo.border.width * 2), topBar.height + ((mainWindow.height - alignVideo.height)/2) + (alignVideo.border.width * 2), videooutput.width, videooutput.height, videooutput);
                            leftMenuButton2.enabled = false
                            leftMenuButton3.enabled = false
                            leftMenuButton4.enabled = false
                            leftMenuButton5.enabled = false
                        } else {
                            backend.stopVideo();
                            leftMenuButton2.enabled = true
                            leftMenuButton3.enabled = true
                            leftMenuButton4.enabled = true
                            leftMenuButton5.enabled = true
                        }
                    }

                    MouseArea {
                        id: mouseArea1
                        width: parent.width
                        height: parent.height
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        enabled: false
                        readonly property bool containsMouse: {
                            var relativePos = mapFromItem(globalMouseArea, globalMouseArea.mouseX, globalMouseArea.mouseY);
                            return contains(Qt.point(relativePos.x, relativePos.y));
                        }
                    }


                    Text {
                        text: "Image Classification"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        font.family: "Helvetica"
                        font.pixelSize: parent.width * 0.075
                        color: parent.checkState===Qt.Checked? whiteColor : bgColor
                    }
                }

                CheckBox {
                    id: leftMenuButton2
                    height: (parent.height - (0.2 * parent.height)) / 5
                    width: parent.width * 0.85
                    anchors.top: leftMenuButton1.bottom
                    anchors.topMargin:(0.2 * parent.height) / 6
                    anchors.horizontalCenter: parent.horizontalCenter
                    indicator: Rectangle {}
                    background: Rectangle {
                        id: leftMenuButton2BG
                        color: !parent.enabled ? bgColor : (parent.checkState===Qt.Checked? buttonStopColor : (mouseArea2.containsMouse ? buttonHoverColor : buttonIdleColor))
                        border.color: whiteColor
                        border.width: 1
                        radius: 5
                    }
                    onCheckStateChanged: {
                        if (leftMenuButton2.checked) {
                            backend.leftMenuButtonPressed(2, leftMenu.width + (alignVideo.border.width * 2), topBar.height + ((mainWindow.height - alignVideo.height)/2) + (alignVideo.border.width * 2), videooutput.width, videooutput.height, videooutput);
                            leftMenuButton1.enabled = false
                            leftMenuButton3.enabled = false
                            leftMenuButton4.enabled = false
                            leftMenuButton5.enabled = false
                        } else {
                            backend.stopVideo();
                            leftMenuButton1.enabled = true
                            leftMenuButton3.enabled = true
                            leftMenuButton4.enabled = true
                            leftMenuButton5.enabled = true
                        }
                    }
                    MouseArea {
                        id: mouseArea2
                        width: parent.width
                        height: parent.height
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        enabled: false
                        readonly property bool containsMouse: {
                            var relativePos = mapFromItem(globalMouseArea, globalMouseArea.mouseX, globalMouseArea.mouseY);
                            return contains(Qt.point(relativePos.x, relativePos.y));
                        }
                    }
                    Text {
                        text: "Object Detection"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        font.family: "Helvetica"
                        font.pixelSize: parent.width * 0.075
                        color: parent.checkState===Qt.Checked? whiteColor : bgColor
                    }
                }
                CheckBox {
                    id: leftMenuButton3
                    height: (parent.height - (0.2 * parent.height)) / 5
                    width: parent.width * 0.85
                    anchors.top: leftMenuButton2.bottom
                    anchors.topMargin:(0.2 * parent.height) / 6
                    anchors.horizontalCenter: parent.horizontalCenter
                    indicator: Rectangle {}
                    background: Rectangle {
                        id: leftMenuButton3BG
                        color: !parent.enabled ? bgColor : (parent.checkState===Qt.Checked? buttonStopColor : (mouseArea3.containsMouse ? buttonHoverColor : buttonIdleColor))
                        border.color: whiteColor
                        border.width: 1
                        radius: 5
                    }
                    onCheckStateChanged: {
                        if (leftMenuButton3.checked) {
                            backend.leftMenuButtonPressed(3, leftMenu.width + (alignVideo.border.width * 2), topBar.height + ((mainWindow.height - alignVideo.height)/2) + (alignVideo.border.width * 2), videooutput.width, videooutput.height, videooutput);
                            leftMenuButton1.enabled = false
                            leftMenuButton2.enabled = false
                            leftMenuButton4.enabled = false
                            leftMenuButton5.enabled = false

                        } else {
                            backend.stopVideo();
                            leftMenuButton1.enabled = true
                            leftMenuButton2.enabled = true
                            leftMenuButton4.enabled = true
                            leftMenuButton5.enabled = true
                        }
                    }
                    MouseArea {
                        id: mouseArea3
                        width: parent.width
                        height: parent.height
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        enabled: false
                        readonly property bool containsMouse: {
                            var relativePos = mapFromItem(globalMouseArea, globalMouseArea.mouseX, globalMouseArea.mouseY);
                            return contains(Qt.point(relativePos.x, relativePos.y));
                        }
                    }
                    Text {
                        text: "Semantic Segmentation"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        font.family: "Helvetica"
                        font.pixelSize: parent.width * 0.075
                        color: parent.checkState===Qt.Checked? whiteColor : bgColor
                    }
                }
                CheckBox {
                    id: leftMenuButton4
                    height: (parent.height - (0.2 * parent.height)) / 5
                    width: parent.width * 0.85
                    anchors.top: leftMenuButton3.bottom
                    anchors.topMargin:(0.2 * parent.height) / 6
                    anchors.horizontalCenter: parent.horizontalCenter
                    indicator: Rectangle {}
                    background: Rectangle {
                        id: leftMenuButton4BG
                        color: !parent.enabled ? bgColor : (parent.checkState===Qt.Checked? buttonStopColor : (mouseArea4.containsMouse ? buttonHoverColor : buttonIdleColor))
                        border.color: whiteColor
                        border.width: 1
                        radius: 5
                    }
                    onCheckStateChanged: {
                        if (leftMenuButton4.checked) {
                            backend.leftMenuButtonPressed(4, leftMenu.width + (alignVideo.border.width * 2), topBar.height + ((mainWindow.height - alignVideo.height)/2) + (alignVideo.border.width * 2), videooutput.width, videooutput.height, videooutput);
                            leftMenuButton1.enabled = false
                            leftMenuButton2.enabled = false
                            leftMenuButton3.enabled = false
                            leftMenuButton5.enabled = false

                        } else {
                            backend.stopVideo();
                            leftMenuButton1.enabled = true
                            leftMenuButton2.enabled = true
                            leftMenuButton3.enabled = true
                            leftMenuButton5.enabled = true
                        }
                    }
                    MouseArea {
                        id: mouseArea4
                        width: parent.width
                        height: parent.height
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        enabled: false
                        readonly property bool containsMouse: {
                            var relativePos = mapFromItem(globalMouseArea, globalMouseArea.mouseX, globalMouseArea.mouseY);
                            return contains(Qt.point(relativePos.x, relativePos.y));
                        }
                    }
                    Text {
                        text: "Multi Channel"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        font.family: "Helvetica"
                        font.pixelSize: parent.width * 0.075
                        color: parent.checkState===Qt.Checked? whiteColor : bgColor
                    }
                }

                CheckBox {
                    id: leftMenuButton5
                    height: (parent.height - (0.2 * parent.height)) / 5
                    width: parent.width * 0.85
                    anchors.top: leftMenuButton4.bottom
                    anchors.topMargin:(0.2 * parent.height) / 6
                    anchors.horizontalCenter: parent.horizontalCenter
                    indicator: Rectangle {}
                    background: Rectangle {
                        id: leftMenuButton5BG
                        color: !parent.enabled ? bgColor : (parent.checkState===Qt.Checked? buttonStopColor : (mouseArea5.containsMouse ? buttonHoverColor : buttonIdleColor))
                        border.color: whiteColor
                        border.width: 1
                        radius: 5
                    }
                    onCheckStateChanged: {
                        if (leftMenuButton5.checked) {
                            popupError.text = " "
                            popup.open()
                            leftMenuButton1.enabled = false
                            leftMenuButton2.enabled = false
                            leftMenuButton3.enabled = false
                            leftMenuButton4.enabled = false
                        } else {
                            backend.stopVideo();
                            leftMenuButton1.enabled = true
                            leftMenuButton2.enabled = true
                            leftMenuButton3.enabled = true
                            leftMenuButton4.enabled = true
                        }
                    }
                    MouseArea {
                        id: mouseArea5
                        width: parent.width
                        height: parent.height
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        enabled: false
                        readonly property bool containsMouse: {
                            var relativePos = mapFromItem(globalMouseArea, globalMouseArea.mouseX, globalMouseArea.mouseY);
                            return contains(Qt.point(relativePos.x, relativePos.y));
                        }
                    }
                    Text {
                        text: "Custom"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        font.family: "Helvetica"
                        font.pixelSize: parent.width * 0.075
                        color: parent.checkState===Qt.Checked? whiteColor : bgColor
                    }
                }
            }
        }
        Rectangle {
            id: mainWindow
            color: bgColor
            width: parent.width * 0.84
            height: parent.height * 0.88
            anchors.top: topBar.bottom
            anchors.left: leftMenu.right
            anchors.rightMargin: parent.width * 0.02

            Rectangle {
                id: alignVideo
                width: parent.width
                height: (parent.width / 16) * 9
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: (parent.height - height) / 2
                border.color: whiteColor
                border.width: 3

                radius: 5
                color: bgColor

                Image {
                    width: parent.width
                    height: parent.height
                    source: "file://opt/oob-demo-assets/wallpaper.jpg"
                    anchors.fill: parent
                    anchors.margins: parent.border.width * 2
                }

                GstGLQt6VideoItem {
                    objectName: "videoItem"
                    id: videooutput
                    width: parent.width
                    height: parent.height
                    anchors.fill: parent
                    anchors.margins: parent.border.width * 2
                }
            }
            Popup {
                id: popup
                anchors.centerIn: parent

                width: alignVideo.width * 0.3
                height: alignVideo.height * 0.6

                modal: true
                focus: true
                closePolicy: Popup.NoAutoClose

                background: Rectangle {
                    width: parent.width
                    height: parent.height
                    border.color: whiteColor
                    border.width: 10
                }

                Text {
                    id: inputTypeHead
                    text: qsTr("Input Type: ")
                    font.pointSize: 11
                    anchors.centerIn: popup.Center
                    anchors.bottom: popupInputType.top
                    anchors.bottomMargin: popupInputType.height * 0.2
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.2
                }

                ComboBox {
                    id: popupInputType
                    width: parent.width * 0.6
                    height: parent.height * 0.1
                    anchors.top: parent.top
                    anchors.topMargin: parent.height * 0.175
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.2

                    model: ListModel {
                        id: popupInputTypeOptions
                        ListElement { Text: "Image" }
                        ListElement { Text: "Video" }
                        ListElement { Text: "Camera" }
                    }
                    onCurrentIndexChanged: {
                        if (popupInputTypeOptions.get(currentIndex).Text === "Image") {
                            popupInputImages.visible = true
                            popupInputVideos.visible = false
                            popupInputCameras.visible = false
                        }
                        if (popupInputTypeOptions.get(currentIndex).Text === "Video") {
                            popupInputImages.visible = false
                            popupInputVideos.visible = true
                            popupInputCameras.visible = false
                        }
                        if (popupInputTypeOptions.get(currentIndex).Text === "Camera") {
                            popupInputImages.visible = false
                            popupInputVideos.visible = false
                            popupInputCameras.visible = true
                        }
                    }
                }
                Text {
                    id: inputHead
                    text: qsTr("Input: ")
                    font.pointSize: 11
                    anchors.bottom: popupInputImages.top
                    anchors.bottomMargin: popupInputImages.height * 0.2
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.2
                }
                Text {
                    id: inputPath
                    text: qsTr(" ")
                    color: "#888888"
                    font.pointSize: 11
                    anchors.bottom: popupInputImages.top
                    anchors.bottomMargin: popupInputImages.height * 0.2
                    anchors.left: inputHead.right
                    anchors.leftMargin: inputHead.width * 0.2
                }
                ComboBox {
                    id: popupInputImages
                    visible: false
                    width: parent.width * 0.6
                    height: parent.height * 0.1
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.2
                    anchors.top: popupInputType.bottom
                    anchors.topMargin: parent.height * 0.1

                    FolderListModel{
                        id: inputImagesFolder
                        folder: "file:///opt/edgeai-test-data/images/"
                        nameFilters: [ "*.jpg", "*.png" ]
                    }

                    model: inputImagesFolder
                    textRole: 'fileName'
                    onVisibleChanged: {
                        if(visible) {
                            inputHead.text = qsTr("Image:")
                            inputPath.text = qsTr("/opt/edgeai-test-data/images/")
                        }
                    }
                }
                ComboBox {
                    id: popupInputVideos
                    visible: false
                    width: parent.width * 0.6
                    height: parent.height * 0.1
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.2
                    anchors.top: popupInputType.bottom
                    anchors.topMargin: parent.height * 0.1

                    FolderListModel{
                        id: inputVideosFolder
                        folder: "file:///opt/edgeai-test-data/videos/"
                        nameFilters: [ "*.mp4", "*.h264", "*.avi" ]
                    }

                    model: inputVideosFolder
                    textRole: 'fileName'
                    onVisibleChanged: {
                        if(visible) {
                            inputHead.text = qsTr("Video:")
                            inputPath.text = qsTr("/opt/edgeai-test-data/videos/")
                        }
                    }
                }
                ComboBox {
                    id: popupInputCameras
                    visible: false
                    width: parent.width * 0.6
                    height: parent.height * 0.1
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.2
                    anchors.top: popupInputType.bottom
                    anchors.topMargin: parent.height * 0.1

                    model: cameraNamesList
                    textRole: 'display'
                    onVisibleChanged: {
                        if(visible) {
                            inputHead.text = qsTr("Camera: ")
                            inputPath.text = qsTr(" ")
                        }
                    }
                }
                Text {
                    id: modelHead
                    text: qsTr("Model:")
                    font.pointSize: 11
                    anchors.bottom: popupModel.top
                    anchors.bottomMargin: popupModel.height * 0.2
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.2
                }
                Text {
                    id: modelPath
                    text: qsTr("/opt/model_zoo/")
                    color: "#888888"
                    font.pointSize: 11
                    anchors.bottom: popupModel.top
                    anchors.bottomMargin: popupModel.height * 0.2
                    anchors.left: modelHead.right
                    anchors.leftMargin: modelHead.width * 0.2
                }

                ComboBox {
                    id: popupModel
                    width: parent.width * 0.6
                    height: parent.height * 0.1
                    anchors.top: popupInputImages.bottom
                    anchors.topMargin: parent.height * 0.1
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.2
                    model: modelNamesList
                    textRole: 'display'
                }
                Text {
                    id: popupError
                    text: " "
                    color: "#FF0000"
                    font.pointSize: 11
                    anchors.top: popupModel.bottom
                    anchors.topMargin: parent.height * 0.025
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.2
                }

                Button {
                    id: popupOkButton
                    text: "Start"
                    onClicked: {
                        popupError.text = "Loading ..."
                        var inputType = popupInputType.model.get(popupInputType.currentIndex).Text
                        var inputFile
                        var modelFile
                        if (popupInputType.model.get(popupInputType.currentIndex).Text === "Image")
                            inputFile = popupInputImages.model.get(popupInputImages.currentIndex, "filePath")
                        if (popupInputType.model.get(popupInputType.currentIndex).Text === "Video")
                            inputFile = popupInputVideos.model.get(popupInputVideos.currentIndex, "filePath")
                        if (popupInputType.model.get(popupInputType.currentIndex).Text === "Camera")
                            inputFile = popupInputCameras.model.data(popupInputCameras.model.index(popupInputCameras.currentIndex, 0))

                        modelFile = "/opt/model_zoo/" + popupModel.model.data(popupModel.model.index(popupModel.currentIndex, 0))

                        if((inputFile === undefined) || (modelFile === undefined)) {
                            popupError.text = "Invalid Inputs!"
                        } else {
                            popupError.text = "Loading ..."
                            // Send userdata to CPP
                            backend.popupOkPressed(inputType, inputFile, modelFile,
                                                                           leftMenu.width + (alignVideo.border.width * 2), topBar.height + ((mainWindow.height - alignVideo.height)/2) + (alignVideo.border.width * 2),
                                                                           videooutput.width, videooutput.height, videooutput);
                            popup.close()
                        }
                    }

                    width: parent.width * 0.2
                    height: parent.height * 0.075

                    anchors.top: popupError.bottom
                    anchors.topMargin: parent.height * 0.025
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.25

                    background: Rectangle {
                        color: parent.hovered ? buttonIdleColor : "#CCCCCC"
                        radius: parent.height
                    }
                }

                Button {
                    id: popupCancelButton
                    text: "Cancel"
                    onClicked: {
                        popup.close()
                        leftMenuButton5.checked = false
                    }

                    width: parent.width * 0.2
                    height: parent.height * 0.075

                    anchors.top: popupError.bottom
                    anchors.topMargin: parent.height * 0.025
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width * 0.25

                    background: Rectangle {
                        color: parent.hovered ? buttonIdleColor : "#CCCCCC"
                        radius: parent.height
                    }
                }
                Text {
                    id: popupNote
                    text: "Note: Models may take time to load after you click 'Start'. So please wait for few seconds!"
                    font.pointSize: 10
                    font.bold: true
                    color: buttonIdleColor
                    width: parent.width * 0.8
                    anchors.top: popupCancelButton.bottom
                    anchors.topMargin: parent.height * 0.05
                    wrapMode: Text.WordWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Popup {
                id: popup_easter_egg
                anchors.centerIn: parent

                width: parent.width * 0.3
                height: parent.height * 0.1

                modal: true
                focus: true
                closePolicy: Popup.NoAutoClose

                onOpened: {
                    popup_easter_egg_progress_timer.start()
                    popup_easter_egg_progress_timer.running = true;
                }

                onClosed: {
                    popup_easter_egg_progress_timer.stop()
                    popup_easter_egg_progress_timer.running = false;
                    popup_easter_egg_progress.value = 0
                }

                background: Rectangle {
                    width: parent.width
                    height: parent.height
                    color: "#202020"
                    radius: 4
                }

                Text {
                    id: popup_easter_egg_content
                    text: ""
                    font.pointSize: 11
                    font.bold: true
                    font.family: "Ubuntu"
                    width: parent.width
                    wrapMode: Text.WordWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: whiteColor
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                ProgressBar {
                    id : popup_easter_egg_progress
                    from: 0
                    value: 0
                    to: 100
                    width: parent.width
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: -10

                    contentItem: Item {
                        Rectangle {
                            width: popup_easter_egg_progress.visualPosition * parent.width
                            height: parent.height
                            radius: 2
                            color: "#17a81a"
                        }
                    }
                }

                Timer
                {
                    id: popup_easter_egg_progress_timer
                    interval: 50
                    repeat: true
                    running: false
                    onTriggered: popup_easter_egg_progress.value += 1
                }



            }

        }
        Rectangle {
            id: deviceInfo
            anchors.left: mainWindow.left
            anchors.right: mainWindow.right
            anchors.top: mainWindow.bottom
            anchors.bottom: parent.bottom
            color: bgColor
            Text {
                id: info1
                text: "<font color=\"#FEFFFF\">Web: </font><font color=\"#FF0000\">https://ti.com/edgeai</font><font color=\"#FEFFFF\"> | Support: </font><font color=\"#FF0000\">https://e2e.ti.com/</font>"
                font.pointSize: 15
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                id: ipAddr
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right

                text: backend.ip_addr
                color: whiteColor
                font.pointSize: 15
            }
        }
    }
}
