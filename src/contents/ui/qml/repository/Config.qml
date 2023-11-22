import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard

import org.tulpenkiste.kirigami64

FormCard.FormCardPage {
	title: i18nc("@title:window", "Configure %1", Backend.buildList(Backend.buildSelectedValue()))

	FormCard.FormHeader {
		title: i18n("Repository Configuration")
		visible: Qt.platform.os !== "android"
	}

	FormCard.FormCard {
		FormCard.AbstractFormDelegate {
			Layout.fillWidth: true

			contentItem: ColumnLayout {
				FormCard.FormSectionText {
					text: i18n("Display")
				}

				Kirigami.ActionTextField {
					id: displayName

					Layout.fillWidth: true

					placeholderText: i18n("Display Name...")
					text: Backend.buildConfigSpecificDataGet(Backend.buildSelectedValue(), 0);
				}

				Kirigami.ActionTextField {
					id: description

					Layout.fillWidth: true

					placeholderText: i18n("Description...")
					text: Backend.buildConfigSpecificDataGet(Backend.buildSelectedValue(), 1);
				}

				
				RowLayout {
					Kirigami.Icon {
						id: iconPreview
						source: Backend.buildConfigSpecificDataGet(Backend.buildSelectedValue(), 2);
					}

					Kirigami.ActionTextField {
						id: iconPath

						Layout.fillWidth: true

						placeholderText: i18n("Icon Path...")
						text: Backend.buildConfigSpecificDataGet(Backend.buildSelectedValue(), 2);
						onTextEdited: iconPreview.source = text
					}

					QQC2.Button {
						id: iconPathPrompter
						property var fileDialog: null;
						icon.name: "folder-symbolic";

						onClicked: {
							fileDialog.getPath(0, romPathUS);
						}

						QQC2.ToolTip {
							text: i18n("Opens a file dialog to find the desired build icon")
							delay: Kirigami.Units.toolTipDelay
						}
					}
				}

				FormCard.FormSectionText {
					text: i18n("Build Region")
				}

				FormCard.FormComboBoxDelegate {
					id: regionDropdown
					text: i18n("ROM Region")

					model: ["Default", "US", "EU", "JP"]
					currentIndex: parseInt(Backend.buildConfigSpecificDataGet(Backend.buildSelectedValue(), 3), 10)
				}

				FormCard.FormSectionText {
					text: i18n("Confirmation")
				}

				QQC2.Button {
					text: i18n("Set repository configuration")
					onClicked: [Backend.modifyConfig(displayName.text, description.text, iconPath.text, regionDropdown.currentIndex), Backend.buildFind(0), closeDialog()]

					QQC2.ToolTip {
						text: i18n("Sets the repository configuration")
						delay: Kirigami.Units.toolTipDelay
					}
				}
			}
		}
	}
}
