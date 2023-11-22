import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.19 as Kirigami

import org.tulpenkiste.kirigami64

Kirigami.ScrollablePage {
    id: displaySheet
	
	actions: []

	Connections {
		target: Backend
		onBuildCountModified: {
			view.model = Backend.buildCountValue()
		}
	}

	Kirigami.CardsListView {
		id: view
		model: Backend.buildCountValue()
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
                        source: Backend.buildConfigSpecificDataGet(modelData, 2)
						Layout.fillHeight: true
						Layout.maximumHeight: Kirigami.Units.iconSizes.huge
						Layout.preferredWidth: height
					}
					ColumnLayout {
						Kirigami.Heading {
							Layout.fillWidth: true
							level: 2
                            text: Backend.buildConfigSpecificDataGet(modelData, 0)
						}
						Kirigami.Separator {
							Layout.fillWidth: true
						}
						Controls.Label {
							Layout.fillWidth: true
							wrapMode: Text.WordWrap
                            text: Backend.buildConfigSpecificDataGet(modelData, 1)
						}
					}
					ColumnLayout {
						Layout.maximumWidth: 200
						Controls.Button{
							Layout.fillWidth: true
							text: i18n("Add Shortcuts")
							//icon.name: "desktop"
							onClicked: [Backend.setBuildSelected(modelData), Backend.addShortcut(Backend.buildList(modelData))]
						}
						Controls.Button {
							Layout.fillWidth: true
							text: i18n("View Repository Options")
							onClicked: [Backend.setBuildSelected(modelData), selectedBuildSheet.updateTitle(), selectedBuildSheet.open()]
						}
					}
				}
			}
		}
	}
}
