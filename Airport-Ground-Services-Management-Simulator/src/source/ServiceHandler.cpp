#include "ServiceHandler.h"



void ServiceHandler::serviceHandler(Flight* landingFlight, bool adding)
{
	bool loop=true;
	std::string loopInput;
	int serviceInput;
	

	while (loop)
	{
		logger->printInfo("Will you add any tasks? (Y/N) ");

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

	switch (fuelInput)
	{
	case 0:
		adding ? landingFlight->addDemandingServices(FuelTasks::RefuelPlane) : landingFlight->removeDemandingServices(FuelTasks::RefuelPlane);
	case 1:
		adding ? landingFlight->addDemandingServices(FuelTasks::RefuelTank) : landingFlight->removeDemandingServices(FuelTasks::RefuelTank);
	case 2:
		adding ? landingFlight->addDemandingServices(FuelTasks::TransportFuel) : landingFlight->removeDemandingServices(FuelTasks::TransportFuel);
	default:
		break;
	}



}

void ServiceHandler::cleaningTaskHandler(Flight* landingFlight, bool adding)
{
	int cleaningInput;
	logger->printInfo( "Please choose the task for add  ---> 0 = Daily , 1 = Weekly , 2 = Monthly , 3 = Yearly ") ;
	std::cin >> cleaningInput;

	switch (cleaningInput)
	{
	case 0:
		adding ? landingFlight->addDemandingServices(CleaningTasks::Daily) : landingFlight->removeDemandingServices(CleaningTasks::Daily);
	case 1:
		adding ? landingFlight->addDemandingServices(CleaningTasks::Weekly) : landingFlight->removeDemandingServices(CleaningTasks::Weekly);
	case 2:
		adding ? landingFlight->addDemandingServices(CleaningTasks::Monthly) : landingFlight->removeDemandingServices(CleaningTasks::Monthly);
	case 3:
		adding ? landingFlight->addDemandingServices(CleaningTasks::Yearly) : landingFlight->removeDemandingServices(CleaningTasks::Yearly);
	default:
		break;
	}



}

void ServiceHandler::luggageTaskHandler(Flight* landingFlight, bool adding)
{
	int luggageInput;
	logger->printInfo ("Please choose the task for add  ---> 0 = Load Luggage , 1 = UnloadLuggage , 2 = Transport Luggage" );
	std::cin >> luggageInput;

	switch (luggageInput)
	{
	case 0:
		adding ? landingFlight->addDemandingServices(LuggageTasks::LoadLuggage) : landingFlight->removeDemandingServices(LuggageTasks::LoadLuggage);
	case 1:
		adding ? landingFlight->addDemandingServices(LuggageTasks::UnloadLuggage) : landingFlight->removeDemandingServices(LuggageTasks::UnloadLuggage);
	case 2:
		adding ? landingFlight->addDemandingServices(LuggageTasks::TransportLuggage) : landingFlight->removeDemandingServices(LuggageTasks::TransportLuggage);

	default:
		break;
	}



}