import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.19 as Kirigami

import org.azreigh.Kirigami64 0.1

Kirigami.ScrollablePage {
	id: configSheet

	GridLayout {
		ColumnLayout {
			id: cloneSheet

			Kirigami.FormLayout {
				id: build
				Layout.fillWidth: true

				Controls.ComboBox {
					id: repoSel
					Kirigami.FormData.label: "Repository:"
					model: Backend.sourceGroups()
				}

				Controls.Button {
					text: "Clone repository data"
					onClicked: [Backend.clone(repoSel.currentText)/*, cloneProgressSheet.open()*/, showPassiveNotification("Please check the terminal to view cloning progress."), Backend.buildFind(0)]
				}
			}
		}
	}
}