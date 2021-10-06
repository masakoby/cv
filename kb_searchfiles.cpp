#include "kb_searchfiles.h"
#include <io.h>
#include "kb_os.h"


#ifdef WINDOWS

int kb::search_files(
	const std::string iDirname,
	const char* iStrext1,
	std::vector<std::string>& oVec1
)
{
	std::string strext1 = iStrext1;

	struct _finddata_t header_file;
	intptr_t hFile = 0;

	if ((hFile = _findfirst((iDirname + strext1).c_str(), &header_file)) == -1L)
		return -1;

	// �����������O��A�����ĐV�����p�X���쐬
	oVec1.push_back(header_file.name);

	//	DICOM File ��ǂݍ���ŒP����臒l���������Ă݂�
	int kk = 0;
	while (_findnext(hFile, &header_file) == 0) {

		// �P�����ڂ�"."".."�Ƃ��͖������đ��s
		if (header_file.name[0] == '.')
			continue;

		// �����������O��A�����ĐV�����p�X���쐬
		oVec1.push_back(header_file.name);

		kk++;
	}
	return kk;
}
#endif

#ifdef LINUX
int kb::search_files(
	const std::string iDirname,
	const char* iStrext1,
	std::vector<std::string>& oVec1
)
{

	//std::string path(iDirname);
	//std::string ext(iStrext1);
	int kk = 0;
	for (auto& p : std::experimental::filesystem::recursive_directory_iterator(iDirname))
	{
		if (p.path().extension() == iStrext1)
		{
			// �����������O��A�����ĐV�����p�X���쐬
			oVec1.push_back(p.path().filename());
		}
		//std::cout << p << '\n';
		kk++;
	}
	return kk;
}

#endif

