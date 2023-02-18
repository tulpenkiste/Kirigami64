import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.19 as Kirigami

import org.tulip.Kirigami64 0.2

Kirigami.ScrollablePage {
	id: configSheet

	RowLayout {
		ColumnLayout {
			Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

			Layout.maximumWidth: 450.0

			Kirigami.Heading {
				Layout.fillWidth: true
				level: 2
				type: Kirigami.Heading.Type.Primary
				text: "Sources"

				horizontalAlignment: Text.AlignHCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
			}

			Controls.Label {
				Layout.fillWidth: true
				wrapMode: Text.WordWrap
				text: "This section is to modify application sources."
			}

			Controls.ToolButton {
				Layout.alignment: Qt.AlignLeft
				Layout.columnSpan: 2
				text: i18n("Modify sources in text editor")
				icon.name: "document-edit"
				flat: false
				onClicked: [showPassiveNotification("Opening editor..."), Backend.openSources()]
			}

			Kirigami.Heading {
				Layout.fillWidth: true
				level: 2
				type: Kirigami.Heading.Type.Primary
				text: "Launch Options"
				horizontalAlignment: Text.AlignHCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
			}

			Controls.Label {
				Layout.fillWidth: true
				wrapMode: Text.WordWrap
				text: "Configure launch settings"
			}

			Controls.Switch {
				Layout.alignment: Qt.AlignLeft
				Layout.columnSpan: 2
				checkable: true
				checked: Backend.useMangoHud
				onCheckedChanged: Backend.useMangoHud = checked
				text: i18n("Use MangoHud")
			}

			Kirigami.Heading {
				Layout.fillWidth: true
				level: 2
				type: Kirigami.Heading.Type.Primary
				text: "Build"
				horizontalAlignment: Text.AlignHCenter
			}

			Kirigami.Separator {
				Layout.fillWidth: true
			}

			Controls.Label {
				Layout.fillWidth: true
				wrapMode: Text.WordWrap
				text: "Configure build settings here (STILL TODO)"
			}
		}
	}
}
