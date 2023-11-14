import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Dialogs
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard

import org.tulpenkiste.kirigami64

FormCard.FormCardPage {
	title: i18nc("@title:window", "Build Options")

	FormCard.FormHeader {
		title: i18n("Region")
		visible: Qt.platform.os !== "android"
	}

	FormCard.FormCard {
		FormCard.FormSectionText {
			text: i18n("Note that anything you attempt to compile requires a legally acquired ROM matching a given hash.")
		}
		FormCard.FormComboBoxDelegate {
			text: i18n("ROM Region")

			model: ["US", "EU", "JP"]
			currentIndex: Backend.currentRegion()
			onCurrentIndexChanged: Backend.setCurrentRegion(currentIndex)
		}
	}

	FormCard.FormHeader {
		title: i18n("ROM paths")
		visible: Qt.platform.os !== "android"
	}

	FormCard.FormCard {
		FormCard.AbstractFormDelegate {
			Layout.fillWidth: true

			contentItem: ColumnLayout {
				FileDialog {
					id: fileDialog

					property int index: 0;
					property var textInput: null;

					onAccepted: {
						var path = selectedFile.toString();

						// remove prefixed "file:///"
						path = path.replace(/^(file:\/{2})/,"");

						// unescape html codes like '%23' for '#'
						var cleanPath = decodeURIComponent(path);

						textInput.text = cleanPath
						Backend.setROMPath(index, cleanPath)
					}

					function getPath(index: int, textInput) {
						this.index = index;
						this.textInput = textInput;

						//console.log(currentFolder)

						if (textInput.text == "")
							currentFolder = "file://" + (Qt.platform.os == "windows" ? "/" : "")
						else {
							var pathSplit = textInput.text.split("/")
							pathSplit.pop()

							var newStr = ""

							for (var i in pathSplit) {
								if (i == 0) continue;
								//console.log(pathSplit[i])
								newStr += "/" + pathSplit[i]
							}

							this.currentFolder = "file://" + (Qt.platform.os == "windows" ? "/" : "") + newStr
						}

						console.log("Current folder set to " + this.currentFolder)

						open();
					}
				}

				FormCard.FormSectionText {
					text: i18n("USA")
				}

				RowLayout {
					Kirigami.ActionTextField {
						id: romPathUS

						Layout.fillWidth: true

						placeholderText: i18n("Path...")
						text: Backend.getROMPath(0)

						onTextEdited: [console.log("US Path updated to: " + romPathUS.text), Backend.setROMPath(0, romPathUS.text)]
					}

					QQC2.Button {
						id: romPathUSPrompter
						property var fileDialog: null;
						icon.name: "folder-symbolic";

						onClicked: {
							fileDialog.getPath(0, romPathUS);
						}

						QQC2.ToolTip {
							text: i18n("Opens a file dialog to find the American ROM file")
							delay: Kirigami.Units.toolTipDelay
						}
					}
				}

				FormCard.FormSectionText {
					text: i18n("EU")
				}

				RowLayout {
					Kirigami.ActionTextField {
						id: romPathEU

						Layout.fillWidth: true

						placeholderText: i18n("Path...")
						text: Backend.getROMPath(1)

						onTextEdited: [console.log("EU Path updated to: " + romPathEU.text), Backend.setROMPath(1, romPathEU.text)]
					}

					QQC2.Button {
						id: romPathEUPrompter
						property var fileDialog: null;
						icon.name: "folder-symbolic";

						onClicked: {
							fileDialog.getPath(1, romPathEU);
						}

						QQC2.ToolTip {
							text: i18n("Opens a file dialog to find the European ROM file")
							delay: Kirigami.Units.toolTipDelay
						}
					}
				}

				FormCard.FormSectionText {
					text: i18n("JP")
				}

				RowLayout {
					Kirigami.ActionTextField {
						id: romPathJP

						Layout.fillWidth: true

						placeholderText: i18n("Japanese ROM Path...")
						text: Backend.getROMPath(2)

						onTextEdited: [console.log("JP Path updated to: " + romPathJP.text), Backend.setROMPath(2, romPathJP.text)]
					}

					QQC2.Button {
						id: romPathJPPrompter
						property var fileDialog: null;
						icon.name: "folder-symbolic";

						onClicked: {
							fileDialog.getPath(2, romPathJP);
						}

						QQC2.ToolTip {
							text: i18n("Opens a file dialog to find the Japanese ROM file")
							delay: Kirigami.Units.toolTipDelay
						}
					}
				}
			}
		}
	}
}