#pragma once
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/polygon/polygon.hpp>
#include <vector>

namespace Geometry
{
	template <class T> struct PointBase2
	{
		typedef T value_type;
		T x, y;
		PointBase2() = default;

		PointBase2(T x_, T y_)
			: x(x_)
			, y(y_)
		{
		}

		bool operator==(const PointBase2<T>& other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const PointBase2<T>& other) const
		{
			return !(*this == other);
		}
	};
	typedef PointBase2<int> PointI;
	typedef PointBase2<float> PointF;
	typedef PointBase2<double> PointD;

	struct Limits
	{
		PointD min;
		PointD max;
		void bound(PointD::value_type boundingDelta)
		{
			min.x -= boundingDelta;
			min.y -= boundingDelta;
			max.x += boundingDelta;
			max.y += boundingDelta;
		}
	};



} // namespace Geometry

namespace bp = boost::polygon;

typedef double coordinate_type;
typedef bp::point_data<coordinate_type> Point;


namespace bg = boost::geometry;
namespace bp = boost::polygon;

typedef double coordinate_type;
typedef bp::point_data<coordinate_type> Point;
typedef std::vector<Point> PointVector;
typedef bg::model::point<coordinate_type, 2, bg::cs::cartesian> PointModel;

typedef bg::model::polygon<PointModel> SitePolygon;
typedef bg::model::multi_polygon<SitePolygon> Sites;

