// Generated from SVG file paper-plane.svg
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
            PathSvg { path: "M 1.20308 1.04312 C 1.00481 0.954998 0.772341 1.0048 0.627577 1.16641 C 0.482813 1.32802 0.458794 1.56455 0.568117 1.75196 L 3.92115 7.50002 L 0.568117 13.2481 C 0.458794 13.4355 0.482813 13.672 0.627577 13.8336 C 0.772341 13.9952 1.00481 14.045 1.20308 13.9569 L 14.7031 7.95693 C 14.8836 7.87668 15 7.69762 15 7.50002 C 15 7.30243 14.8836 7.12337 14.7031 7.04312 L 1.20308 1.04312 M 4.84553 7.10002 L 2.21234 2.586 L 13.2689 7.50002 L 2.21234 12.414 L 4.84552 7.90002 L 9 7.90002 C 9.22092 7.90002 9.4 7.72094 9.4 7.50002 C 9.4 7.27911 9.22092 7.10002 9 7.10002 L 4.84553 7.10002 " }
        }
    }
}
