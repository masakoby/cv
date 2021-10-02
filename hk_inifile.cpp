//#include "pch.h"
#include "hk_inifile.h"

#include <fstream>
#include <sstream>
#include <iostream>

hk::CIniFile::CIniFile()
{
}


hk::CIniFile::~CIniFile()
{
}

hk::CIniFile::CIniFile(const std::string& i_fpath)
{
	Load(i_fpath);
}

void hk::CIniFile::Clear()
{
	m_items.clear();
}


bool hk::CIniFile::Load(const std::string& i_fpath)
{
	Clear();

	std::ifstream fs(i_fpath);
	if (fs.is_open() == false)
	{
		return false;
	}

	std::string cur_sec = "";
	while (fs.eof() == false)
	{
		std::string line;
		std::getline(fs, line);
		SItem item = SItem::ParseText(line);

		if (item.Type == EType::TYPE_SECTION)
		{
			cur_sec = item.Section;
		}
		else if (item.Type == EType::TYPE_PARAMETER)
		{
			item.Section = cur_sec;
		}

		m_items.push_back(item);
	}
	return true;
}

bool hk::CIniFile::Save(const std::string& i_fpath)
{
	std::ofstream fs(i_fpath);
	if (fs.is_open() == false)
	{
		//std::cout << "fs.is_open() == false" << std::endl;
		return false;
	}

	for (int i = 0; i < (int)m_items.size(); i++)
	{
		if (i == 0)
		{
			fs << m_items[i].Text;
		}
		else
		{
			fs << "\n" << m_items[i].Text;
		}
	}

	return true;
}

bool hk::CIniFile::ExportCsvFile(const std::string& i_fpath)
{
	std::ofstream fs(i_fpath);
	if (fs.is_open() == false)
	{
		return false;
	}

	std::vector<int> indexs;
	EnumParameter(indexs);

	fs << "section,key,value" << std::endl;

	for (int i = 0; i < (int)indexs.size(); i++)
	{
		int ii = indexs[i];
		SItem item = m_items[ii];
		fs << item.Section << "," << item.Key << "," << item.Value << std::endl;
	}

	return true;
}


bool hk::CIniFile::Get(const std::string& i_section, const std::string& i_key, std::string& io_value)
{
	int i = FindParameter(i_section, i_key);
	if (i >= 0)
	{
		io_value = m_items[i].Value;
		return true;
	}
	return false;
}

void hk::CIniFile::Set(const std::string& i_section, const std::string& i_key, const std::string& i_value)
{
	int i = FindParameter(i_section, i_key);
	if (i >= 0)
	{
		// 既存パラメータ更新
		m_items[i] = SItem::FromParameter(i_section, i_key, i_value);
	}
	else
	{
		// 新規追加
		insertParameter(i_section, i_key, i_value);
	}
}

//bool hk::CIniFile::Get(const std::string& i_section, const std::string& i_key, short& io_value)
//{
//	std::string strval = shortToString(io_value);
//	if (Get(i_section, i_key, strval))
//	{
//		io_value = shortFromString(strval);
//		return true;
//	}
//	return false;
//}
//
//void hk::CIniFile::Set(const std::string& i_section, const std::string& i_key, short i_value)
//{
//	std::string strval = shortToString(i_value);
//	Set(i_section, i_key, strval);
//}
//
//bool hk::CIniFile::Get(const std::string& i_section, const std::string& i_key, int& io_value)
//{
//	std::string strval = intToString(io_value);
//	if (Get(i_section, i_key, strval))
//	{
//		io_value = intFromString(strval);
//		return true;
//	}
//	return false;
//}
//
//void hk::CIniFile::Set(const std::string& i_section, const std::string& i_key, int i_value)
//{
//	std::string strval = intToString(i_value);
//	Set(i_section, i_key, strval);
//}
//
//bool hk::CIniFile::Get(const std::string& i_section, const std::string& i_key, float& io_value)
//{
//	std::string strval = floatToString(io_value);
//	if (Get(i_section, i_key, strval))
//	{
//		io_value = floatFromString(strval);
//		return true;
//	}
//	return false;
//}
//
//void hk::CIniFile::Set(const std::string& i_section, const std::string& i_key, float i_value)
//{
//	std::string strval = floatToString(i_value);
//	Set(i_section, i_key, strval);
//}
//
//bool hk::CIniFile::Get(const std::string& i_section, const std::string& i_key, double& io_value)
//{
//	std::string strval = doubleToString(io_value);
//	if (Get(i_section, i_key, strval))
//	{
//		io_value = doubleFromString(strval);
//		return true;
//	}
//	return false;
//}
//
//void hk::CIniFile::Set(const std::string& i_section, const std::string& i_key, double i_value)
//{
//	std::string strval = doubleToString(i_value);
//	Set(i_section, i_key, strval);
//}

void hk::CIniFile::EnumSection(std::vector<int>& o_index) const
{
	o_index.clear();

	for (int i = 0; i < (int)m_items.size(); i++)
	{
		if (m_items[i].Type == EType::TYPE_SECTION)
		{
			o_index.push_back(i);
		}
	}
}

void hk::CIniFile::EnumParameter(std::vector<int>& o_index) const
{
	o_index.clear();

	for (int i = 0; i < (int)m_items.size(); i++)
	{
		if (m_items[i].Type == EType::TYPE_PARAMETER)
		{
			o_index.push_back(i);
		}
	}
}

int hk::CIniFile::FindSection(const std::string& i_section) const
{
	for (int i = 0; i < (int)m_items.size(); i++)
	{
		if (m_items[i].Type == EType::TYPE_SECTION)
		{
			if (m_items[i].Section == i_section)
			{
				return i;
			}
		}
	}
	return -1;
}

int hk::CIniFile::FindParameter(const std::string& i_section, const std::string& i_key) const
{
	for (int i = 0; i < (int)m_items.size(); i++)
	{
		if (m_items[i].Type == EType::TYPE_PARAMETER)
		{
			if (m_items[i].Section == i_section && m_items[i].Key == i_key)
			{
				return i;
			}
		}
	}
	return -1;
}

void hk::CIniFile::InsertComment(int i_index, const std::string& i_text, const std::string& i_mark)
{
	SItem item= SItem::FromComment(i_text, i_mark);

	if (i_index > (int)m_items.size())
	{
		m_items.push_back(item);
	}
	else
	{
		auto ite = m_items.begin() + i_index;
		m_items.insert(ite, item);
	}
}


void hk::CIniFile::insertParameter(const std::string& i_section, const std::string& i_key, const std::string& i_value)
{
	std::vector<int> indexs;
	EnumSection(indexs);

	for (int i = 0; i < (int)indexs.size(); i++)
	{
		int index = indexs[i];
		SItem item = m_items[index];
		if (item.Section == i_section)
		{
			int insert_index = index;
			for (int j = index + 1; j < (int)m_items.size(); j++)
			{
				insert_index = j;
				SItem item2 = m_items[j];
				if (item2.Type == EType::TYPE_SECTION && item2.Section != i_section)
				{
					// 途中挿入
					m_items.insert(m_items.begin() + insert_index, SItem::FromParameter(i_section, i_key, i_value));
					return;
				}
			}
			// 最後に挿入
			m_items.push_back(SItem::FromParameter(i_section, i_key, i_value));
			return;
		}
	}

	// セクションがない場合、最後に追加
	m_items.push_back(SItem::FromSection(i_section));
	m_items.push_back(SItem::FromParameter(i_section, i_key, i_value));
}

bool hk::CIniFile::GetPrivateProfileString(const std::string& i_section, const std::string& i_key, std::string& io_value, const std::string& i_fpath)
{
	CIniFile ini;
	if (ini.Load(i_fpath) == false)
	{
		return false;
	}
	if (ini.Get(i_section, i_key, io_value) == false)
	{
		return false;
	}
	return true;
}

bool hk::CIniFile::WritePrivateProfileString(const std::string& i_section, const std::string& i_key, const std::string& i_value, const std::string& i_fpath)
{
	CIniFile ini(i_fpath);
	ini.Set(i_section, i_key, i_value);
	if ( ini.Save(i_fpath)==false )
	{
		return false;
	}
	return true;
}

// 前後の空白を削除する※ASCII以外は注意
std::string hk::CIniFile::strTrim(const std::string& i_text, const std::string& i_chars)
{
	std::string t1 = strTrimStart(i_text, i_chars);
	std::string t2 = strTrimEnd(t1, i_chars);
	return t2;
}

// 前の空白を削除する※ASCII以外は注意
std::string hk::CIniFile::strTrimStart(const std::string& i_text, const std::string& i_chars)
{
	std::string::size_type pos = 0;
	while (true)
	{
		std::string::size_type tmp_pos = pos;
		for (int i = 0; i < i_chars.length(); i++)
		{
			char c = i_chars.at(i);
			tmp_pos = i_text.find_first_not_of(c, tmp_pos);
			if (tmp_pos == std::string::npos)
			{
				return "";
			}
		}
		if (pos == tmp_pos)
		{
			break;
		}
		pos = tmp_pos;
	}
	std::string res = i_text.substr(pos);
	return res;
}

// 後ろの空白を削除する※ASCII以外は注意
std::string hk::CIniFile::strTrimEnd(const std::string& i_text, const std::string& i_chars)
{
	std::string::size_type pos = i_text.length() - 1;
	while (true)
	{
		std::string::size_type tmp_pos = pos;
		for (int i = 0; i < i_chars.length(); i++)
		{
			char c = i_chars.at(i);
			tmp_pos = i_text.find_last_not_of(c, tmp_pos);
			if (tmp_pos == std::string::npos)
			{
				return "";
			}
		}
		if (pos == tmp_pos)
		{
			break;
		}
		pos = tmp_pos;
	}
	std::string res = i_text.substr(0, pos + 1);
	return res;
}

//std::string hk::CIniFile::shortToString(short i_val)
//{
//	//	return std::to_string((int)i_val);
//	std::stringstream ss;
//	ss << i_val;
//	return ss.str();
//}
//
//short hk::CIniFile::shortFromString(const std::string& i_val)
//{
//	short res = 0;
//	try
//	{
//		res = (short)std::stoi(i_val);
//	}
//	catch (std::string e)
//	{
//	}
//	return res;
//}
//
//std::string hk::CIniFile::intToString(int i_val)
//{
//	//return std::to_string(i_val);
//	std::stringstream ss;
//	ss << i_val;
//	return ss.str();
//}
//
//int hk::CIniFile::intFromString(const std::string& i_val)
//{
//	int res = 0;
//	try
//	{
//		res = std::stoi(i_val);
//	}
//	catch (std::string e)
//	{
//	}
//	return res;
//}
//
//std::string hk::CIniFile::floatToString(float i_val)
//{
//	//return std::to_string(i_val);
//	std::stringstream ss;
//	ss << i_val;
//	return ss.str();
//}
//
//float hk::CIniFile::floatFromString(const std::string& i_val)
//{
//	float res = 0;
//	try
//	{
//		res = std::stof(i_val);
//	}
//	catch (std::string e)
//	{
//	}
//	return res;
//}
//
//std::string hk::CIniFile::doubleToString(double i_val)
//{
//	//return std::to_string(i_val);
//	std::stringstream ss;
//	ss << i_val;
//	return ss.str();
//}
//
//double hk::CIniFile::doubleFromString(const std::string& i_val)
//{
//	double res = 0;
//	try
//	{
//		res = std::stod(i_val);
//	}
//	catch (std::string e)
//	{
//	}
//	return res;
//}
//
