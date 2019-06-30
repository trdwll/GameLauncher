#pragma once

#include <QObject>
#include <QStringList>

class Utils : public QObject
{
	Q_OBJECT

private:

	class QNetworkReply* m_CurrentReply;

public:
	Utils(QObject *parent);
	~Utils();


	static QString ConvertToHuman(float Size)
	{
		QStringList list;
		list << "KB" << "MB" << "GB" << "TB";

		QStringListIterator i(list);
		QString unit("bytes");

		while (Size >= 1024.0 && i.hasNext())
		{
			unit = i.next();
			Size /= 1024.0;
		}
		return QString().setNum(Size, 'f', 2) + " " + unit;
	}
};
