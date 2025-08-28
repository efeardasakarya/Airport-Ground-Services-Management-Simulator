#include "ServiceHandler.h"



void ServiceHandler::serviceHandler(Flight* landingFlight, bool adding)
{
	bool loop=true;
	std::string loopInput;
	int serviceInput;
	
	
	
	while (loop)
	{
		
		std::this_thread::sleep_for(std::chrono::milliseconds(500) );  // 0.5 sn gecikme

		logger->printInfo(landingFlight->getFlightNumber() + ": Will you add any tasks? (Y/N) ");
		

		std::cin >> loopInput;


		if (loopInput == "Y" || loopInput == "y")
		{
			
			logger->printInfo("Please choose the task you add/remove  ---> 0 = Luggage , 1 = Cleaning , 2 = Fuel ");
			std::cin >> serviceInput;

			switch (serviceInput)
			{
			case 0:
				luggageTaskHandler(landingFlight, adding);
				break;
			case 1:
				cleaningTaskHandler(landingFlight, adding);
				break;
			case 2:
				fuelTaskHandler(landingFlight, adding);
				break;
			default:
				logger->printError("Please enter a valid number");
			}
		}

		else if (loopInput == "N" || loopInput == "n")
		{
			loop = false;
			break;
		}

		else
		{
			logger->printInfo("Invalid input. Please try again");
			
		}



	}
		
}

void ServiceHandler::fuelTaskHandler(Flight* landingFlight, bool adding)
{
	int fuelInput;
	logger->printInfo( "Please choose the task for add ---> 0 = Refuel Plane , 1 = Refuel Tank , 2 = TransportFuel ");
	std::cin >> fuelInput;
	FuelTasks task;

	switch (fuelInput)
	{
	case 0:
		task = FuelTasks::RefuelPlane;
		break;
	case 1:
		task = FuelTasks::RefuelTank;
		break;
	case 2:
		task = FuelTasks::TransportFuel;
		break;
	default:
		logger->printError("Invalid Input");
		break;
	}

	if (adding)
	{
		landingFlight->addDemandingServices(task);
	}
	else
	{
		landingFlight->removeDemandingServices(task);
	}


}

void ServiceHandler::cleaningTaskHandler(Flight* landingFlight, bool adding)
{
	int cleaningInput;
	logger->printInfo( "Please choose the task for add  ---> 0 = Daily , 1 = Weekly , 2 = Monthly , 3 = Yearly ") ;
	std::cin >> cleaningInput;
	CleaningTasks task;

	switch (cleaningInput)
	{
	case 0:
		task = CleaningTasks::Daily;
		break;
	case 1:
		task = CleaningTasks::Weekly;
		break;
	case 2:
		task = CleaningTasks::Monthly;
		break;
	case 3:
		task = CleaningTasks::Yearly;
		break;
	default:
		logger->printError("Invalid Input");
		break;
	}

	if (adding)
	{
		landingFlight->addDemandingServices(task);
	}
	else
	{
		landingFlight->removeDemandingServices(task);
	}



}

void ServiceHandler::luggageTaskHandler(Flight* landingFlight, bool adding)
{
	int luggageInput;
	logger->printInfo ("Please choose the task for add  ---> 0 = Load Luggage , 1 = UnloadLuggage , 2 = Transport Luggage" );
	std::cin >> luggageInput;
	LuggageTasks task;

	switch (luggageInput)
	{
	case 0:
		task = LuggageTasks::LoadLuggage;
		break;
	case 1:
		task = LuggageTasks::UnloadLuggage;
		break;
	case 2:
		task = LuggageTasks::TransportLuggage;
		break;
	default:
		logger->printError("Invalid Input");
		break;
	}

	if (adding)
	{
		landingFlight->addDemandingServices(task);
	}
	else
	{
		landingFlight->removeDemandingServices(task);
	}
}

