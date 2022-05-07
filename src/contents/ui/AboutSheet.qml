import QtQuick 2.15
import org.kde.kirigami 2.19 as Kirigami

import org.azreigh.Kirigami64 0.1

Component {
	id: aboutSheet
	
    Kirigami.AboutPage {
		aboutData: AboutType.aboutData
	}
}