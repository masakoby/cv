#pragma once

#include <string>
#include <vector>

namespace hk
{
	class CIniFile
	{
	public:
		enum EType
		{
			TYPE_NULL,
			TYPE_COMMENT,
			TYPE_SECTION,
			TYPE_PARAMETER
		};

		struct SItem
		{
			std::string Text;
			EType Type;
			std::string Section;
			std::string Key;
			std::string Value;
			
			static SItem Null()
			{
				SItem res;
				res.Type = EType::TYPE_NULL;
				return res;
			}

			static SItem ParseText(const std::string& i_text)
			{
				SItem res = SItem::Null();
				res.Text = i_text;
				res.Type = TYPE_COMMENT;

				// 空白削除
				std::string text = strTrimStart(i_text);

				// 空文字判定
				if ( text.empty() )
				{
					return res;
				}

				// コメント行判定
				char c0 = text.at(0);
				if ( c0==';' || c0=='#' || c0=='/' )
				{
					return res;
				}

				// セクション行判定
				if ( c0=='[' )
				{
					std::string::size_type p = text.find(']');
					if ( p!=std::string::npos )
					{
						// セクション設定
						res.Type = EType::TYPE_SECTION;
						res.Section = strTrim(text.substr(1, p-1));
					}
				}
				else
				{
					// パラメータ行判定
					std::string::size_type p = text.find('=');
					if ( p!=std::string::npos )
					{
						std::string key = strTrim(text.substr(0, p));
						if ( key.empty()==false )
						{
							// パラメータ設定
							res.Type = EType::TYPE_PARAMETER;
							res.Key = strTrim(text.substr(0, p));
							res.Value = text.substr(p + 1);
						}
					}
				}
				return res;
			}

			static SItem FromComment(const std::string& i_text, const std::string& i_mark=";")
			{
				SItem res = SItem::Null();
				res.Text = i_mark + i_text;
				res.Type = EType::TYPE_COMMENT;
				return res;
			}

			static SItem FromSection(const std::string& i_section)
			{
				SItem res = SItem::Null();
				res.Text = "[" + i_section + "]";
				res.Type = EType::TYPE_SECTION;
				res.Section = i_section;
				return res;
			}

			static SItem FromParameter(const std::string& i_section, const std::string& i_key, const std::string& i_value)
			{
				SItem res = SItem::Null();
				res.Text = i_key + "=" + i_value;
				res.Type = EType::TYPE_PARAMETER;
				res.Section = i_section;
				res.Key = i_key;
				res.Value = i_value;
				return res;
			}
		};

	private:
		std::vector<SItem> m_items;

	public:
		CIniFile();
		CIniFile(const std::string& i_fpath);
		~CIniFile();

		void Clear();
		bool Load(const std::string& i_fpath);
		bool Save(const std::string& i_fpath);
		bool ExportCsvFile(const std::string& i_fpath);
	
		bool Get(const std::string& i_section, const std::string& i_key, std::string& io_value) ;
		void Set(const std::string& i_section, const std::string& i_key, const std::string& i_value);
		//bool Get(const std::string& i_section, const std::string& i_key, short& io_value);
		//void Set(const std::string& i_section, const std::string& i_key, short i_value);
		//bool Get(const std::string& i_section, const std::string& i_key, int& io_value);
		//void Set(const std::string& i_section, const std::string& i_key, int i_value);
		//bool Get(const std::string& i_section, const std::string& i_key, float& io_value);
		//void Set(const std::string& i_section, const std::string& i_key, float i_value);
		//bool Get(const std::string& i_section, const std::string& i_key, double& io_value);
		//void Set(const std::string& i_section, const std::string& i_key, double i_value);

		int GetItemCount() const {return (int)m_items.size(); }
		SItem GetItemAt(int i_index) const { return m_items[i_index]; }
		void EnumSection(std::vector<int>& o_index) const;
		void EnumParameter(std::vector<int>& o_index) const;
		int FindSection(const std::string& i_section) const;
		int FindParameter(const std::string& i_section, const std::string& i_key) const;

		void InsertComment(int i_index, const std::string& i_text, const std::string& i_mark = ";");

	private:
		void insertParameter(const std::string& i_section, const std::string& i_key, const std::string& i_value);

	public:
		static bool GetPrivateProfileString(const std::string& i_section, const std::string& i_key, std::string& io_value, const std::string& i_fpath);
		static bool WritePrivateProfileString(const std::string& i_section, const std::string& i_key, const std::string& i_value, const std::string& i_fpath);

	public:
		 static std::string strTrim(const std::string& i_text, const std::string& i_chars = " \t");
		 static std::string strTrimStart(const std::string& i_text, const std::string& i_chars = " \t");
		 static std::string strTrimEnd(const std::string& i_text, const std::string& i_chars = " \t");

		//static std::string shortToString(short i_val);
		//static short shortFromString(const std::string& i_val);
		//static std::string intToString(int i_val);
		//static int intFromString(const std::string& i_val);
		//static std::string floatToString(float i_val);
		//static float floatFromString(const std::string& i_val);
		//static std::string doubleToString(double i_val);
		//static double doubleFromString(const std::string& i_val);
	};
};

