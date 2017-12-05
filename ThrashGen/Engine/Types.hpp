#pragma once
/******************************
//Types.hpp math types(classes)

Vector  - for two-dimensional point

Rectangle - startpoint and size
*******************************/
#include "Core.hpp"
#include <string>
#include <sstream>
#include <typeinfo>
#include <iomanip>



//!!!NEW SYSTEM!!!

namespace ThrashEngine
{
	class Vector;

	class VectorFull
	{
	public:
		double x; //x component
		double y; //y component
		double len; // buffer for length
		double zero; // for 32 byte class
		VectorFull() //default constructor
		{
			x = y = 0;
		}
		VectorFull(double x, double y = 0) //constructor with params
		{
			this->x = x;
			this->y = y;
		}		
		VectorFull operator=(const VectorFull& rhs) // = operator for other vector
		{
			this->x = rhs.x;
			this->y = rhs.y;
			return *this;
		}
		VectorFull operator+(const VectorFull& rhs) // sum operator
		{
			VectorFull lhs = *this; //temporary vector
			lhs.x += rhs.x;
			lhs.y += rhs.y;
			return lhs;
		}
		VectorFull operator+=(const VectorFull& rhs) //sum+= operator
		{
			*this = *this + rhs;
			return *this;
		}
		VectorFull operator-()	// - operator(changes direction)
		{
			VectorFull vec = *this;
			vec.x = -vec.x;
			vec.y = -vec.y;
			return vec;
		}
		VectorFull operator-(VectorFull& rhs)// minus vector
		{
			return *this + -rhs;
		}
		VectorFull operator-=(VectorFull& rhs) //minus-=
		{
			*this = *this - rhs;
			return *this;
		}
		VectorFull operator*(double rhs)// multiply with a double
		{
			VectorFull vec = *this;
			vec.x *= rhs;
			vec.y *= rhs;
			return vec;
		}
		VectorFull operator*(int rhs)//multiply with an int
		{
			VectorFull vec = *this;
			vec.x *= rhs;
			vec.y *= rhs;
			return vec;
		}
		VectorFull operator*=(double rhs)// multiply with a double
		{
			*this = *this*rhs;
			return *this;
		}
		VectorFull operator*=(int rhs)//multiply with an int
		{
			*this = *this*rhs;
			return *this;
		}
		double Len()//Get vector length
		{
			len = sqrt(x*x + y*y);
			return len;
		}
		double LenSq()//Get vector length square
		{
			len = x*x + y*y;
			return len;
		}
		void Normalize()//Normalize vector
		{
			if (x && y)
			{
				Len();
				x = x / len;
				y = y / len;
			}
		}
		void SetLen(double sq)
		{
			if (!sq)return;
			double thislen = LenSq();
			sq *= sq;
			double koef = sq / thislen;
			x *= koef;
			y *= koef;
		}
	};


	class Vector
	{
	public:
		double x; //x component
		double y; //y component
		Vector() //default constructor
		{
			x = y = 0;
		}
		Vector(double x, double y = 0) //constructor with params
		{
			this->x = x;
			this->y = y;
		}
		Vector operator=(const Vector& rhs) // = operator for other vector
		{
			this->x = rhs.x;
			this->y = rhs.y;
			return *this;
		}
		Vector operator+(const Vector& rhs) // sum operator
		{
			Vector lhs = *this; //temporary vector
			lhs.x += rhs.x;
			lhs.y += rhs.y;
			return lhs;
		}
		Vector operator+=(const Vector& rhs) //sum+= operator
		{
			*this = *this + rhs;
			return *this;
		}
		Vector operator-()	// - operator(changes direction)
		{
			Vector vec = *this;
			vec.x = -vec.x;
			vec.y = -vec.y;
			return vec;
		}
		Vector operator-(Vector& rhs)// minus vector
		{
			return *this + -rhs;
		}
		Vector operator-=(Vector& rhs) //minus-=
		{
			*this = *this - rhs;
			return *this;
		}
		Vector operator*(double rhs)// multiply with a double
		{
			Vector vec = *this;
			vec.x *= rhs;
			vec.y *= rhs;
			return vec;
		}
		Vector operator*(int rhs)//multiply with an int
		{
			Vector vec = *this;
			vec.x *= rhs;
			vec.y *= rhs;
			return vec;
		}
		Vector operator*=(double rhs)// multiply with a double
		{
			*this = *this*rhs;
			return *this;
		}
		Vector operator*=(int rhs)//multiply with an int
		{
			*this = *this*rhs;
			return *this;
		}
		double Len()//Get vector length
		{
			return sqrt(x*x + y*y);
		}
		double LenSq()//Get vector length square
		{
			return x*x + y*y;
		}
		void SetLen(double sq)
		{
			if (!sq)return;
			double thislen = LenSq();
			sq *= sq;
			double koef = sq / thislen;
			x *= koef;
			y *= koef;
		}
		operator VectorFull()
		{
		return VectorFull(x,y);
		}
	};

	/*
namespace ThrashEngine
{

	class Vector
	{
	public:
		double x; //x component
		double y; //y component
		double len; // buffer for length
		double zero; // for 32 byte class
		Vector() //default constructor
		{
			x = y = 0;
		}
		Vector(double x, double y = 0) //constructor with params
		{
			this->x = x;
			this->y = y;
		}
		Vector operator=(const Vector& rhs) // = operator for other vector
		{
			this->x = rhs.x;
			this->y = rhs.y;
			return *this;
		}
		Vector operator+(const Vector& rhs) // sum operator
		{
			Vector lhs = *this; //temporary vector
			lhs.x += rhs.x;
			lhs.y += rhs.y;
			return lhs;
		}
		Vector operator+=(const Vector& rhs) //sum+= operator
		{
			*this = *this + rhs;
			return *this;
		}
		Vector operator-()	// - operator(changes direction)
		{
			Vector vec = *this;
			vec.x = -vec.x;
			vec.y = -vec.y;
			return vec;
		}
		Vector operator-(Vector& rhs)// minus vector
		{
			return *this + -rhs;
		}
		Vector operator-=(Vector& rhs) //minus-=
		{
			*this = *this - rhs;
			return *this;
		}
		Vector operator*(double rhs)// multiply with a double
		{
			Vector vec = *this;
			vec.x *= rhs;
			vec.y *= rhs;
			return vec;
		}
		Vector operator*(int rhs)//multiply with an int
		{
			Vector vec = *this;
			vec.x *= rhs;
			vec.y *= rhs;
			return vec;
		}
		Vector operator*=(double rhs)// multiply with a double
		{
			*this = *this*rhs;
			return *this;
		}
		Vector operator*=(int rhs)//multiply with an int
		{
			*this = *this*rhs;
			return *this;
		}
		double Len()//Get vector length
		{
			len = sqrt(x*x + y*y);
			return len;
		}
		double LenSq()//Get vector length square
		{
			len = x*x + y*y;
			return len;
		}
		void Normalize()//Normalize vector
		{
			if (x && y)
			{
				Len();
				x = x / len;
				y = y / len;
			}
		}
		void SetLen(double sq)
		{
			if (!sq)return;
			double thislen = LenSq();
			sq *= sq;
			double koef = sq / thislen;
			x *= koef;
			y *= koef;
		}
	};
	*/
	//Type for rectangle with double's (instead of using SDL_Rect with int's)
	class Rectangle
	{
	public:
		double x;
		double y;
		double w;
		double h;
		Rectangle() //default constructor
		{
			x = y = w = h = 0;
		}
		Rectangle(double x, double y = 0, double w = 0, double h = 0)//constructor with params
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
		Rectangle(SDL_Rect rect)//copy constructor
		{
			x = rect.x;
			y = rect.y;
			w = rect.w;
			h = rect.h;
		}
		Rectangle (Vector vector)//vector constructor
		{
			x = vector.x;
			y = vector.y;
			w = h = 0;
		}
		Rectangle(Vector xy, Vector wh)
		{
			this->x = xy.x;
			this->y = xy.y;
			this->w = wh.x;
			this->h = wh.y;
		}
		Rectangle operator=(const Rectangle& rhs)//copy operator
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->w = rhs.w;
			this->h = rhs.h;
			return *this;
		}		
		Rectangle operator=(const Vector& rhs)//copy operator
		{
			this->x = rhs.x;
			this->y = rhs.y;
			return *this;
		}
		Rectangle operator=(const double& rhs)//copy operator
		{
			this->x = this->y = this->w = this->h = rhs;

			return *this;
		}
		Rectangle operator+(const Rectangle& rhs)//sum operator
		{
			Rectangle rect;
			rect.x = x + rhs.x;
			rect.y = y + rhs.y;
			rect.w = w + rhs.w;
			rect.h = h + rhs.h;
			return rect;
		}
		Rectangle operator+=(const Rectangle& rhs)//sum+=
		{
			*this = *this + rhs;
			
			return *this;
		}
		Rectangle operator-() //oposite
		{
			Rectangle rect=*this;
			rect.x = -rect.x;
			rect.y = -rect.y;
			rect.w = -rect.w;
			rect.h = -rect.h;
			return rect;

		}
		Rectangle operator-(Rectangle& rhs)//minus rect
		{
			return *this+-rhs;
		}
		Rectangle operator -=(Rectangle& rhs)//minus-=
		{
			*this = *this - rhs;
			return *this;
		}
		Vector GetVector()
		{
			return Vector(x, y);
		}

	};
	//Type convertions

	static bool TypeCastStatus = false;

	static std::string IntToStr(int value) //Integer to string
	{
		return std::to_string(value);
	}
	static std::string DoubleToStr(double value) //Double to string
	{
		return std::to_string(value);
	}

	static std::string IntToStr(int value, int precise)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(precise) << value;
		return stream.str();
	}

	static std::string DoubleToStr(double value, int precise,int width)
	{
		std::stringstream stream;
		stream << std::fixed << std::setw(width) << std::setprecision(precise) << value;
		return stream.str();
	}

	static double StrToDouble(std::string str) //String to double
	{
		std::string::size_type sz;
		return std::stod(str, &sz);
	}

	template <typename T>
	static T StrToValue(std::string str)
	{
		std::stringstream stream;
		T res;
		stream << str;
		stream >> res;
		return res;
	}
	template <typename T>
	static std::string ValueToString(T value)
	{
		std::stringstream stream;
		std::string res;
		stream << value;
		stream >> res;
		return res;
	}

	static std::string GetToWord(std::string str)
	{
		size_t i = 0;
		while (str[i] == ' ')
		{
			if (i > str.length()) return std::string();
			i++;
		}
		return std::string(str, i);
	}

	static std::string GetToSpace(std::string str)
	{
		size_t i = 0;
		while (str[i] != ' ')
		{
			if (i > str.length()) return std::string();
			i++;
		}
		return std::string(str, i);
	}

	static std::string GetWord(std::string str)
	{
		size_t i = 0;
		if (str.length() == 0)return std::string("");
		while (str[i] != ' ')
		{
			if (i > str.length() - 1) return str;
			i++;
		}
		return std::string(str, 0, i);
	}

	static SDL_Color Color(unsigned char r=255, unsigned char g=255, unsigned char b=255, unsigned char a=255)
	{
		SDL_Color col;
		col.r = r;
		col.g = g;
		col.b = b;
		col.a = a;
		return col;
	}


}