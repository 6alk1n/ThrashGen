#include "Config.hpp"

using namespace ThrashEngine;

Config::Config()
{
}
#include <iostream>
Config::~Config()
{

}

int Config::LoadConfig(std::string filename)
{

	std::fstream File(filename, std::fstream::in);
	if (!File)
	{
		std::cout << "Failed to open file" << std::endl;
	}

	bool done = false;
	int linenum = 0;
	while (!done)
	{
		linenum++;
		LoaderStruct data = ReadLine(File);
		if (data.error)
		{
			if (data.error == 1)
			{
				File.close();
				return 1;
			}
			std::cout << linenum << ":" << data.name << std::endl;
		}
		else
		{
			if (data.type == type_data)
			{
				ConfigData newdata;
				newdata.data = data.value;
				newdata.name = data.name;
				newdata.pointer = nullptr;
				Add(newdata);
			}
			else if (data.type == type_group)
			{
				CreateGroup(data.name);
				SetGroup(data.name);
			}

		}
	}
	File.close();
	return 1;
}

int Config::AddConfig(std::string)
{
	return 1;
}

void Config::ClearConfig()
{
	for (auto i = Data.begin(); i != Data.end(); i++)
	{
		ClearGroup(i[0]);
		i[0].GroupName.clear();
	}
	Data.erase(Data.begin(), Data.end());
	Data.clear();
}

void Config::ClearGroup(GroupData& Group)
{
	for (auto i = Group.Data.begin(); i != Group.Data.end(); i++)
	{
		i[0].name.clear();
		if (i[0].pointer != nullptr)
		{
			delete i[0].pointer;
			i[0].pointer = nullptr;
		}
	}
	Group.Data.erase(Group.Data.begin(), Group.Data.end());
	Group.Data.clear();
}

GroupData& Config::FindGroup(std::string str)
{
	for (auto i = Data.begin(); i != Data.end(); i++)
	{
		if (i[0].GroupName == str)
		{
			return i[0];
		}
	}
	return GroupData(DefaultGroupName);
}

int Config::AddToGroup(GroupData& Group, ConfigData CData)
{
	for (auto i = Group.Data.begin(); i != Group.Data.end(); i++) // check for names
	{
		if (i[0].name == CData.name)
		{
			return 0; //config with same name already exists
		}
	}
	Group.Data.push_back(CData);
	return 1;
}

void Config::SetGroup(std::string name)
{
	CurrentGroup = FindGroup(name);
}
void Config::SetGroup(GroupData group)
{
	CurrentGroup = group;
}

int Config::Add(ConfigData dat)
{
	return (AddToGroup(FindGroup(CurrentGroup.GroupName), dat));
}

int Config::CreateGroup(std::string name)
{
	for (auto i = Data.begin(); i != Data.end(); i++)
	{
		if (i[0].GroupName == name)
		{
			return 0;
		}
	}
	GroupData NewGroup(name);
	Data.push_back(NewGroup);
	return 1;
}
int Config::CreateGroup(GroupData group)
{
	for (auto i = Data.begin(); i != Data.end(); i++)
	{
		if (i[0].GroupName == group.GroupName)
		{
			return 0;
		}
	}
	Data.push_back(group);
	return 1;
}

ConfigData& Config::GetParam(std::string str)
{
	GroupData& Group = FindGroup(CurrentGroup.GroupName);
	for (auto i = Group.Data.begin(); i != Group.Data.end(); i++)
	{
		if (i[0].name == str)
		{
			return i[0];
		}
	}
	return ConfigData();
}
ConfigData& Config::GetParam(GroupData& Group, std::string str)
{
	for (auto i = Group.Data.begin(); i != Group.Data.end(); i++)
	{
		if (i[0].name == str)
		{
			return i[0];
		}
	}
	return ConfigData();
}

Config::LoaderStruct Config::ReadLine(std::fstream &File)
{
	LoaderStruct res;
	std::string str;
	if (!(std::getline(File, str)))
	{
		res.error = 1; //EOF or getline error
		res.name = "Failed to load string";
		return res;
	}
	if (str == "")
	{
		res.error = 0; //EOF or getline error
		res.name = "No string";
		return res;
	}
	std::string loadername = GetToWord(str);
	loadername = GetWord(loadername);

	if (loadername.length() > 3)
	{
		if ((loadername[0] == '[') && (loadername[loadername.length() - 1] == ']')) //it is group
		{
			std::string GroupName(loadername, 1, loadername.length() - 2);
			res.type = type_group;
			res.name = GroupName;
			res.value = 0;
			return res;
		}
		else if ((loadername[0] == '/') && (loadername[1] == '/'))
		{
			std::string GroupName(loadername, 0, 1);
			res.type = type_comment;
			res.name = GroupName;
			res.value = 0;
			return res;
		}
	}
	{
		std::string GroupName(loadername, 0, loadername.length());
		res.type = type_data;
		res.name = GroupName;
		std::string read = GetToWord(str);
		read = GetToSpace(read);
		read = GetToWord(read);
		std::string eqoperator = GetWord(read);
		if (eqoperator == "=")
		{
			read = GetToSpace(read);
			read = GetToWord(read);
			std::string ParamValue = GetWord(read);

			double Value = StrToValue<double>(ParamValue);
			res.value = Value;
			return res;
		}
		else
		{
			res.error = 3; //fail operator equal
			res.name = "Didn't found operator equal";
			return res;
		}
	}

	res.error = 2; //unknown command
	res.name = "Didn't recognized command";
	return res;

}