
#include <string>
#pragma once

namespace kb
{

	//	INI file �`���̃t�@�C������f�[�^��ǂݎ��
	//	�ǂ݂Ƃ�Ȃ������ꍇ�A�߂�l���O�ƂȂ�B
	//	�ǂ݂Ƃꂽ�Ƃ��A�߂�l�ɓǂ݂Ƃ������������Ԃ�
	int read(const char* iPath, const char* iSection, const char* iKey, std::string& oValue);
	int write(const char* iPath, const char* iSection, const char* iKey, std::string& iValue);
	int write(const char* iPath, const char* iSection, const char* iKey, const char* iValue);

	//	INI file �`���̃t�@�C�����琮���f�[�^��ǂݎ��
	int read(const char* iPath, const char* iSection, const char* iKey, int& oValue);
	//	INI file �`���̃t�@�C�����琮���f�[�^��ǂݎ��
	int read(const char* iPath, const char* iSection, const char* iKey, short& oValue);
	//	INI file �`���̃t�@�C�����畂�������f�[�^��ǂݎ��
	int read(const char* iPath, const char* iSection, const char* iKey, double& oValue);
	int read(const char* iPath, const char* iSection, const char* iKey, float& oValue);

	//	INI file �`���̃t�@�C�����畂�������f�[�^��ǂݎ��
	int read_csv(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num);
	int read_space(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num);
	//	INI file �`���̃t�@�C�����畂�������f�[�^��ǂݎ��
	int write_csv(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num);
	int write_space(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num);

	int write(const char* iPath, const char* iSection, const char* iKey, double oValue);
	int write(const char* iPath, const char* iSection, const char* iKey, int oValue);

	//	INI file �`���̃t�@�C�����畂�������f�[�^��ǂݎ��
	int read_csv(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num);
	int read_space(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num);
	//	INI file �`���̃t�@�C�����畂�������f�[�^��ǂݎ��
	int write_csv(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num);
	int write_space(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num);

};