#include "torprocess.h"

void TorProcessThread::launch ()
{
  m_torprocess.setProgram(m_command);
  m_torprocess.setArguments(m_args);
  m_torprocess.start();
}

void TorProcessThread::readall (QString & stdout_dat, QString & stderr_dat)
{
  QByteArray out_dat = m_torprocess.readAllStandardOutput();
  stdout_dat = out_dat;
  QByteArray err_dat = m_torprocess.readAllStandardError();
  stderr_dat = err_dat;
}

// -- end torprocess.cpp
