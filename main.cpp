#include "stdio.h"
#include "stdlib.h"
#include "stable.h"
#include "util.h"

int g_syncTimerId = -1;

class SyncApplication : public QApplication
{
public:
	SyncApplication(int argc, char **argv) : QApplication(argc, argv) { ; }
	virtual void timerEvent(QTimerEvent *e)
	{
		if (e->timerId() != g_syncTimerId) return ;
		QDir dir("e:\\sync\\kindle\\sync");
		if (!dir.exists() || 2 >= dir.count()) return ;
		char c = getKindleDriverLetter();
		if (!c) return ;
		QString cmd;
		cmd = QString("cmd /c xcopy e:\\sync\\kindle\\sync %1:\\DK_Documents\\sync /Y")
			.arg(QChar(c));
		::system(cmd.toStdString().c_str());
		cmd = "cmd /c xcopy e:\\sync\\kindle\\sync e:\\sync\\kindle\\backup /Y /I";
		::system(cmd.toStdString().c_str());
		cmd = "cmd /c del e:\\sync\\kindle\\sync\\*.* /Q /S";
		::system(cmd.toStdString().c_str());
	}
private:
};

int main(int argc, char *argv[])
{
	SyncApplication a(argc, argv);

	g_syncTimerId = a.startTimer(1000);

	return a.exec();
}