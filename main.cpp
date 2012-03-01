#include "stdio.h"
#include "stdlib.h"
#include "stable.h"
#include "util.h"

int g_syncTimerId = -1;

class SyncApplication : public QCoreApplication
{
public:
	SyncApplication(int argc, char **argv) : QCoreApplication(argc, argv) { ; }

	virtual void timerEvent(QTimerEvent *e)
	{
		if (e->timerId() != g_syncTimerId) return ;
		doSync("kindle",
			"e:\\sync\\kindle\\sync",
			"e:\\sync\\kindle\\backup",
			"%1:\\DK_Documents\\sync");
		doSync("defy",
			"e:\\sync\\defy\\sync",
			"e:\\sync\\defy\\backup",
			"%1:\\sync");
	}
private:
};

int main(int argc, char *argv[])
{
	SyncApplication a(argc, argv);

	g_syncTimerId = a.startTimer(1000);

	return a.exec();
}