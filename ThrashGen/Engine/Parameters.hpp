#pragma once
#include <string>
#include <map>
//Object parameters consts that are mostly used


//!!!NEW SYSTEM!!!
namespace ThrashEngine {
	enum NPCState
	{
		Idle,
		Moving,
		Attack,
		Chacing,
		Jump,
		Kill
	};

	enum PropertyType
	{
	  ERRORTYPE,
	  DOUBLE,
	  STRING
	};

	struct Property
	{
	  std::string value;
	  PropertyType type;
	  std::string info;
	};

	class PropertyClass
	{
	public:
		//Methods
		PropertyClass();
		~PropertyClass();
		Property* Get(std::string);
		double GetDouble(std::string);
		bool Set(std::string,Property,std::string info="");
		bool Set(std::string,std::string,std::string info = "");
		bool Set(std::string,double,std::string info = "");

		size_t size();

		//Members
	public:
		bool status;
		std::map<std::string, Property> m_property;
	private:
		double __unused8byte__;
	};
}

/*
namespace ThrashEngine {
	enum NPCState
	{
		Idle,
		Moving,
		Attack,
		Chacing,
		Jump,
		Kill
	};
	enum PropertyType
	{
		INT,
		DOUBLE,
		CHAR,
		BOOL,
		STRING,
		ERRORTYPE
	};

	struct NPCProperty
	{
		NPCProperty()
		{
			type = ERRORTYPE;
			data = nullptr;
			name = nullptr;
		}
		PropertyType type;
		void* data;
		std::string* name;
	};

	struct NPCProperties
	{
		int fraction;
		NPCState state;
		double range;
		double InteractionRange;
		double MaxSpeed;
		double Acceleration;
		double breakSpeed;
		double interactionColdDown;
		double hp;
		double maxhp;
		double damage;
		double armor;
	};

	class Property
	{
	public:
		std::map<std::string, NPCProperty> m_property;
		NPCProperty* GetProperty(std::string);
		double GetPropertyDouble(std::string);
		NPCProperty SetProperty(std::string, NPCProperty,std::string info="");
		NPCProperty SetProperty(std::string, double, std::string info = "");
		NPCProperty SetProperty(std::string, std::string, std::string info = "");
		NPCProperty SetPropertyStr(std::string, std::string, std::string info = "");
		NPCProperty SetProperty(std::string, char, std::string info = "");
		NPCProperty SetProperty(std::string, bool, std::string info = "");

		bool m_status;
	};
}
*/
