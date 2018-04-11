#pragma once

#include <algorithm>

struct Point {
	double x = 0.0, y = 0.0, z = 0.0;

	Point & operator = (const Point & p) = default;

	Point operator+(Point & b) {
		Point point = *this;
		point.x += b.x;
		point.y += b.y;
		point.z += b.z;

		return point;
	}

	Point operator-(Point & b) {
		Point point = *this;
		point.x -= b.x;
		point.y -= b.y;
		point.z -= b.z;

		return point;
	}

	Point operator*(double b) {
		Point point = *this;
		point.x *= b;
		point.y *= b;
		point.z *= b;

		return point;
	}

	Point operator/(double b) {
		Point point = *this;
		point.x /= b;
		point.y /= b;
		point.z /= b;

		return point;
	}

	void operator+=(Point & b) {
		x += b.x;
		y += b.y;
		z += b.z;
	}

	void operator-=(Point & b) {
		x -= b.x;
		y -= b.y;
		z -= b.z;
	}

	void operator*=(double b) {
		x *= b;
		y *= b;
		z *= b;
	}

	void operator/=(double b) {
		x /= b;
		y /= b;
		z /= b;
	}

	bool operator!=(Point & b) {
		if (b.x == x && b.y == y && b.z == z) {
			return false;
		}
		else {
			return true;
		}
	}

	bool operator==(Point & b) {
		if (b.x == x && b.y == y && b.z == z) {
			return true;
		}
		else {
			return false;
		}
	}

	Point(double x, double y, double z) : x(x), y(y), z(z) {};
	Point() {}

	double getLength() {
		return sqrt(x * x + y * y + z * z);
	}

	Point normalize() {
		double length = getLength();
		x /= length;
		y /= length;
		z /= length;

		return Point(x, y, z);
	}

	Point getNormal() {
		Point normalized;
		normalized = *this;
		normalized.normalize();
		return normalized;
	}

};