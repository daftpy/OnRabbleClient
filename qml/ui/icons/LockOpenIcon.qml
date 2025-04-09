// Generated from SVG file lock-open-1.svg
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
            PathSvg { path: "M 7.4986 0 C 6.3257 0 5.36107 0.38943 4.73753 1.19361 C 4.23745 1.83856 4 2.68242 4 3.63325 L 5 3.63325 C 5 2.84313 5.19691 2.23312 5.5278 1.80636 C 5.91615 1.30552 6.55152 1 7.4986 1 C 8.35683 1 8.96336 1.26502 9.35846 1.68623 C 9.75793 2.11211 10 2.76044 10 3.63601 L 10 6 L 3 6 C 2.44772 6 2 6.44772 2 7 L 2 13 C 2 13.5523 2.44772 14 3 14 L 12 14 C 12.5523 14 13 13.5523 13 13 L 13 7 C 13 6.44771 12.5523 6 12 6 L 11 6 L 11 3.63601 C 11 2.58135 10.7065 1.66167 10.0878 1.0021 C 9.46477 0.337871 8.57061 0 7.4986 0 M 3 7 L 12 7 L 12 13 L 3 13 L 3 7 " }
        }
    }
}
