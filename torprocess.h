#ifndef TORPROCESS_H
#define TORPROCESS_H 1

// TorProcess -- Start the Tor process with the right options.

#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QThread>

class TorProcessThread : public QThread
{
  Q_OBJECT

public:
  TorProcessThread (const QString & command, const QStringList & args) 
    : m_torprocess(),
    m_command(command),
    m_args(args),
    m_finished(false),
    m_erroroccurred(false)
    {
      // Handling signal 'finished'
      //
      QObject::connect(&m_torprocess,
	      QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
	      [=](int exitCode, QProcess::ExitStatus exitStatus)
	      {
		switch(exitStatus)
		  {
		  case QProcess::NormalExit:
		    m_exitstatus = new QString("NormalExit");
		    break;
		  case QProcess::CrashExit:		    
		    m_exitstatus = new QString("CrashExit");
		    break;
		  default:
		    {
		      m_exitstatus = new QString("error");
		    }
		  }
		m_finished = true;
		emit torProcessDone();
	      }
	      );

      // Handling signal 'errorOccurred'
      //
      m_errormessage = QString("");
      QObject::connect(&m_torprocess,
	      QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
		     [=](QProcess::ProcessError error)
		       {
			 switch (error)
			   {
			   case QProcess::FailedToStart:
			     m_errormessage = QString() +
			       "The process failed to start. " +
			       "Either the invoked program is missing, or " +
			       "you may have insufficient permissions to " +
			       "invoke the program.";
			     break;
			   case QProcess::Crashed:
			     m_errormessage = QString() +
			       "The process crashed some time " +
			       "after starting successfully.";
			     break;
			   case QProcess::Timedout:
			     m_errormessage = QString() +
			       "The last waitFor...() function "+
			       "timed out. The state of QProcess is " +
			       "unchanged, and you can try calling " +
			       "waitFor...() again.";
			     break;
			   case QProcess::WriteError:
			     m_errormessage = QString() +
			       "An error occurred when " +
			       "attempting to write to the process. For " +
			       "example, the process may not be running, " +
			       "or it may have closed its input channel.";
			     break;
			   case QProcess::ReadError:
			     m_errormessage = QString() +
			       "An error occurred when " +
			       "attempting to read from the process. For " +
			       "example, the process may not be running.";
			     break;
			   case QProcess::UnknownError:
			     m_errormessage = QString() +
			       "An unknown error occurred. " +
			       "This is the default return value of error().";
			     break;
			   default:
			     m_errormessage = QString() +
			       "Qt error. This should not happen.";
			   }
			 m_erroroccurred = true;
			 emit torProcessSignal(m_errormessage);
		       }
		       );
    }

  // run -- Start a thread, hence the overload from QThread::run()
  //
  void run() override
  {
    launch();
    emit torProcessDone();
  }

signals:
    void torProcessSignal(const QString &s);
    void torProcessDone();    

public slots:
  void finishedHandler(int exitcode, QProcess::ExitStatus exitstatus);

public:
  void launch ();
  void readall (QString & stdout_dat, QString & stderr_dat);
  bool isfinished () { return m_finished; }
  bool erroroccurred () { return m_erroroccurred; }  
  void geterrormessage (QString & errmsg) { errmsg = m_errormessage; }
  void setargs(QStringList & args) { m_args = args; }
  virtual ~TorProcessThread () {}

private:
    QProcess     m_torprocess;
    QString      m_command;
    QStringList  m_args;
    QString    * m_exitstatus = nullptr;
    QString      m_errormessage;
    bool         m_finished;
    bool         m_erroroccurred;
    QStringList  m_readbuffer;
};


// TorProcessWorkerThread -- Because it is easier to run a thread to check
//                              that things are okay
//

/*
class TorControllerWorkerThread : public QThread
{
    Q_OBJECT

 public:
    TorControllerWorkerThread (TorController & torcontroller) :
       m_torcontroller(torcontroller) {}

    void run() override
    {
        QString result;
	m_torcontroller.launch();
        emit resultReady(result);
    }
signals:
    void resultReady(const QString &s);

 private:
    TorController m_torcontroller;

};

void MyObject::startWorkInAThread()
{
    WorkerThread *workerThread = new WorkerThread(this);
    connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}
*/

#endif // TORPROCESS_H
