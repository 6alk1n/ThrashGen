#pragma once
/*****************
//Physics.hpp
Math functions for collision
******************/
#include "Core.hpp"

namespace ThrashEngine
{
	static bool isPointinRect(Vector& point,Rectangle& rect)
	{
		return (point.x >= rect.x && point.y >= rect.y && point.x <= rect.x + rect.w && point.y <= rect.y + rect.h);
	}
	static bool RectRectCollision(Rectangle& rect1, Rectangle& rect2) //don't touch
	{
			return (rect1.x < rect2.x + rect2.w &&
			rect1.x + rect1.w > rect2.x &&
			rect1.y < rect2.y + rect2.h &&
			rect1.h + rect1.y > rect2.y	);
	}
	static bool RectRectCollisionWeak(Rectangle& rect1, Rectangle& rect2)//borders can touch a little
	{
		return (rect1.x <= rect2.x + rect2.w &&
			rect1.x + rect1.w >= rect2.x &&
			rect1.y <= rect2.y + rect2.h &&
			rect1.h + rect1.y >= rect2.y);
	}
	static bool isPointinCircle(Vector& point, Vector& circle, double size)
	{
		Vector dif = circle - point;
		double len = dif.x*dif.x + dif.y*dif.y;
		return (len < (size*size));
	}
	static bool RectCircleCollision(Rectangle& rect, Vector& vec, double size)
	{
		/*if (isPointinCircle(Vector(rect.x, rect.y), vec, size) ||
			isPointinCircle(Vector(rect.x+rect.w, rect.y), vec, size) ||
			isPointinCircle(Vector(rect.x+rect.w, rect.y+rect.h), vec, size) ||
			isPointinCircle(Vector(rect.x, rect.y+rect.h), vec, size)) return true;
		if (isPointinRect(vec, rect)) return true;
		return false;
	
	*/
		Vector rectcen(rect.x + (rect.w / 2), rect.y + (rect.h / 2));

		double w = rect.w / 2;
		double h = rect.h / 2;
		Vector df = vec - rectcen;
		if (abs(df.x) > (size + w) || abs(df.y) > (size + h)) return false;
		double dw = abs(df.x - w);
		double dh = abs(df.y - h);
		if (vec.x <= dw) return true;
		if (vec.y <= dh) return true;
		double len = (dw - w)*(dw - w) + (dh - h)*(dh - h);
		return len <= size*size;


	/*
	var rectangleCenter = new PointF((rectangle.X +  rectangle.Width / 2),
                                     (rectangle.Y + rectangle.Height / 2));

    var w = rectangle.Width  / 2;
    var h = rectangle.Height / 2;

    var dx = Math.Abs(circle.X - rectangleCenter.X);
    var dy = Math.Abs(circle.Y - rectangleCenter.Y);

    if (dx > (radius + w) || dy > (radius + h)) return false;

    var circleDistance = new PointF
                             {
                                 X = Math.Abs(circle.X - rectangle.X - w),
                                 Y = Math.Abs(circle.Y - rectangle.Y - h)
                             };

    if (circleDistance.X <= (w))
    {
        return true;
    }

    if (circleDistance.Y <= (h))
    {
        return true;
    }

    var cornerDistanceSq = Math.Pow(circleDistance.X - w, 2) + 
                                    Math.Pow(circleDistance.Y - h, 2);

    return (cornerDistanceSq <= (Math.Pow(radius, 2)));
	*/
	
	
	}
}