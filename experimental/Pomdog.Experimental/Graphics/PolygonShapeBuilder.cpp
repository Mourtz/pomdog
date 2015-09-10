// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "PolygonShapeBuilder.hpp"
#include "Pomdog/Math/MathHelper.hpp"
#include <cmath>

namespace Pomdog {
//-----------------------------------------------------------------------
PolygonShapeBuilder::PolygonShapeBuilder()
{
    vertices.reserve(MinVertexCount);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::Reset()
{
    if (vertices.capacity() > MaxVertexCount) {
        POMDOG_ASSERT(vertices.size() <= MaxVertexCount);
        vertices.resize(MaxVertexCount);
        vertices.shrink_to_fit();
    }
    vertices.clear();
}
//-----------------------------------------------------------------------
PolygonBatchVertex const* PolygonShapeBuilder::GetData() const noexcept
{
    return vertices.data();
}
//-----------------------------------------------------------------------
std::size_t PolygonShapeBuilder::GetVertexCount() const noexcept
{
    return vertices.size();
}
//-----------------------------------------------------------------------
bool PolygonShapeBuilder::IsEmpty() const noexcept
{
    return vertices.empty();
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawArc(
    Vector2 const& position,
    float radius,
    Radian<float> const& startAngle,
    Radian<float> const& arcAngle,
    std::size_t segments,
    Color const& color)
{
    POMDOG_ASSERT(radius >= 0);
    POMDOG_ASSERT(arcAngle >= 0);
    POMDOG_ASSERT(segments >= 3);

    if (radius <= 0 || segments < 3 || arcAngle <= 0) {
        return;
    }

    POMDOG_ASSERT(radius > 0);
    POMDOG_ASSERT(arcAngle >= 0);
    POMDOG_ASSERT(segments >= 3);

    const auto center = Vector3{position, 0.0f};
    const Radian<float> centralAngle =
        std::min(arcAngle.value, MathConstants<float>::TwoPi()) / segments;

    auto computePoint = [&](std::size_t index){
        auto rad =  startAngle + centralAngle * index;
        auto cos = std::cos(rad.value);
        auto sin = std::sin(rad.value);
        return center + Vector3{radius * Vector2{cos, sin}, 0};
    };

    auto prevPoint = computePoint(0);
    auto colorVector = color.ToVector4();

    for (std::size_t i = 0; i < segments; ++i) {
        auto nextPoint = computePoint(i + 1);
        DrawTriangle(nextPoint, prevPoint, center,
            colorVector, colorVector, colorVector);
        prevPoint = nextPoint;
    }
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawBox(
    Vector3 const& position,
    Vector3 const& scale,
    Color const& color)
{
    DrawBox(position, scale, Vector3{0.0f, 0.0f, 0.0f}, color);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawBox(
    Vector3 const& position,
    Vector3 const& scale,
    Vector3 const& originPivot,
    Color const& color)
{
    Vector3 boxVertices[] = {
        // top
        Vector3(0.0f, 1.0f, 0.0f),
        Vector3(1.0f, 1.0f, 0.0f),
        Vector3(1.0f, 1.0f, 1.0f),
        Vector3(0.0f, 1.0f, 1.0f),

        // bottom
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(1.0f, 0.0f, 0.0f),
        Vector3(1.0f, 0.0f, 1.0f),
        Vector3(0.0f, 0.0f, 1.0f),

        // left
        Vector3(0.0f, 0.0f, 1.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 1.0f, 0.0f),
        Vector3(0.0f, 1.0f, 1.0f),

        // right
        Vector3(1.0f, 0.0f, 1.0f),
        Vector3(1.0f, 0.0f, 0.0f),
        Vector3(1.0f, 1.0f, 0.0f),
        Vector3(1.0f, 1.0f, 1.0f),

        // front
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(1.0f, 0.0f, 0.0f),
        Vector3(1.0f, 1.0f, 0.0f),
        Vector3(0.0f, 1.0f, 0.0f),

        // back
        Vector3(0.0f, 0.0f, 1.0f),
        Vector3(1.0f, 0.0f, 1.0f),
        Vector3(1.0f, 1.0f, 1.0f),
        Vector3(0.0f, 1.0f, 1.0f),
    };

    for (auto & v : boxVertices) {
        v = ((v - originPivot) * scale) + position;
    }

    const auto colorVector = color.ToVector4();
    auto draw = [&](int a, int b, int c) {
        DrawTriangle(
            boxVertices[a],
            boxVertices[b],
            boxVertices[c],
            colorVector,
            colorVector,
            colorVector);
    };

    draw(3, 1, 0);
    draw(2, 1, 3);
    draw(6, 4, 5);
    draw(7, 4, 6);
    draw(11, 9, 8);
    draw(10, 9, 11);
    draw(14, 12, 13);
    draw(15, 12, 14);
    draw(19, 17, 16);
    draw(18, 17, 19);
    draw(22, 20, 21);
    draw(23, 20, 22);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawCircle(
    Vector2 const& position,
    float radius,
    std::size_t segments,
    Color const& color)
{
    POMDOG_ASSERT(segments >= 3);
    POMDOG_ASSERT(radius >= 0);

    DrawCircle(Vector3{position, 0.0f}, radius, segments, color);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawCircle(
    Vector3 const& position,
    float radius,
    std::size_t segments,
    Color const& color)
{
    POMDOG_ASSERT(segments >= 3);
    POMDOG_ASSERT(radius >= 0);

    if (radius <= 0) {
        return;
    }

    if (segments < 3) {
        return;
    }

    POMDOG_ASSERT(radius > 0);
    POMDOG_ASSERT(segments >= 3);

    Radian<float> centralAngle = MathConstants<float>::TwoPi() / segments;
    auto prevPoint = position + Vector3{radius, 0, 0};

    auto colorVector = color.ToVector4();

    for (std::size_t i = 0; i < segments; ++i) {
        auto rad = centralAngle * (i + 1);
        auto cos = std::cos(rad.value);
        auto sin = std::sin(rad.value);
        auto nextPoint = position + Vector3{radius * Vector2{cos, sin}, 0};
        DrawTriangle(nextPoint, prevPoint, position,
            colorVector, colorVector, colorVector);
        prevPoint = nextPoint;
    }
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawLine(
    Vector2 const& start,
    Vector2 const& end,
    Color const& color,
    float weight)
{
    DrawLine(start, end, color, color, weight);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawLine(
    Vector2 const& start,
    Vector2 const& end,
    Color const& startColor,
    Color const& endColor,
    float weight)
{
    auto halfWeight = weight / 2;

    if (halfWeight <= 0) {
        return;
    }

    auto vec = end - start;
    std::swap(vec.X, vec.Y);

    auto a = Vector2::Normalize(vec * Vector2{1, -1}) * halfWeight;
    auto b = Vector2::Normalize(vec * Vector2{-1, 1}) * halfWeight;

    Vector3 p1 = Vector3{start + a, 0.0f};
    Vector3 p2 = Vector3{start + b, 0.0f};
    Vector3 p3 = Vector3{end + b, 0.0f};
    Vector3 p4 = Vector3{end + a, 0.0f};

    DrawTriangle(p1, p2, p3, startColor, startColor, endColor);
    DrawTriangle(p3, p4, p1, endColor, endColor, startColor);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawPolyline(
    std::vector<Vector2> const& points,
    float thickness,
    Color const& color)
{
    if (points.size() < 2) {
        return;
    }

    auto halfThickness = thickness / 2;

    if (halfThickness <= 0) {
        return;
    }

    ///@todo Please reimplementation this function:

    for (std::size_t i = 0; i + 1 < points.size(); ++i) {
        auto & start = points[i];
        auto & end = points[i + 1];

        auto vec = end - start;
        std::swap(vec.X, vec.Y);

        auto a = Vector2::Normalize(vec * Vector2{1, -1}) * halfThickness;
        auto b = Vector2::Normalize(vec * Vector2{-1, 1}) * halfThickness;

        Vector3 p1 = Vector3{start + a, 0.0f};
        Vector3 p2 = Vector3{start + b, 0.0f};
        Vector3 p3 = Vector3{end + b, 0.0f};
        Vector3 p4 = Vector3{end + a, 0.0f};

        DrawTriangle(p1, p2, p3, color, color, color);
        DrawTriangle(p3, p4, p1, color, color, color);
    }
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawRectangle(
    Rectangle const& sourceRect,
    Color const& color)
{
    DrawRectangle(sourceRect, color, color, color, color);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawRectangle(
    Rectangle const& sourceRect,
    Color const& color1,
    Color const& color2,
    Color const& color3,
    Color const& color4)
{
    if (sourceRect.Width <= 0 || sourceRect.Height <= 0) {
        return;
    }

    std::array<Vector3, 4> rectVertices = {
        Vector3(sourceRect.GetLeft(), sourceRect.Y, 0.0f),
        Vector3(sourceRect.GetLeft(), sourceRect.Y + sourceRect.Height, 0.0f),
        Vector3(sourceRect.GetRight(), sourceRect.Y + sourceRect.Height, 0.0f),
        Vector3(sourceRect.GetRight(), sourceRect.Y, 0.0f),
    };

    auto colorVector1 = color1.ToVector4();
    auto colorVector2 = color2.ToVector4();
    auto colorVector3 = color3.ToVector4();
    auto colorVector4 = color4.ToVector4();

    DrawTriangle(
        rectVertices[0], rectVertices[1], rectVertices[2],
        colorVector1, colorVector4, colorVector3);
    DrawTriangle(
        rectVertices[2], rectVertices[3], rectVertices[0],
        colorVector3, colorVector2, colorVector1);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawRectangle(
    Matrix3x2 const& matrix,
    Rectangle const& sourceRect,
    Color const& color)
{
    DrawRectangle(matrix, sourceRect, color, color, color, color);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawRectangle(
        Matrix3x2 const& matrix,
        Rectangle const& sourceRect,
        Color const& color1,
        Color const& color2,
        Color const& color3,
        Color const& color4)
{
    if (sourceRect.Width <= 0 || sourceRect.Height <= 0) {
        return;
    }

    std::array<Vector3, 4> rectVertices = {
        Vector3(sourceRect.GetLeft(), sourceRect.Y, 0.0f),
        Vector3(sourceRect.GetLeft(), sourceRect.Y + sourceRect.Height, 0.0f),
        Vector3(sourceRect.GetRight(), sourceRect.Y + sourceRect.Height, 0.0f),
        Vector3(sourceRect.GetRight(), sourceRect.Y, 0.0f),
    };

    for (auto & vertex: rectVertices) {
        auto vec2 = Vector2::Transform(Vector2{vertex.X, vertex.Y}, matrix);
        vertex.X = vec2.X;
        vertex.Y = vec2.Y;
    }

    auto colorVector1 = color1.ToVector4();
    auto colorVector2 = color2.ToVector4();
    auto colorVector3 = color3.ToVector4();
    auto colorVector4 = color4.ToVector4();

    DrawTriangle(
        rectVertices[0], rectVertices[1], rectVertices[2],
        colorVector1, colorVector4, colorVector3);
    DrawTriangle(
        rectVertices[2], rectVertices[3], rectVertices[0],
        colorVector3, colorVector2, colorVector1);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawRectangle(
    Vector2 const& position,
    float width,
    float height,
    Vector2 const& originPivot,
    Color const& color)
{
    if (width <= 0 || height <= 0) {
        return;
    }

    Vector2 anchorOffset = Vector2{width, height} * originPivot;
    const auto minX = position.X - anchorOffset.X;
    const auto minY = position.Y - anchorOffset.Y;
    const auto maxX = position.X + width - anchorOffset.X;
    const auto maxY = position.Y + height - anchorOffset.Y;

    std::array<Vector3, 4> rectVertices = {
        Vector3(minX, minY, 0.0f),
        Vector3(minX, maxY, 0.0f),
        Vector3(maxX, maxY, 0.0f),
        Vector3(maxX, minY, 0.0f),
    };

    auto colorVector = color.ToVector4();

    DrawTriangle(
        rectVertices[0], rectVertices[1], rectVertices[2],
        colorVector, colorVector, colorVector);
    DrawTriangle(
        rectVertices[2], rectVertices[3], rectVertices[0],
        colorVector, colorVector, colorVector);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawSphere(
    Vector3 const& position,
    float radius,
    Color const& color,
    std::size_t segments)
{
    POMDOG_ASSERT(segments >= 4);
    POMDOG_ASSERT(radius >= 0);

    if (radius <= 0) {
        return;
    }

    const auto rings = std::max(static_cast<int>(segments), 4);
    const auto sectors = std::max(static_cast<int>(segments), 4);

    std::vector<Vector3> sphereVertices;
    sphereVertices.reserve(rings * sectors);

    const auto R = 1.0f / static_cast<float>(rings - 1);
    const auto S = 1.0f / static_cast<float>(sectors - 1);

    for (int ring = 0; ring < rings; ++ring) {
        const auto latitude = MathConstants<float>::Pi() * ring * R;
        const auto y = std::cos(latitude);
        const auto r = std::sin(latitude);
        for (int s = 0; s < sectors; ++s) {
            const auto longitude = MathConstants<float>::TwoPi() * s * S;
            const auto x = r * std::cos(longitude);
            const auto z = r * std::sin(longitude);
            sphereVertices.push_back(Vector3{x, y, z} * radius + position);
        }
    }

    const auto colorVector = color.ToVector4();
    const auto drawIndices = [&](std::size_t a, std::size_t b, std::size_t c, std::size_t d) {
        POMDOG_ASSERT(a < sphereVertices.size());
        POMDOG_ASSERT(b < sphereVertices.size());
        POMDOG_ASSERT(c < sphereVertices.size());
        POMDOG_ASSERT(d < sphereVertices.size());
        DrawTriangle(
            sphereVertices[a],
            sphereVertices[c],
            sphereVertices[b],
            colorVector,
            colorVector,
            colorVector);
        DrawTriangle(
            sphereVertices[c],
            sphereVertices[a],
            sphereVertices[d],
            colorVector,
            colorVector,
            colorVector);
    };

    for (int r = 0; r < rings - 1; ++r) {
        for (int s = 0; s < sectors - 1; ++s) {
            drawIndices(
                r * sectors + s,
                (r + 1) * sectors + s,
                (r + 1) * sectors + (s + 1),
                r * sectors + (s + 1));
        }
    }
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawTriangle(
    Vector2 const& point1,
    Vector2 const& point2,
    Vector2 const& point3,
    Color const& color)
{
    auto colorVector = color.ToVector4();
    DrawTriangle(
        Vector3{point1, 0.0f},
        Vector3{point2, 0.0f},
        Vector3{point3, 0.0f},
        colorVector, colorVector, colorVector);
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawTriangle(
    Vector2 const& point1,
    Vector2 const& point2,
    Vector2 const& point3,
    Color const& color1,
    Color const& color2,
    Color const& color3)
{
    DrawTriangle(
        Vector3{point1, 0.0f},
        Vector3{point2, 0.0f},
        Vector3{point3, 0.0f},
        color1.ToVector4(),
        color2.ToVector4(),
        color3.ToVector4());
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawTriangle(
    Vector3 const& point1,
    Vector3 const& point2,
    Vector3 const& point3,
    Color const& color1,
    Color const& color2,
    Color const& color3)
{
    DrawTriangle(point1, point2, point3,
        color1.ToVector4(), color2.ToVector4(), color3.ToVector4());
}
//-----------------------------------------------------------------------
void PolygonShapeBuilder::DrawTriangle(
    Vector3 const& point1,
    Vector3 const& point2,
    Vector3 const& point3,
    Vector4 const& color1,
    Vector4 const& color2,
    Vector4 const& color3)
{
    if (vertices.size() + 3 > MaxVertexCount) {
        if (onFlush) {
            onFlush();
        }
    }

    POMDOG_ASSERT(vertices.size() + 3 <= MaxVertexCount);
    vertices.push_back(Vertex{point1, color1});
    vertices.push_back(Vertex{point2, color2});
    vertices.push_back(Vertex{point3, color3});
}
//-----------------------------------------------------------------------
} // namespace Pomdog
