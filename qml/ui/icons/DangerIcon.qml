// Generated from SVG file exclamation-triangle.svg
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
            PathSvg { path: "M 8.4449 0.608765 C 8.0183 -0.107015 6.9817 -0.107015 6.55509 0.608766 L 0.161178 11.3368 C -0.275824 12.07 0.252503 13 1.10608 13 L 13.8939 13 C 14.7475 13 15.2758 12.07 14.8388 11.3368 L 8.4449 0.608765 M 7.4141 1.12073 C 7.45288 1.05566 7.54712 1.05566 7.5859 1.12073 L 13.9798 11.8488 C 14.0196 11.9154 13.9715 12 13.8939 12 L 1.10608 12 C 1.02849 12 0.980454 11.9154 1.02018 11.8488 L 7.4141 1.12073 M 6.8269 4.48611 C 6.81221 4.10423 7.11783 3.78663 7.5 3.78663 C 7.88217 3.78663 8.18778 4.10423 8.1731 4.48612 L 8.01921 8.48701 C 8.00848 8.766 7.7792 8.98664 7.5 8.98664 C 7.2208 8.98664 6.99151 8.766 6.98078 8.48701 L 6.8269 4.48611 M 8.24989 10.476 C 8.24989 10.8902 7.9141 11.226 7.49989 11.226 C 7.08567 11.226 6.74989 10.8902 6.74989 10.476 C 6.74989 10.0618 7.08567 9.72599 7.49989 9.72599 C 7.9141 9.72599 8.24989 10.0618 8.24989 10.476 " }
        }
    }
}
