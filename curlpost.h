#ifndef CURLPOST_H
#define CURLPOST_H 1

#include <QString>
#include <QByteArray>
#include <QThread>

// ---
class CurlpostException
{
 private:
  QString data;
 public:
  explicit CurlpostException (const QString & d = "") : data(d) {}
  virtual const QString & what() const 
  {
    return data;
  }
  virtual ~CurlpostException () {}
};

// ---
class Curlpost
{
public:
  Curlpost () { init(); }
  ~Curlpost () { cleanup(); }

  void send (const QString & target,
	     const QByteArray & data, 
	     QString & readbuffer,
	     bool useTorProxy = false);
        /* throw (CurlpostException) */

  // Curlpost::is_Tor_on -- Check if Tor circuit is active on this host
  //
  bool is_Tor_on (const int torport = 9050);
        /* throw (CurlpostException) */

private:
  void init ();
  void cleanup ();
};

// --
class CurlpostWorker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QString &parameter)
    {
      Curlpost curlpost;
      for (;;)
        {
          try
            {
              if (curlpost.is_Tor_on())
                {
                    emit resultReady("Tor is ON");
                }
              else
                {
                    emit resultReady("Tor is OFF");
                }
             }
          catch (CurlpostException excp)
            {
              emit resultReady("Tor is OFF");
            }
          QThread::sleep(3*60); // 3 minutes
        }
    }

signals:
    void resultReady(const QString &result);
};

class CurlpostController : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    CurlpostController() 
      {
	CurlpostWorker * worker = new CurlpostWorker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker,
		&QObject::deleteLater);
        connect(this, &CurlpostController::operate, worker,
		&CurlpostWorker::doWork);
        connect(worker, &CurlpostWorker::resultReady, this,
		&CurlpostController::handleThemResults);
        workerThread.start();
    }
    ~CurlpostController() 
      {
        workerThread.quit();
        workerThread.wait();
      }
public slots:
     void handleThemResults(const QString & results)
        {
	  emit themResultsReady(results);
	}
signals:
    void operate(const QString &);
    void themResultsReady(const QString & result);
};

#endif // CURLPOST_H
