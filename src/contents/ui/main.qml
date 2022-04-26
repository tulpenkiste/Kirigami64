// Includes relevant modules used by the QML
import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.19 as Kirigami

import org.azreigh.Kirigami64 0.1

// Base element, provides basic features needed for all kirigami applications
Kirigami.ApplicationWindow {
	// ID provides unique identifier to reference this element
	id: root

	// Window title
	// i18nc is useful for adding context for translators, also lets strings be changed for different languages
	title: i18nc("@title:window", "Kirigami64")

	globalDrawer: Kirigami.GlobalDrawer {
		title: "Kirigami64"
		titleIcon: "kde"
		
		bannerVisible: true

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
				text: "About"
				icon.name: "help-about"
				onTriggered: pageStack.layers.push(aboutPage)
			},
			Kirigami.Action {
				text: "Test"
				icon.name: "help-about"
				onTriggered: selectedBuildSheet.open()
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
				onClicked: Backend.clone()
			}
		}
	}

	Kirigami.OverlaySheet {
		
		id: cloneOverlay

		header: Kirigami.Heading {
        	text: "Cloning repository"
    	}

		Controls.ProgressBar {
			from: 0
			to: 100
			value: 0
			indeterminate: true
		}

	}

	Kirigami.MenuDialog {
        id: selectedBuildSheet
        title: qsTr("Build Options")
        
        actions: [
            Kirigami.Action {
				iconName: "media-playback-start"
				text: qsTr("Play", "Play this build")
				tooltip: qsTr("Play this build")
			},
			Kirigami.Action {
				iconName: "document-open-folder"
				text: qsTr("Show in folder", "Show the folder within your file manager")
				tooltip: qsTr("Show the folder within your file manager")
			},
			Kirigami.Action {
				iconName: "documentinfo"
				text: qsTr("View details", "View build details")
				tooltip: qsTr("View build details")
			},
			Kirigami.Action {
				iconName: "update-none"
				text: qsTr("Pull changes", "Pull changes for this repository off of the internet")
				tooltip: qsTr("Pull changes for this repository off of the internet")
			},
			Kirigami.Action {
				iconName: "delete"
				text: qsTr("Delete", "Delete the specified build")
				tooltip: qsTr("Delete the specified build")
			}
        ]
    }


	// Initial page to be loaded on app load
	pageStack.initialPage: Kirigami.ScrollablePage {
	}

	Component {
        id: aboutPage

        Kirigami.AboutPage {
            aboutData: AboutType.aboutData
        }
    }
}