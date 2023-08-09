import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.19 as Kirigami

import org.tulip.Kirigami64 0.2

Kirigami.ScrollablePage {
	id: configureBuildSheet

	title: i18nc("@title:window", "Configure " + Backend.buildList(Backend.buildSelected))

	function updateValues() {
		nameInp.text = Backend.buildConfigSpecificDataGet(Backend.buildSelected, 0);
		descInp.text = Backend.buildConfigSpecificDataGet(Backend.buildSelected, 1);
		iconInp.text = Backend.buildConfigSpecificDataGet(Backend.buildSelected, 2);
		iconValidate.source = iconInp.text;
	}

	RowLayout {
		ColumnLayout {
			id: configBuild

			Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
			Layout.maximumWidth: 450.0

			Kirigami.Heading {
				Layout.fillWidth: true
				level: 2
				type: Kirigami.Heading.Type.Primary
				text: "Repository Configuration"
				horizontalAlignment: Text.AlignHCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
			}

			Kirigami.Heading {
				Layout.fillWidth: true
				level: 3
				type: Kirigami.Heading.Type.Secondary
				text: "Settings"
				horizontalAlignment: Text.AlignHCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
			}

			RowLayout {
				Kirigami.Label {
					text: "Display Name in launcher:"
				}

				Controls.TextField {
					id: nameInp
					placeholderText: "Name:"
				}
			}

			RowLayout {
				Kirigami.Label {
					text: "Description in launcher:"
				}

				Controls.TextField {
					id: descInp
					placeholderText: "Description:"
				}
			}

			RowLayout {
				Kirigami.Label {
					text: "Icon (name or path):"
				}

				Controls.TextField {
					id: iconInp
					onTextEdited: iconValidate.source = iconInp.text
				}

				Kirigami.Icon {
					id: iconValidate
					source: ""
				}
			}

			RowLayout {
				id: romLayout
				property int currentRegion: 0
				Kirigami.Label {
					text: "ROM Region: "
				}
				Controls.RadioButton {
					text: "Default"
					checked: true
					onCheckedChanged: romLayout.currentRegion = 0
				}
				Controls.RadioButton {
					text: "US"
					onCheckedChanged: romLayout.currentRegion = 1
				}
				Controls.RadioButton {
					text: "EU"
					onCheckedChanged: romLayout.currentRegion = 2
				}
				Controls.RadioButton {
					text: "JP"
					onCheckedChanged: romLayout.currentRegion = 3
				}
			}

			Kirigami.Heading {
				Layout.fillWidth: true
				level: 3
				type: Kirigami.Heading.Type.Secondary
				text: "Confirm"
				horizontalAlignment: Text.AlignHCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
			}

			Controls.Button {
				text: "Set repository configuration"
				onClicked: [Backend.modifyConfig(nameInp.text, descInp.text, iconInp.text, romLayout.currentRegion), showPassiveNotification("Updated config for " + Backend.buildList(Backend.buildSelected) + "."), Backend.buildFind(0)]
			}
		}
	}
}
