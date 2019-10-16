import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import Proton.Datas 1.0

Flickable {
    id: root
    property string title: "Spline chart view"
    property int moveLength: 0
    clip: true
    contentHeight: contentPane.height + 10

    onMovingChanged: {
        console.log(contentY)
        console.log(originY)
    }

    onMovementStarted: {

    }
    onMovementEnded: {
        console.log(contentY)
        console.log(originY)
        if (contentPane.y < 0) {
            extendSettings.from = -root.height + 100
            extendSettings.to = 0
            extendSettings.start()
        } else {
            extendSettings.from = 0
            extendSettings.to = -root.height + 100
            extendSettings.start()
        }
    }

    DataItems {
        id: trending_datas
        datas: [
            DataItem {
                name: "Average Speed"
                value: 0
            },
            DataItem {
                name: "Average Length"
                value: 100.20
            }
        ]
    }

    DataItems {
        id: refLines_datas
        datas: [
            DataItem {
                name: "Upper Limit"
                value: 15
            },
            DataItem {
                name: "Middle Limit"
                value: 5
            },
            DataItem {
                name: "Lower Limit"
                value: 0
            }
        ]
    }

    NumberAnimation {
        id: extendSettings
        target: contentPane
        properties: "y"
        duration: 200
        easing.type: Easing.InOutQuad
        from: 0
        to: root.height - 100
    }

    NumberAnimation {
        id: extendSettings1
        target: contentPane
        properties: "y"
        duration: 200
        easing.type: Easing.InOutQuad
        from: root.height - 100
        to: 0
    }

    Pane {
        id: contentPane
        width: parent.width
        padding: 5
        y: -root.height + 100
        Column {
            id: column
            y: 0
            anchors.fill: parent
            spacing: 0
            Item {
                id: paneSettins
                width: parent.width
                height: root.height - 100
                Rectangle {
                    color: "pink"
                    Layout.margins: 10
                    radius: 10
                    anchors.fill: parent
                }
            }

            CustomLegend {
                id: customLegend
                width: parent.width
                height: 60
                title: "Wheel of fortune"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            ChartView {
                id: chartView
                width: parent.width
                height: root.height - 60
                legend.visible: false
                antialiasing: true
                onSeriesAdded: {
                    if (series.name !== "")
                        customLegend.addSeries(series.name, series.color)
                }

                DateTimeAxis {
                    id: dxAxis
                    titleText: "Date Time"
                    format: "HH:mm:ss"
                    tickCount: 10
                }
            }

            MultiPointTouchArea {
                anchors.fill: parent
                mouseEnabled: true
                minimumTouchPoints: 1
                maximumTouchPoints: 2
                touchPoints: [
                    TouchPoint {
                        id: point1
                    },
                    TouchPoint {
                        id: point2
                    }
                ]
                Rectangle {
                    width: 30
                    height: 30
                    color: "green"
                    x: point1.x
                    y: point1.y
                }

                Rectangle {
                    width: 30
                    height: 30
                    color: "yellow"
                    x: point2.x
                    y: point2.y
                }
                onTouchUpdated: {
                    moveLength = point1.y - point1.startY
                    console.log(moveLength)
                }
            }
        }
    }

    function createSeries(name, ischange) {
        var yAxis = Qt.createQmlObject('import QtCharts 2.0;ValueAxis{}',
                                       chartView)
        yAxis.titleText = name

        var newSeries = chartView.createSeries(ChartView.SeriesTypeLine, name,
                                               dxAxis, yAxis)
        newSeries.useOpenGL = true
        if (ischange)
            trendingTimer.change(newSeries, yAxis)
    }

    function createRefes(name, val, flag) {
        var yAxis = Qt.createQmlObject(
                    'import QtCharts 2.0;ValueAxis{min:0;max:1;visible:false}',
                    chartView)

        var xAxis = Qt.createQmlObject(
                    'import QtCharts 2.0;ValueAxis{min:0;max:1;visible:false}',
                    chartView)

        var newSeries = chartView.createSeries(ChartView.SeriesTypeLine, "",
                                               xAxis, yAxis)
        newSeries.append(0, val)
        newSeries.append(1, val)
        newSeries.useOpenGL = true
        if (flag) {
            newSeries.color = "black"
        } else {
            newSeries.color = "red"
            newSeries.style = Qt.DashDotLine
        }
    }

    TrendingTimer {
        id: trendingTimer
        interval: 100
        timeLength: 10
        onLoad: {
            var i = 0
            for (; i < datas.length; i++) {
                if (flag > 0) {
                    createRefes(datas[i], (i + 1) * 0.25, i === 1)
                } else {
                    createSeries(datas[i], i > 0)
                }
            }
        }
        onRefsUpdate: {
            var i = 0
            for (; i < datas.length; i++) {
                var item = chartView.series(i)
                item.removePoints(0, 2)
                item.append(0, datas[i])
                item.append(1, datas[i])
            }
        }

        onDataUpdate: {
            var i = 0
            for (; i < datas.length; i++) {
                var item = chartView.series(i + 3)
                item.append(xTime, datas[i])
            }
            i = 0
            for (; i < datas.length; i++) {
                trendingTimer.setRange(chartView.series(i + 3))
            }
        }
    }

    Component.onCompleted: {
        trendingTimer.setRefLines(refLines_datas)
        trendingTimer.start(trending_datas)
    }
}

/*##^## Designer {
    D{i:0;height:300;width:600}
}
 ##^##*/

