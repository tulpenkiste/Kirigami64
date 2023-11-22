import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard

import org.tulpenkiste.kirigami64

FormCard.FormCardPage {
	title: i18nc("@title:window", "General Launcher Settings")

	FormCard.FormHeader {
		title: i18n("Repository Sources")
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

	FormCard.FormHeader {
		title: i18n("Shortcut Creation")
		visible: Qt.platform.os !== "android"
	}

	FormCard.FormCard {
		FormCard.FormCheckDelegate {
			text: i18n("Applicaiton Menu Shortcut")
			description: i18n("Whether to add shortcuts to the application menu")
			checked: Backend.allowingShortcut(0)
			visible: Qt.platform.os == "linux"

			onToggled: {
				Backend.setAllowShortcut(0, checked)
			}
		}

		FormCard.FormCheckDelegate {
			text: i18n("Desktop Shortcut")
			description: i18n("Whether to add shortcuts to the desktop")
			checked: Backend.allowingShortcut(1)
			visible: Qt.platform.os == "linux"

			onToggled: {
				Backend.setAllowShortcut(1, checked)
			}
		}
	}
}