import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard

import org.tulpenkiste.kirigami64

FormCard.FormCardPage {
	title: i18nc("@title:window", "General Launcher Settings")

	FormCard.FormHeader {
		title: i18n("General settings")
		visible: Qt.platform.os !== "android"
	}

	FormCard.FormCard {
		FormCard.AbstractFormDelegate {
			Layout.fillWidth: true

			contentItem: RowLayout {
				FormCard.FormSectionText {
					text: i18n("Edit Sources")
				}
				
				QQC2.Button {
					id: editSources
					text: i18n("Edit Sources")
					icon.name: "document-edit"
					display: QQC2.AbstractButton.IconOnly
					onClicked: [showPassiveNotification("Opening editor..."), Backend.openSources()]

					QQC2.ToolTip {
						text: "Edits the file used for git sources. Requires a restart to take effect."
						delay: Kirigami.Units.toolTipDelay
					}
				}
			}
		}
	}
}