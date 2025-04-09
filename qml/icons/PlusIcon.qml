// Generated from SVG file plus.svg
import QtQuick
import QtQuick.Shapes
import OnRabbleClient

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
            PathSvg { path: "M 8 2.75 C 8 2.47386 7.77614 2.25 7.5 2.25 C 7.22386 2.25 7 2.47386 7 2.75 L 7 7 L 2.75 7 C 2.47386 7 2.25 7.22386 2.25 7.5 C 2.25 7.77614 2.47386 8 2.75 8 L 7 8 L 7 12.25 C 7 12.5261 7.22386 12.75 7.5 12.75 C 7.77614 12.75 8 12.5261 8 12.25 L 8 8 L 12.25 8 C 12.5261 8 12.75 7.77614 12.75 7.5 C 12.75 7.22386 12.5261 7 12.25 7 L 8 7 L 8 2.75 " }
        }
    }
}
