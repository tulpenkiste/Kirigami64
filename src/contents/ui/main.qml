// Includes relevant modules used by the QML
import QtQuick 2.6
import QtQuick.Controls 2.0 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.13 as Kirigami

import org.azreigh.kirigami64 0.1

// Base element, provides basic features needed for all kirigami applications
Kirigami.ApplicationWindow {
	// ID provides unique identifier to reference this element
	id: root

	// Window title
	// i18nc is useful for adding context for translators, also lets strings be changed for different languages
	title: i18nc("@title:window", "Kirigami64")

	globalDrawer: Kirigami.GlobalDrawer {
		title: i18n("Kirigami64")
		titleIcon: "kde"

		actions: [
			Kirigami.Action {
				text: "Play"
				icon.name: "media-playback-start"
			},
			Kirigami.Action {
				text: "Build"
				icon.name: "run-build"
				onTriggered: buildSheet.open()
			}/*,
			Kirigami.Action {
				text: i18n("About")
				icon.name: "help-about"
				onTriggered: pageStack.layers.push(aboutPage)
			}*/
		]
	}

	Kirigami.OverlaySheet {
		id: buildSheet

		header: Kirigami.Heading {
        	text: "Build - Repository Information"
    	}

		Kirigami.FormLayout {
			id: build
			Layout.fillWidth: true

			Controls.TextField {
				Kirigami.FormData.label: "Repository:"
			}
			Controls.TextField {
				Kirigami.FormData.label: "Branch Name:"
			}
			Controls.TextField {
				Kirigami.FormData.label: "Local Folder:"
			}
			Controls.Button {
				text: "Clone repository data"
        		//onClicked: showPassiveNotification("Boop!")
			}
		}
	}

	// Initial page to be loaded on app load
	pageStack.initialPage: Kirigami.Page {
		Controls.Label {
			text: Backend.introductionText
		}
	}
}