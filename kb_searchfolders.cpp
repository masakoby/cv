#include "kb_searchfolders.h"
#include <io.h>
#include "kb_os.h"



#ifdef WINDOWS

int kb::search_folders(
	const std::string& iDirname,
	const char* iStrext1,
	std::vector<std::string>& foldernames
)
{
	struct _finddata_t header_file;
	intptr_t hFile = 0;

	if ((hFile = _findfirst((iDirname + iStrext1).c_str(), &header_file)) == -1L)
		return -1;

	while (_findnext(hFile, &header_file) == 0) {

		// skip "."".."
		if (header_file.name[0] == '.')
			continue;

		//	skip directories name
		if (header_file.attrib&_A_SUBDIR) {
			std::string fname = header_file.name;
			foldernames.push_back(fname);
		}

	}

	return 0;
}
#endif
