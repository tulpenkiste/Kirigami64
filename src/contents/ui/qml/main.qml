// Includes relevant modules used by the QML
import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

import org.tulpenkiste.kirigami64

// Base element, provides basic features needed for all kirigami applications
Kirigami.ApplicationWindow {
	// ID provides unique identifier to reference this element
	id: root

	function popCheck(requestedPage) {
		if (pageStack.layers.currentItem == requestedPage) {
			console.log("Requested page is already in use! Returning...");
			return;
		}
		
		console.log("Current layer depth: " + pageStack.layers.depth);

		if (pageStack.layers.depth > 1) {
			pageStack.layers.pop();
		}

		pageStack.layers.push(requestedPage);
	}

	ConfigureBuildSheet {
		id: configureBuildSheet
	}

	DisplaySheet {
		id: displaySheet
	}

	CloneSheet {
		id: cloneSheet
	}

	// Window title
	title: i18nc("@title:window", "Kirigami64")

	minimumWidth: Kirigami.Units.gridUnit * 35
	minimumHeight: Kirigami.Units.gridUnit * 25

	globalDrawer: Kirigami.GlobalDrawer {
		title: "Kirigami64"
		titleIcon: ":/icon.png"

		modal: false
		collapsible: true
		collapsed: true
		showHeaderWhenCollapsed: true
		
		//bannerVisible: true

		actions: [
			Kirigami.Action {
				text: i18n("Clone")
				icon.name: "run-build"
				onTriggered: popCheck(cloneSheet)
			},
			Kirigami.Action {
				text: i18n("Settings")
				icon.name: "settings-configure"
				onTriggered: pageStack.pushDialogLayer("qrc:/Config.qml", {}, { title: i18n("Settings") })
			}
		]
	}

	Shortcut {
		sequence: "Ctrl+Shift+."
		onActivated: {
			pageStack.pushDialogLayer("qrc:/Config.qml", {}, { title: i18n("Settings") })
		}
	}

	Kirigami.OverlaySheet {
		id: cloneProgressSheet

		header: Kirigami.Heading {
			text: i18n("Cloning repository...")
		}

		Kirigami.FormLayout {
			QQC2.Label {
				text: i18n("Cloning...")
				anchors.horizontalCenter: parent.horizontalCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
				visible: true
				anchors.centerIn: parent
			}

			QQC2.ProgressBar {
				from: 0
				to: 100
				value: 0
				indeterminate: Backend.downloadSizeUnknown
			}
		}
	}

	Kirigami.MenuDialog {
		id: selectedBuildSheet
		title: i18n("Options for ") + Backend.buildConfigSpecificDataGet(Backend.buildSelected, "name")
		
		actions: [
			Kirigami.Action {
				icon.name: "media-playback-start"
				text: i18n("Play")
				tooltip: i18n("Play this build")
				onTriggered: [Backend.run(Backend.buildList(Backend.buildSelected))]
			},
			Kirigami.Action {
				icon.name: "run-build-install"
				text: i18n("Compile")
				tooltip: i18n("Compile this build")
				onTriggered: [Backend.build(Backend.buildList(Backend.buildSelected))]
			},
			Kirigami.Action {
				icon.name: "update-none"
				text: i18n("Pull changes")
				tooltip: i18n("Pull changes for this repository off of the internet")
				onTriggered: [Backend.pull(Backend.buildList(Backend.buildSelected))]
			},
			Kirigami.Action {
				icon.name: "configure"
				text: i18n("Configure")
				tooltip: i18n("Configure this build")
				onTriggered: [selectedBuildSheet.close(), pageStack.layers.push(configureBuildSheet), configureBuildSheet.updateValues()]
			},
			Kirigami.Action {
				icon.name: "configure"
				text: i18n("Open repo data directory")
				tooltip: i18n("Opens a directory within your selected file manager")
				onTriggered: [selectedBuildSheet.close(), Backend.openRepoDataDir()]
			},
			Kirigami.Action {
				icon.name: "delete"
				text: i18n("Delete")
				tooltip: i18n("Delete the specified build")
				onTriggered: [Backend.rmDir(Backend.buildList(Backend.buildSelected)), selectedBuildSheet.close()]
			}
		]
	}

	// Initial page to be loaded on app load
	pageStack.initialPage: displaySheet
}
