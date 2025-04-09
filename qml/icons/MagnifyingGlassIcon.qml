// Generated from SVG file magnifying-glass.svg
import QtQuick
import QtQuick.Shapes

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
            PathSvg { path: "M 10 6.5 C 10 8.433 8.433 10 6.5 10 C 4.567 10 3 8.433 3 6.5 C 3 4.567 4.567 3 6.5 3 C 8.433 3 10 4.567 10 6.5 M 9.30884 10.0159 C 8.53901 10.6318 7.56251 11 6.5 11 C 4.01472 11 2 8.98528 2 6.5 C 2 4.01472 4.01472 2 6.5 2 C 8.98528 2 11 4.01472 11 6.5 C 11 7.56251 10.6318 8.53901 10.0159 9.30884 L 12.8536 12.1464 C 13.0488 12.3417 13.0488 12.6583 12.8536 12.8536 C 12.6583 13.0488 12.3417 13.0488 12.1464 12.8536 L 9.30884 10.0159 " }
        }
    }
}
