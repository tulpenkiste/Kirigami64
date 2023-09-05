import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.19 as Kirigami

import org.tulip.Kirigami64 0.2

Kirigami.ScrollablePage {
	id: configSheet

	RowLayout {
		ColumnLayout {
			Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

			Layout.maximumWidth: 450.0

			Kirigami.Heading {
				Layout.fillWidth: true
				level: 2
				type: Kirigami.Heading.Type.Primary
				text: "Sources"

				horizontalAlignment: Text.AlignHCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
			}

			Controls.Label {
				Layout.fillWidth: true
				wrapMode: Text.WordWrap
				text: "This section is to modify application sources."
			}

			Controls.ToolButton {
				Layout.alignment: Qt.AlignLeft
				Layout.columnSpan: 2
				text: i18n("Modify sources in text editor")
				icon.name: "document-edit"
				flat: false
				onClicked: [showPassiveNotification("Opening editor..."), Backend.openSources()]
			}

			Kirigami.Heading {
				Layout.fillWidth: true
				level: 2
				type: Kirigami.Heading.Type.Primary
				text: "Launch Options"
				horizontalAlignment: Text.AlignHCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
			}

			Controls.Label {
				Layout.fillWidth: true
				wrapMode: Text.WordWrap
				text: "Configure launch settings"
			}

			Controls.Switch {
				Layout.alignment: Qt.AlignLeft
				Layout.columnSpan: 2
				checkable: true
				checked: Backend.useMangoHud
				onCheckedChanged: Backend.useMangoHud = checked
				text: i18n("Use MangoHud")
			}

			Controls.Switch {
				Layout.alignment: Qt.AlignLeft
				Layout.columnSpan: 2
				checkable: true
				checked: Backend.useGameMode
				onCheckedChanged: Backend.useGameMode = checked
				text: i18n("Use GameMode")
			}

			Kirigami.Heading {
				Layout.fillWidth: true
				level: 2
				type: Kirigami.Heading.Type.Primary
				text: "Roms"
				horizontalAlignment: Text.AlignHCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
			}

			RowLayout {
				Kirigami.Label {
					text: "Default ROM type:"
				}

				Controls.ComboBox {
					width: 200
					model: ["US", "EU", "JP"]
					currentIndex: Backend.currentRegion()
					onCurrentIndexChanged: Backend.setCurrentRegion(currentIndex)
				}
			}
			
			RowLayout {
				Kirigami.Label {
					text: "US Rom Path:"
				}

				Controls.TextField {
					id: usRomPath
					placeholderText: "path..."
					text: Backend.getROMPath(0)
					onTextEdited: [console.log("PATHUS: " + usRomPath.text), Backend.setROMPath(0, usRomPath.text)]
				}

				Controls.Button {
					text: "Find in filesystem"
					onClicked: fileDialogUS.open()
				}
			}
			
			RowLayout {
				Kirigami.Label {
					text: "EU Rom Path:"
				}

				Controls.TextField {
					id: euRomPath
					placeholderText: "path..."
					text: Backend.getROMPath(1)
					onTextEdited: [console.log("PATHEU: " + euRomPath.text), Backend.setROMPath(1, euRomPath.text)]
				}

				Controls.Button {
					text: "Find in filesystem"
					onClicked: fileDialogEU.open()
				}
			}
			
			RowLayout {
				Kirigami.Label {
					text: "JP Rom Path:"
				}

				Controls.TextField {
					id: jpRomPath
					placeholderText: "path..."
					text: Backend.getROMPath(2)
					onTextEdited: [console.log("PATHJP: " + jpRomPath.text), Backend.setROMPath(2, jpRomPath.text)]
				}

				Controls.Button {
					text: "Find in filesystem"
					onClicked: fileDialogJP.open()
				}
			}

			FileDialog {
				id: fileDialogUS
				folder: shortcuts.home
				onAccepted: {
					var path = fileUrl.toString();
					// remove prefixed "file:///"
					path = path.replace(/^(file:\/{2})/,"");
					// unescape html codes like '%23' for '#'
					var cleanPath = decodeURIComponent(path);
					usRomPath.text = cleanPath
					Backend.setROMPath(0, cleanPath)
				}
			}

			FileDialog {
				id: fileDialogEU
				folder: shortcuts.home
				onAccepted: {
					var path = fileUrl.toString();
					// remove prefixed "file:///"
					path = path.replace(/^(file:\/{2})/,"");
					// unescape html codes like '%23' for '#'
					var cleanPath = decodeURIComponent(path);
					euRomPath.text = cleanPath
					Backend.setROMPath(1, cleanPath)
				}
			}

			FileDialog {
				id: fileDialogJP
				folder: shortcuts.home
				onAccepted: {
					var path = fileUrl.toString();
					// remove prefixed "file:///"
					path = path.replace(/^(file:\/{2})/,"");
					// unescape html codes like '%23' for '#'
					var cleanPath = decodeURIComponent(path);
					jpRomPath.text = cleanPath
					Backend.setROMPath(2, cleanPath)
				}
			}
		}
	}
}
