#include "stable.h"
#include "util.h"
// Function to retrieve volume names

char getKindleDriverLetter()
{
	DWORD res = ::GetLogicalDrives();
	if (0 == res) return 0;
	for (int i = 0; i < 31; ++ i)
	{
		if (!(1 << i & res)) continue;
		char root[4] = "C:\\";
		root[0] = 'A' + i;
		char buf[MAX_PATH + 1] = {0};
		bool b = ::GetVolumeInformationA(root, buf, _countof(buf), 0, 0, 0, 0, 0);
		if (!b) continue;
		if (0 != ::_strnicmp(buf, "kindle", _countof(buf))) continue;
		return root[0];
	}
	return 0;
}