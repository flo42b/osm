/**
 *  OSM
 *  Copyright (C) 2020  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1
import "elements"
import QtQml.Models 2.12

Item {
    id: viewPreset
    property var dataObject
    //property int viewPresetIndex: 0

    ColumnLayout{
        anchors.fill: parent
        spacing: 0

        RowLayout{
            spacing: 10
            //NameField {
            TextField{
                id:presetNameTextInput
                text: qsTr("");
                Layout.minimumWidth: 100
                Layout.alignment: Qt.AlignVCenter
            }
            Button {
                text: qsTr("New");
                onClicked: {
                    applicationSettings.copyGroup("layout/charts", qsTr("viewPreset/") + presetNameTextInput.text);
                    viewPresetViewList.model = applicationSettings.getGroup("viewPreset").getChildGroups();
                }
                implicitWidth: 75
                font.capitalization: Font.AllLowercase
                ToolTip.visible: hovered
                ToolTip.text: qsTr("apply estimated delay")
            }
            DropDown {
                id: viewPresetViewList
                implicitWidth: 170
                model: []
                Component.onCompleted: {
                    model = applicationSettings.getGroup("viewPreset").getChildGroups();
                }
            }

            Button {
                text: "Select"
                font.family: "Osm"
                onClicked: {
                    var PresetList = applicationSettings.getGroup("viewPreset").getChildGroups();
                    var selectedPreset = PresetList[viewPresetViewList.currentIndex];

                    charts.count = applicationSettings.value("viewPreset/" + selectedPreset + "/count");

                    charts.first.height = applicationSettings.value("viewPreset/" + selectedPreset + "/1/height");
                    charts.first.type = applicationSettings.value("viewPreset/" + selectedPreset + "/1/type");
                    charts.first.xmax = applicationSettings.value("viewPreset/" + selectedPreset + "/1/xmax");
                    charts.first.xmin = applicationSettings.value("viewPreset/" + selectedPreset + "/1/xmin");
                    charts.first.ymax = applicationSettings.value("viewPreset/" + selectedPreset + "/1/ymax");
                    charts.first.ymin = applicationSettings.value("viewPreset/" + selectedPreset + "/1/ymin");
                    charts.first.mode = applicationSettings.value("viewPreset/" + selectedPreset + "/1/mode");
                    charts.first.normalized = applicationSettings.value("viewPreset/" + selectedPreset + "/1/normalized");

                    charts.second.height = applicationSettings.value("viewPreset/" + selectedPreset + "/2/height");
                    charts.second.type = applicationSettings.value("viewPreset/" + selectedPreset + "/2/type");
                    charts.second.xmax = applicationSettings.value("viewPreset/" + selectedPreset + "/2/xmax");
                    charts.second.xmin = applicationSettings.value("viewPreset/" + selectedPreset + "/2/xmin");
                    charts.second.ymax = applicationSettings.value("viewPreset/" + selectedPreset + "/2/ymax");
                    charts.second.ymin = applicationSettings.value("viewPreset/" + selectedPreset + "/2/ymin");
                    charts.second.mode = applicationSettings.value("viewPreset/" + selectedPreset + "/2/mode");
                    charts.second.normalized = applicationSettings.value("viewPreset/" + selectedPreset + "/2/normalized");

                    charts.third.height = applicationSettings.value("viewPreset/" + selectedPreset + "/3/height");
                    charts.third.type = applicationSettings.value("viewPreset/" + selectedPreset + "/3/type");
                    charts.third.xmax = applicationSettings.value("viewPreset/" + selectedPreset + "/3/xmax");
                    charts.third.xmin = applicationSettings.value("viewPreset/" + selectedPreset + "/3/xmin");
                    charts.third.ymax = applicationSettings.value("viewPreset/" + selectedPreset + "/3/ymax");
                    charts.third.ymin = applicationSettings.value("viewPreset/" + selectedPreset + "/3/ymin");
                    charts.third.mode = applicationSettings.value("viewPreset/" + selectedPreset + "/3/mode");
                    charts.third.normalized = applicationSettings.value("viewPreset/" + selectedPreset + "/3/normalized");
                }
            }

            Button {
                text: "Remove"
                font.family: "Osm"
                onClicked: {
                    var PresetList = applicationSettings.getGroup("viewPreset").getChildGroups();
                    var selectedPreset = PresetList[viewPresetViewList.currentIndex];
                    applicationSettings.removeGroup(qsTr("viewPreset/") + selectedPreset);
                    viewPresetViewList.model = applicationSettings.getGroup("viewPreset").getChildGroups();
                }
            }
        }
    }
}
