// Includes relevant modules used by the QML
import QtQuick 2.6
import QtQuick.Controls 2.0 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.13 as Kirigami

import org.azreigh.Kirigami64 0.1

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
			},
			Kirigami.Action {
				text: i18n("About")
				icon.name: "help-about"
				onTriggered: pageStack.layers.push(aboutPage)
			}
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
				id: repoInp
				Kirigami.FormData.label: "Repository:"
				onEditingFinished: Backend.repoText = text
			}
			Controls.TextField {
				id: branchInp
				Kirigami.FormData.label: "Branch Name:"
				onEditingFinished: Backend.branchText = text
			}
			Controls.TextField {
				id: folderInp
				Kirigami.FormData.label: "Local Folder:"
				onEditingFinished: Backend.folderText = text
			}
			Controls.Button {
				text: "Clone repository data"
				onClicked: Backend.clone
			}
		}
	}

	// Initial page to be loaded on app load
	pageStack.initialPage: playPage

	Kirigami.Page {
		id: playPage
		Controls.Label {
			text: Backend.introductionText
			anchors.centerIn: parent
		}
	}

	Component {
        id: aboutPage

        Kirigami.AboutPage {
            aboutData: AboutType.aboutData
        }
    }
}