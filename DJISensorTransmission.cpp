#include "vehicle.hpp"
#include "mobile_communication.hpp"
#include "DJISensorFileReader.hpp" 

using namespace DJI;
using namespace DJI::OSDK;

int main(int argc, char** argv)
{
		Vehicle* vehicle = setupOSDK(argc, argv);
		if (vehicle == NULL)
		{
				std::cout << "Vehicle not initialized, exiting.\n";
				return -1;
		}

		setupMSDKParsing(vehicle);

		delete (vehicle);
		return 0;
}


bool setupMSDKParsing()
{
		MobileCommunication::setFromMSDKCallback(parseFromMobileCallback);
		std::cout << "Listening to mobile commands. Press any key to exit.\n";
		char a;
		std::cin >> a;
		return true;
}

void parseFromMobileCallback(RecvContainer recvFrame, UserData userData)
{
		uint16_t mobile_data_id;
		mobile_data_id = *(reinterpret_cast<uint16_t*>(&recvFrame.recvData.raw_ack_array));

		switch (mobile_data_id)
		{
				case 44:
						sendSensorDataToMobileDevice(sendSensorDataCallback);
						break;
				default:
						break;
		}
}

void sendSensorDataCallback(Vehicle* vehiclePtr, RecvContainer recvFrame, UserData userData)
{
		char *sensorBuffer = new char[100];
		int sensorDataByte;
		sensorDataByte = DJISensorFileReader::read_pm25(sensorBuffer, 90);
		//Protocol::send(0, 0, OpenProtocol::CMDSet::Activation::toMobile, sensorBuffer, sensorDataByte, 500, 1, NULL, 0);
		vehiclePtr->moc->sendDataToMSDK(sensorBuffer, sensorDataByte);
		ACK::getErrorCodeMessage("PM25 SENSOR DATA", __func__);

		delete [] sensorBuffer;
}
