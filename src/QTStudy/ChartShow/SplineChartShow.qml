import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import Proton.Datas 1.0

Page {
    id:root
    title: "Splie Chart"

    //    property int __activeIndex: 0
    //    property real __intervalCoefficient: 0
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
        id:extendSettings
        target: paneSettins
        properties: "height"
        duration: 200
        easing.type: Easing.InOutQuad
        from:0
        to:120
    }
    NumberAnimation {
        id:extendSettings1
        target: paneSettins
        properties: "height"
        duration: 200
        easing.type: Easing.InOutQuad
        from:120
        to:0
    }
        Column {
            id: column
            y:0
            width: parent.width
            height: root.height-paneSettins.height
            spacing: 0
            Column {
                id: paneSettins
                width: parent.width
                height: 0
                Rectangle {
                    color: "pink"
                    Layout.margins: 10
                    radius: 10
                    anchors.fill: parent
                }


            }
            Item{
                width: parent.width
                height: 50
                CustomLegend {
                     id: customLegend
                    width: parent.width
                    height: 50
                    title: "Wheel of fortune"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            Button{
                anchors.right: parent.right
                Layout.rightMargin: 10
                text: "Show Settings"
                onClicked: {
                    if(paneSettins.height>0){
                        extendSettings1.start()
                         text="Show Settings"
                    }else{
                        extendSettings.start()
                        text="Hidden Settings"
                    }
                }
            }
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
            }

//            MultiPointTouchArea{
//                anchors.fill: parent
//                mouseEnabled: true
//                minimumTouchPoints: 1
//                maximumTouchPoints: 2
//                touchPoints: [
//                    TouchPoint{
//                        id:point1
//                        onPressedChanged: {
//                            if(column.y<100)
//                                column.y=0
//                            console.log(column.y)
//                        }
//                    },
//                    TouchPoint{
//                        id:point2
//                    }
//                ]
//                Rectangle {
//                    id:rec1
//                  width: 30; height: 30
//                  color: "green"
//                  x: point1.x
//                  y: point1.y
//              }

//              Rectangle {
//                  width: 30; height: 30
//                  color: "yellow"
//                  x: point2.x
//                  y: point2.y
//              }
//            onTouchUpdated: {
//                column.y =point1.y-point1.startY
//                if(column.y>100)
//                {
//                    rec1.color="blue"
//                    paneSettins.visible=true
//                }else{
//                    rec1.color="red"
//                    paneSettins.visible=false
//                }
//            }
//        }

        }


    function createSeries(name,ischange) {
        var yAxis = Qt.createQmlObject('import QtCharts 2.0;ValueAxis{}',
                                       chartView)
        yAxis.titleText = name

        var newSeries = chartView.createSeries(ChartView.SeriesTypeLine, name,
                                               dxAxis, yAxis)
        newSeries.useOpenGL = true
        if (ischange)
            trendingTimer.change(newSeries, yAxis)
    }

    function createRefes(name,val,flag) {
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

