
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/algorithms/correct.hpp>
#include <QtSvg/QSvgGenerator>
#include <QPainter>

#include "test_data.h"

constexpr double kBoundingDelta	  = 1000.0;
int main(int argc, char *argv[])
{
    Geometry::Limits limits;
    limits.max={582694,932300};
    limits.min={578214,929587};
    auto boundedLimits = limits;
    boundedLimits.bound(kBoundingDelta);

    {
        std::vector<Sites> clippedPolygons;

        for (auto it = testSites.cbegin(); it != testSites.cend(); it++)
        {
            Sites clippedPoly;

            bool status = bg::intersection(*it, testClippingPolys, clippedPoly);
            if (status && !clippedPoly.empty())
            {
                clippedPolygons.push_back(clippedPoly);
            }
        }

        {

            QSvgGenerator generator;
            generator.setFileName("isoline_clipped.svg");
            generator.setSize(QSize(std::abs(boundedLimits.max.x - boundedLimits.min.x),
                                    std::abs(boundedLimits.max.y - boundedLimits.min.y)));

            generator.setTitle(("Isoline clipped"));
            generator.setDescription(("Isoline clipped ok"));
            QPainter painter;
            painter.begin(&generator);
            for (auto&& site : clippedPolygons)
            {
                for (auto&& polygon : site)
                {
                    QPolygonF qpolygon;
                    std::transform(polygon.outer().cbegin(), polygon.outer().cend(), std::back_inserter(qpolygon),
                                   [](const PointModel& point)
                                   {
                                       return QPointF(point.get<0>(), point.get<1>());
                                   });
                    painter.drawPolygon(qpolygon);
                }
            }

            painter.end();
        }
        {
            QSvgGenerator generator;
            generator.setFileName("isoline_with_broken_clipping_area.svg");
            generator.setSize(QSize(std::abs(boundedLimits.max.x - boundedLimits.min.x),
                                    std::abs(boundedLimits.max.y - boundedLimits.min.y)));

            generator.setTitle(("Isoline with broken clipping area"));
            generator.setDescription(("Isoline with broken clipping area"));
            QPainter painter;
            painter.begin(&generator);
            for (const auto& site : testSites)
            {
                QPolygonF qpolygon;
                std::transform(site.outer().cbegin(), site.outer().cend(), std::back_inserter(qpolygon),
                               [](const PointModel& point)
                               {
                                   return QPointF(point.get<0>(), point.get<1>());
                               });
                painter.drawPolygon(qpolygon);
            }
            QPolygonF qpolygon;

            std::transform(brokenClippingPolygon.outer().cbegin(), brokenClippingPolygon.outer().cend(),
                           std::back_inserter(qpolygon),
                           [](const PointModel& point)
                           {
                               return QPointF(point.get<0>(), point.get<1>());
                           });
            painter.drawPolygon(qpolygon);
            painter.end();
        }

    }
    {
        std::vector<Sites> clippedPolygons;

        auto clippingPoly=brokenClippingPolygon;
        bg::correct(clippingPoly);

        for (auto it = testSites.cbegin(); it != testSites.cend(); it++)
        {
            Sites clippedPoly;

            bool status = bg::intersection(*it, clippingPoly, clippedPoly);
            if (status && !clippedPoly.empty())
            {
                clippedPolygons.push_back(clippedPoly);
            }
        }



        QSvgGenerator generator;
        generator.setFileName("isoline_clipped_broken.svg");
        generator.setSize(QSize(std::abs(boundedLimits.max.x - boundedLimits.min.x),
                                std::abs(boundedLimits.max.y - boundedLimits.min.y)));

        generator.setTitle(("Isoline clipped by broken clipping area"));
        generator.setDescription(("Isoline clipped by broken clipping area"));
        QPainter painter;
        painter.begin(&generator);
        for (auto&& site : clippedPolygons)
        {
            for (auto&& polygon : site)
            {
                QPolygonF qpolygon;
                std::transform(polygon.outer().cbegin(), polygon.outer().cend(), std::back_inserter(qpolygon),
                               [](const PointModel& point)
                               {
                                   return QPointF(point.get<0>(), point.get<1>());
                               });
                painter.drawPolygon(qpolygon);
            }
        }

        painter.end();

    }

    return 0;
}
