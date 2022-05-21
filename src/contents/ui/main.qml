// Includes relevant modules used by the QML
import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.19 as Kirigami

import org.azreigh.Kirigami64 0.2

// Base element, provides basic features needed for all kirigami applications
Kirigami.ApplicationWindow {
	// ID provides unique identifier to reference this element
	id: root

	ConfigSheet {
		id: configSheet
	}

	DisplaySheet {
		id: displaySheet
	}

	AboutSheet {
		id: aboutSheet
	}

	CloneSheet {
		id: cloneSheet
	}

	// Window title
	// i18nc is useful for adding context for translators, also lets strings be changed for different languages
	title: i18nc("@title:window", "Kirigami64")

	globalDrawer: Kirigami.GlobalDrawer {
		title: "Kirigami64"
		titleIcon: ":/icon.png"

		modal: false
		collapsible: true
		collapsed: true
		showHeaderWhenCollapsed: true
		
		bannerVisible: true

		actions: [
			Kirigami.Action {
				text: "Clone"
				icon.name: "run-build"
				onTriggered: pageStack.layers.push(cloneSheet)
			},
			Kirigami.Action {
				text: "Settings"
				icon.name: "settings-configure"
				onTriggered: pageStack.layers.push(configSheet)
			},
			Kirigami.Action {
				text: "About"
				icon.name: "help-about"
				onTriggered: pageStack.layers.push(aboutSheet)
			}
		]
	}

	Kirigami.OverlaySheet {
		id: cloneProgressSheet

		header: Kirigami.Heading {
			text: "Cloning repository..."
		}

		Kirigami.FormLayout {
			Controls.Label {
				text: "Cloning data..."
				anchors.horizontalCenter: parent.horizontalCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
				visible: true
				anchors.centerIn: parent
			}

			Controls.ProgressBar {
				from: 0
				to: 100
				value: 0
				indeterminate: Backend.downloadSizeUnknown
			}
		}
	}

	Kirigami.MenuDialog {
		id: selectedBuildSheet
		title: qsTr("Options for ") + Backend.buildConfigSpecificDataGet(Backend.buildSelected, "name")
		
		actions: [
			Kirigami.Action {
				iconName: "media-playback-start"
				text: qsTr("Play", "Play this build")
				tooltip: qsTr("Play this build")
				onTriggered: [Backend.run(Backend.buildList(Backend.buildSelected))]
			},
			Kirigami.Action {
				iconName: "run-build-install"
				text: qsTr("Compile", "Compile this build")
				tooltip: qsTr("Compile this build")
				onTriggered: [Backend.build(Backend.buildList(Backend.buildSelected))]
			},
			Kirigami.Action {
				iconName: "update-none"
				text: qsTr("Pull changes", "Pull changes for this repository off of the internet")
				tooltip: qsTr("Pull changes for this repository off of the internet")
				onTriggered: [Backend.pull(Backend.buildList(Backend.buildSelected))]
			},
			Kirigami.Action {
				iconName: "delete"
				text: qsTr("Delete", "Delete the specified build")
				tooltip: qsTr("Delete the specified build")
				onTriggered: [Backend.rmDir(Backend.buildList(Backend.buildSelected)), selectedBuildSheet.close()]
			}
		]
	}

	// Initial page to be loaded on app load
	pageStack.initialPage: displaySheet
}