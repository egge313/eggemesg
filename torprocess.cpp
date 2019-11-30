#include "torprocess.h"
#include <QProcess>

void TorProcessThread::launch ()
{
  m_torprocess.setProgram(m_command);
  m_torprocess.setArguments(m_args);

  /*
void 	errorOccurred(QProcess::ProcessError error)
void 	finished(int exitCode, QProcess::ExitStatus exitStatus)
void 	readyReadStandardError()
void 	readyReadStandardOutput()
void 	started()
void 	stateChanged(QProcess::ProcessState newState)
  */

  QObject::connect(&m_torprocess, 
		   SIGNAL(finished(int /* exitCode */,
				   QProcess::ExitStatus)),
		   this,
		   SLOT(finishedHandler(int, QProcess::ExitStatus)));

  m_finished = false;

  m_torprocess.start();
}

void TorProcessThread::readall (QString & stdout_dat, QString & stderr_dat)
{
  QByteArray out_dat = m_torprocess.readAllStandardOutput();
  stdout_dat = out_dat;
  QByteArray err_dat = m_torprocess.readAllStandardError();
  stderr_dat = err_dat;
}

void TorProcessThread::finishedHandler(int exitcode, 
				       QProcess::ExitStatus exitstatus)
{
  QString stdoutmsg;
  QString stderrmsg;
  QString exitcodestr;
  exitcodestr.setNum(exitcode);

  switch (exitstatus)
    {
    case QProcess::NormalExit:
      m_readbuffer << "Normal exit, code = " << exitcodestr << ".";
      break;
    case QProcess::CrashExit:
      m_readbuffer << "Crashed.";
      break;
    }
  readall(stdoutmsg, stderrmsg);
  m_readbuffer << stdoutmsg << stderrmsg;
  m_finished = true;
}


// -- end torprocess.cpp
