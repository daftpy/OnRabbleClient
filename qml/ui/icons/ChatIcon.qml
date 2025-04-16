// Generated from SVG file chat-bubble.svg
import QtQuick
import QtQuick.Shapes
import OnRabbleClient
import QtQuick.Layouts

Item {
    id: root
    required property string color
    implicitWidth: 15
    implicitHeight: 15
    transform: [
        Scale { xScale: width / 15; yScale: height / 15 }
    ]
    Shape {
        preferredRendererType: Shape.CurveRenderer
        ShapePath {
            strokeColor: "transparent"
            fillColor: root.color
            fillRule: ShapePath.OddEvenFill
            PathSvg { path: "M 12.5 3 L 2.5 3.00002 C 1.67157 3.00002 1 3.6716 1 4.50002 L 1 9.50003 C 1 10.3285 1.67157 11 2.5 11 L 7.50003 11 C 7.63264 11 7.75982 11.0527 7.85358 11.1465 L 10 13.2929 L 10 11.5 C 10 11.2239 10.2239 11 10.5 11 L 12.5 11 C 13.3284 11 14 10.3285 14 9.50003 L 14 4.5 C 14 3.67157 13.3284 3 12.5 3 M 2.49999 2.00002 L 12.5 2 C 13.8807 2 15 3.11929 15 4.5 L 15 9.50003 C 15 10.8807 13.8807 12 12.5 12 L 11 12 L 11 14.5 C 11 14.7022 10.8782 14.8845 10.6913 14.9619 C 10.5045 15.0393 10.2894 14.9965 10.1464 14.8536 L 7.29292 12 L 2.5 12 C 1.11929 12 0 10.8807 0 9.50003 L 0 4.50002 C 0 3.11931 1.11928 2.00003 2.49999 2.00002 " }
        }
    }
}
