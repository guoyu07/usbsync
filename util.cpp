#include "stable.h"
#include "util.h"
// Function to retrieve volume names

QChar getDriverLetter(const QString label)
{
	X_ASSERT(!label.isNull()); // usb device must have a unique label
	if (label.isNull()) return 0;
	QFileInfoList drivers = QDir::drives();
	foreach(QFileInfo fi, drivers)
	{
		QString s = fi.canonicalFilePath();
		char buf[MAX_PATH + 1] = {0};
		bool b = ::GetVolumeInformationA(
			s.toStdString().c_str(), 
			buf,
			_countof(buf),
			0, 0, 0, 0, 0);
		if (!b) continue;
		if (0 != label.compare(buf, Qt::CaseInsensitive)) continue;
		return s.at(0);
	}
	return 0;
}

QStringList enumFiles(const QString &folder)
{
	QStringList result;
	QDir dir(folder);
	if (!dir.exists()) return result;
	QFileInfoList files = dir.entryInfoList(
		QStringList() << "*", 
		QDir::Files);
	foreach(QFileInfo fi, files)
	{
		result << fi.canonicalFilePath();
	}
	files.clear();
	QFileInfoList dirs = dir.entryInfoList(
		QStringList() << "*",
		QDir::AllDirs | QDir::NoDotAndDotDot);
	foreach(QFileInfo fi, dirs)
	{
		result << enumFiles(fi.canonicalFilePath());
	}
	dirs.clear();
	return result;
}

// src : e:\\sync\\kindle\\sync
// bak : e:\\sync\\kindle\\backup
// dst : %1:\\DK_Documents\\sync
bool doSync(const QString &label,
			const QString &src, 
			const QString &bak, 
			const QString &dst)
{
	QChar c = getDriverLetter(label);
	if (c.isNull()) return false;
	int count = enumFiles(src).size();
	if (0 == count) return false;
	QString cmd;
	cmd = QString("cmd /c xcopy \"%1\" \"%2\" /Y /I /S").arg(src).arg(dst);
	cmd = cmd.arg(c);
	::system(cmd.toStdString().c_str());
	cmd = QString("cmd /c xcopy \"%1\" \"%2\" /Y /I /S").arg(src).arg(bak);
	::system(cmd.toStdString().c_str());
	cmd = QString("cmd /c del \"%1\\*.*\" /Q /S").arg(src);
	::system(cmd.toStdString().c_str());
	return true;
}