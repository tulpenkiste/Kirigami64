import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard

import org.tulpenkiste.kirigami64

FormCard.FormCardPage {
	title: i18nc("@title:window", "Launch Options")

	FormCard.FormHeader {
		title: i18n("Launch Options")
		visible: Qt.platform.os !== "android"
	}

	FormCard.FormCard {
		FormCard.FormCheckDelegate {
			text: i18n("Use MangoHud")
			description: i18n("Whether to utilise MangoHud, a performance overlay for applications and games")
			checked: Backend.usingMangoHud()
			visible: Qt.platform.os == "linux"
			onToggled: {
				console.log(Qt.platform.os)
				Backend.setUsingMangoHud(checked)
			}
		}
		FormCard.FormCheckDelegate {
			text: i18n("Use FeralInteractive GameMode")
			description: i18n("Whether to utilise GameMode, a daemon/library that requests optimisations")
			checked: Backend.usingGameMode()
			visible: Qt.platform.os == "linux"
			onToggled: {
				console.log(Qt.platform.os)
				Backend.setUsingGameMode(checked)
			}
		}
	}

	/*
	Controls.Switch {
		Layout.alignment: Qt.AlignLeft
		Layout.columnSpan: 2
		checkable: true
		checked: Backend.useMangoHud
		onCheckedChanged: Backend.useMangoHud = checked
		text: i18n("Use MangoHud")
	}

	Controls.Switch {
		Layout.alignment: Qt.AlignLeft
		Layout.columnSpan: 2
		checkable: true
		checked: Backend.useGameMode
		onCheckedChanged: Backend.useGameMode = checked
		text: i18n("Use GameMode")
	}
	*/
}