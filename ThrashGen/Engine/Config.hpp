/*#pragma once
#include "Core.hpp"
#include <string>
#include <vector>

const int ConfigLineTypeNumber = 1;
const int ConfigLineTypeString = 2;

struct ConfigLine
{
	std::string m_paramName;
	int m_type;
	double m_value;
	std::string m_strvalue;
};

class ConfigFile
{
public:
	ConfigFile();
	~ConfigFile();
	bool ReadFromFile(std::string);
	ConfigLine* GetParam(std::string);

protected:
	void GetTokens(std::string& input);
	std::vector<ConfigLine> m_params;
	std::vector<std::string> m_tokens;
};*/


#pragma once
#include "Core.hpp"
#include <vector>
#include <string>
#include <list>
#include <fstream>
namespace ThrashEngine
{

	const std::string DefaultGroupName("DefaultGroup");

	const int type_comment = 0;
	const int type_data = 1;
	const int type_group = 2;

	struct ConfigData
	{
		std::string name;
		double data;
		void* pointer;
		ConfigData() :
			data(0),
			pointer(nullptr)
		{}
		ConfigData(std::string name) :
			name(name),
			data(0),
			pointer(nullptr)
		{}
	};
	typedef std::vector<ConfigData>::iterator ConfigDataIterator;

	struct GroupData
	{
		std::string GroupName;
		std::vector<ConfigData> Data;
		GroupData()
		{}
		GroupData(std::string name) :
			GroupName(name)
		{}
	};
	typedef std::vector<ConfigData>::iterator GroupDataIterator;
	const GroupData DefaultGroupFail(DefaultGroupName);

	class Config
	{
	protected:
		std::vector<GroupData> Data;
		GroupData CurrentGroup;

		struct LoaderStruct
		{
			int type;
			std::string name;
			double value;
			int error;
			LoaderStruct()
			{
				type = type_comment;
				value = 0;
				error = false;
			}
		};

		LoaderStruct ReadLine(std::fstream &File);

	public:
		Config();
		~Config();
		int LoadConfig(std::string);
		int AddConfig(std::string);
		void ClearConfig();
		void ClearGroup(GroupData&);
		GroupData& FindGroup(std::string);

		int CreateGroup(std::string);
		int CreateGroup(GroupData);

		int AddToGroup(GroupData&, ConfigData);
		int Add(ConfigData);
		void SetGroup(std::string);
		void SetGroup(GroupData);

		ConfigData& GetParam(std::string);
		ConfigData& GetParam(GroupData&, std::string);
	};
}