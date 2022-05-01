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
				text: "Clone"
				icon.name: "run-build"
				onTriggered: buildSheet.open()
			},
			Kirigami.Action {
				text: "About"
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
			/*Controls.TextField {
				id: folderInp
				Kirigami.FormData.label: "Local Folder:"
				onEditingFinished: Backend.folderText = text
			}*/
			Controls.Button {
				text: "Clone repository data"
				onClicked: [Backend.clone(), buildSheet.close(), cloneProgressSheet.open()]
			}
		}
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
		title: qsTr("Build Options for build ") + Backend.buildList(Backend.buildSelected)
		
		actions: [
			Kirigami.Action {
				iconName: "media-playback-start"
				text: qsTr("Play", "Play this build")
				tooltip: qsTr("Play this build")
			},
			Kirigami.Action {
				iconName: "media-playback-start"
				text: qsTr("Compile", "Compile this build")
				tooltip: qsTr("Compile this build")
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
			}
		]
	}


	// Initial page to be loaded on app load
	pageStack.initialPage: Kirigami.ScrollablePage {
		actions.main: Kirigami.Action {
			id: refreshButton
			iconName: "view-refresh"
			text: qsTr("Refresh", "Refresh list")
			tooltip: qsTr("Refresh list")
			onTriggered: Backend.buildFind(0)
		}
		Kirigami.CardsListView {
			id: view
			model: Backend.buildCount

			delegate: Kirigami.AbstractCard {
				contentItem: Item {
					implicitWidth: delegateLayout.implicitWidth
					implicitHeight: delegateLayout.implicitHeight
					GridLayout {
						id: delegateLayout
						anchors {
							left: parent.left
							top: parent.top
							right: parent.right
						}
						rowSpacing: Kirigami.Units.largeSpacing
						columnSpacing: Kirigami.Units.largeSpacing
						columns: width > Kirigami.Units.gridUnit * 20 ? 4 : 2
						Kirigami.Icon {
							source: "application-x-n64-rom"
							Layout.fillHeight: true
							Layout.maximumHeight: Kirigami.Units.iconSizes.huge
							Layout.preferredWidth: height
						}
						ColumnLayout {
							Kirigami.Heading {
								level: 2
								text: Backend.buildList(modelData)
							}
							Kirigami.Separator {
								Layout.fillWidth: true
							}
							Controls.Label {
								Layout.fillWidth: true
								wrapMode: Text.WordWrap
								text: qsTr("Build description invalid.")
							}
						}
						Controls.Button {
							Layout.alignment: Qt.AlignRight|Qt.AlignVCenter
							Layout.columnSpan: 2 
							text: qsTr("View Build Options")
							onClicked: [Backend.setBuildSelected(Backend.buildList(modelData)), selectedBuildSheet.open()]// showPassiveNotification("Install for Product " + modelData + " clicked");
						}
					}
				}
			}
		}
	}

	Component {
		id: aboutPage

		Kirigami.AboutPage {
			aboutData: AboutType.aboutData
		}
	}
}