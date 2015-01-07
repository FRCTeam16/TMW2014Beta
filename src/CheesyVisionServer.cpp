#include "CheesyVisionServer.h"
#include "WPILib.h"
#include "networktables2/util/EOFException.h"
using namespace std;

CheesyVisionServer *CheesyVisionServer::_instance = (CheesyVisionServer *) 0;

#define HEARTBEAT_TIMEOUT 1.0

CheesyVisionServer::CheesyVisionServer(int port)
{
    cout << "CheesyVisionServer Constructor Start" << endl;
	_listenPort = port;
    _counting = false;
    _curLeftStatus = false;
    _curRightStatus = false;
    _lastHeartbeatTime = Timer::GetFPGATimestamp();
    _leftCount = 0;
    _rightCount = 0;
    _totalCount = 0;
    _listening = false;

    cout << "CheesyVisionServer Constructor Complete" << endl;

}

void CheesyVisionServer::Run()
{
	cout << "Running Cheesy Vision Server" << endl;

    if (_listening == false) return;    //Make sure we are listening
	SocketServerStreamProvider *sock;
	sock = new SocketServerStreamProvider(_listenPort);
	while (_listening)
	{
		try
		{
			 IOStream *stream = sock->accept();
					_lastHeartbeatTime = Timer::GetFPGATimestamp();
			while (Timer::GetFPGATimestamp() < _lastHeartbeatTime + HEARTBEAT_TIMEOUT && _listening)
			{
				try
				{
					uint8_t byte;
					stream->read(&byte, 1);
					_curLeftStatus = (byte & (1 << 1)) > 0;
					_curRightStatus = (byte & (1 << 0)) > 0;
					UpdateCounts(_curLeftStatus,_curRightStatus);
					_lastHeartbeatTime = Timer::GetFPGATimestamp();
					cout << "CheesyRead Good   _listening =" << _listening << endl;
				}
				catch (EOFException e)
				{
					//End of file, wait for a bit and read some more
					cout << "CheesyRead Failed" << endl;
					Wait(0.05);
				}

			}
			cout << "New Socket";
			delete stream;//close, delete and recreate the stream
		}
		catch (IOException e)
		{
			printf("Socket IO error: %s\n", e.what());
			//Catching this exception will dro
		}
	}
	cout << "Done Listening" << endl;
	Wait(0.05);

    delete sock;

}

void CheesyVisionServer::Reset()
{
    _leftCount = 0;
    _rightCount = 0;
    _totalCount = 0;

    _curLeftStatus = false;
    _curRightStatus = false;
}

void CheesyVisionServer::UpdateCounts(bool left, bool right)
{
    if (true == _counting)
    {
        _leftCount += left ? 1 : 0;
        _rightCount += right ? 1 : 0;
        _totalCount++;
    }
}

CheesyVisionServer *CheesyVisionServer::GetInstance()
{
    if (CheesyVisionServer::_instance == (CheesyVisionServer *) 0)
    {
        CheesyVisionServer::_instance = new CheesyVisionServer();

    }
    return CheesyVisionServer::_instance;
}

bool CheesyVisionServer::HasClientConnection()
{
    return (_lastHeartbeatTime > 0) && (Timer::GetFPGATimestamp() - _lastHeartbeatTime);
}
