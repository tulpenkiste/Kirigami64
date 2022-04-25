// Includes relevant modules used by the QML
import QtQuick 2.6
import QtQuick.Controls 2.0 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.13 as Kirigami


// Base element, provides basic features needed for all kirigami applications
Kirigami.ApplicationWindow {
	// ID provides unique identifier to reference this element
	id: root

	// Window title
	// i18nc is useful for adding context for translators, also lets strings be changed for different languages
	title: i18nc("@title:window", "Kirigami64")

	globalDrawer: Kirigami.GlobalDrawer {
		title: i18n("Kirigami64")
		titleIcon: "kde"

		actions: [
			Kirigami.Action {
				text: "Play"
				icon.name: "media-playback-start"
			},
			Kirigami.Action {
				text: "Build"
				icon.name: "run-build"
			}/*,
			Kirigami.Action {
                text: i18n("About")
                icon.name: "help-about"
                onTriggered: pageStack.layers.push(aboutPage)
            }*/
		]
	}

	/*Component {
        id: aboutPage

        Kirigami.AboutPage {
            aboutData: AboutType.aboutData
        }
    }*/

	// Initial page to be loaded on app load
	pageStack.initialPage: Kirigami.Page {

		/*actions.main: Kirigami.Action {
			id: addAction
			text: i18nc("@action:button", "About")
			onTriggered: aboutSheet.open()
		}*/
	}
	/*Kirigami.OverlaySheet {
		id: aboutSheet
		header: Kirigami.Heading {
			text: i18nc("@title:window", "About")
		}
		Kirigami.FormLayout {
			Controls.Label {
				anchors.centerIn: parent
            	text: i18n("License goes here.")
			}
		}
	}*/
}