import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.19 as Kirigami

import org.azreigh.Kirigami64 0.2

Kirigami.ScrollablePage {
	id: configureBuildSheet

	title: i18nc("@title:window", "Configure " + Backend.buildList(Backend.buildSelected))

	GridLayout {
		ColumnLayout {
			id: configBuild

			Kirigami.FormLayout {
				id: build
				Layout.fillWidth: true

				Controls.TextField {
					id: nameInp
					Kirigami.FormData.label: "Name:"
				}

				Controls.TextField {
					id: descInp
					Kirigami.FormData.label: "Description:"
				}

				Controls.TextField {
					id: iconInp
					Kirigami.FormData.label: "Icon:"
				}

				Controls.Button {
					text: "Clone repository data"
					onClicked: [Backend.buildList(Backend.buildSelected, nameInp.currentText, descInp.currentText, iconInp.currentText),/*, cloneProgressSheet.open()*/, showPassiveNotification("Updated config for " + Backend.buildList(Backend.buildSelected) + "."), Backend.buildFind(0)]
				}
			}
		}
	}
}