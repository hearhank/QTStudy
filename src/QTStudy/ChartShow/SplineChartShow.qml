import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import Proton.Datas 1.0

Page {
    title: "Splie Chart"

    property int __activeIndex: 0
    property real __intervalCoefficient: 0
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
    Column {
        id: column
        anchors.fill: parent
        spacing: 0
        CustomLegend {
            width: parent.width
            height: 50
            title: "Wheel of fortune"
            anchors.horizontalCenter: parent.horizontalCenter
            id: customLegend
        }

        ChartView {
            id: chartView
            width: parent.width
            height: parent.height - customLegend.height
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
            //            SplineSeries{
            //                color: "red"
            //                useOpenGL: true
            //                capStyle: Qt.DashDotLine
            //            }
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
