#include "Parameters.hpp"
#include "Types.hpp"
namespace ThrashEngine {

	PropertyClass::PropertyClass()
	{
		//m_property.clear();
		status = true;
	}
	PropertyClass::~PropertyClass()
	{
		//m_property.clear();
		status = true;
	}
	Property* PropertyClass::Get(std::string propName)
	{
		auto it = m_property.find(propName);
		if (it != m_property.end())
		{
			status = true;
			return &it->second; //Texture was found
		}
		status = false;
		return nullptr;
	}
	double PropertyClass::GetDouble(std::string propName)
	{
		Property* prop = Get(propName);
		if (prop == nullptr || prop->type!=DOUBLE)
		{
			status = false;
			return 0;
		}
		status = true;
		return StrToDouble(prop->value);
	
	}
	bool PropertyClass::Set(std::string propName, Property property, std::string info)
	{
		auto it = m_property.find(propName);
		if (info == "")
		{
			property.info = propName;
		}
		else
		{
			property.info = info;
		}
		if (it != m_property.end())
		{
			it->second.type = property.type;		
			it->second.info = property.info;
			it->second.value = property.value;
			status = true;
			return status;
		}
		m_property.insert({ propName,property });
		status = false;
		return status;
	}
	bool PropertyClass::Set(std::string propName, std::string value, std::string info)
	{
		auto it = m_property.find(propName);
		if (it != m_property.end())
		{
			it->second.type = STRING;
			if (info=="")
				it->second.info = propName;
			else 
				it->second.info = info;
			it->second.value = value;
			status = true;
			return status;
		}
		Property newProperty;
		newProperty.value = value;
		newProperty.type = STRING; 
		if (info == "")
			newProperty.info = propName;
		else
			newProperty.info = info;
		m_property.insert({ propName,newProperty });
		status = false;
		return status;
	}
	bool PropertyClass::Set(std::string propName, double value, std::string info)
	{
		auto it = m_property.find(propName);
		if (it != m_property.end())
		{
			it->second.type = DOUBLE;
			if (info == "")
				it->second.info = propName;
			else
				it->second.info = info;
			it->second.value = DoubleToStr(value);
			status = true;
			return status;
		}
		Property newProperty;
		newProperty.value = DoubleToStr(value);
		newProperty.type = DOUBLE;
		if (info == "")
			newProperty.info = propName;
		else
			newProperty.info = info;
		m_property.insert({ propName,newProperty });
		status = false;
		return status;
	}

	size_t PropertyClass::size()
	{
		return m_property.size();
	}
	/*
	NPCProperty* Property::GetProperty(std::string propName)
	{
		auto it = m_property.find(propName);
		if (it != m_property.end())
		{
			m_status = true;
			return &it->second; //Texture was found
		}
		m_status = false;
		return nullptr;
	}
	NPCProperty Property::SetProperty(std::string propName, NPCProperty prop, std::string info)
	{
		auto it = m_property.find(propName);
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			m_status = true;
			return it->second;
		}
		prop.name = new std::string;

		if (info == "")
		{
			*prop.name = propName;
		}
		else
		{
			*prop.name = info;
		}
		m_property.insert({ propName,prop });
		m_status = false;

		return prop;
	}

	NPCProperty Property::SetProperty(std::string propName, double value, std::string info)
	{
		auto it = m_property.find(propName);
		NPCProperty prop;
		prop.type = DOUBLE;
		double* ptr = new double;
		*ptr = value;
		prop.data = ptr;
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			m_status = true;
			return it->second;
		}
		prop.name = new std::string;

		if (info == "")
		{
			*prop.name = propName;
		}
		else
		{
			*prop.name = info;
		}
		m_property.insert({ propName,prop });


		m_status = false;
		return prop;
	}
	NPCProperty Property::SetProperty(std::string propName, std::string value, std::string info)
	{
		auto it = m_property.find(propName);
		NPCProperty prop;
		prop.type = STRING;
		std::string* ptr = new std::string;
		*ptr = value;
		prop.data = ptr;
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			m_status = true;
			return it->second;
		}
		prop.name = new std::string;

		if (info == "")
		{
			*prop.name = propName;
		}
		else
		{
			*prop.name = info;
		}
		m_property.insert({ propName,prop });

		m_status = false;
		return prop;
	}
	NPCProperty Property::SetProperty(std::string propName, char value, std::string info )
	{
		auto it = m_property.find(propName);
		NPCProperty prop;
		prop.type = CHAR;
		char* ptr = new char;
		*ptr = value;
		prop.data = ptr;
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			m_status = true;
			return it->second;
		}
		prop.name = new std::string;

		if (info == "")
		{
			*prop.name = propName;
		}
		else
		{
			*prop.name = info;
		}
		m_property.insert({ propName,prop });


		m_status = false;
		return prop;
	}
	NPCProperty Property::SetPropertyStr(std::string propName, std::string value, std::string info )
	{
		auto it = m_property.find(propName);
		NPCProperty prop;
		prop.type = STRING;
		std::string* ptr = new std::string;
		*ptr = value;
		prop.data = ptr;
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			m_status = true;
			return it->second;
		}
		prop.name = new std::string;

		if (info == "")
		{
			*prop.name = propName;
		}
		else
		{
			*prop.name = info;
		}
		m_property.insert({ propName,prop });


		m_status = false;
		return prop;
	}
	NPCProperty Property::SetProperty(std::string propName, bool value, std::string info )
	{
		auto it = m_property.find(propName);
		NPCProperty prop;
		prop.type = BOOL;
		bool* ptr = new bool;
		*ptr = value;
		prop.data = ptr;
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			m_status = true;
			return it->second;
		}
		prop.name = new std::string;

		if (info == "")
		{
			*prop.name = propName;
		}
		else
		{
			*prop.name = info;
		}
		m_property.insert({ propName,prop });


		m_status = false;
		return prop;
	}

	double Property::GetPropertyDouble(std::string propstr)
	{
		auto prop = GetProperty(propstr);
		if (prop && prop->type == BOOL)
		{
			return (double)(*(bool*)prop);
		}
		if (prop && prop->type != STRING)
		{
			return *(double*)prop;
		}
		return 0;
	}*/
}