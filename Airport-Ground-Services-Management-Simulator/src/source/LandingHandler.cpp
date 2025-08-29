#include "LandingHandler.h"
#include <random>


 // Random number generator for better real life simulation by landing duration
int LandingHandler::randomNumberGenerator(int i, int j)
{
	static thread_local std::mt19937 rng{ std::random_device{}() };
	return std::uniform_int_distribution<int>(i, j)(rng);
}




//Defined local variables because prevent the conflicts between threads
thread_local std::optional<std::map<std::string, Flight>::node_type> localNode;
thread_local Flight* localFlight = nullptr;
thread_local int localRemainLandTime = 0;

// Mutex for serviceHandler.
static std::mutex serviceGate; 


//CONSTRUCTOR. And create logger at the begining
LandingHandler::LandingHandler()
{
	logger = GlobalLogger::getInstance();
}

void LandingHandler::landingProcess(std::map<std::string, Flight>& flightRecords)
{
	
	while (true)
	{
		//  The part locked with mutex for thread-safe
		{
			// Use unique lock for unlock after
			std::unique_lock<std::mutex> lock(refLock);

			// if Flight object is null , this part start work and give object from flightRecords
			if (!localNode)
			{
				// Get new flight if flightRecords not empty
				if (!flightRecords.empty())
				{
					localNode.emplace(flightRecords.extract(flightRecords.begin()));	//Extract and give the Flight to  a node for prevent data-race and avoid copying
					localFlight = &localNode->mapped();									   
					
					localRemainLandTime = randomNumberGenerator(6, 13); // Give random remain time between 6-13 
				}

				//  Flights are ended if records file is empty. Finish the landingHandler function 
				else
				{
					lock.unlock(); // Unlock the lock for logging. Two locks could make a deadlock

					logger->printInfo("Ucus kayit listesi bos. İnis sistemi beklemede");

					return;


				}

			}

		}


		// Uçak indiğinde logger ile yazı yazdır ve servive handleri çalıştır. Loggeri gecikme ve deadlockun önüne geçmemek adına kilit dışında kullanıyoruz.
		if (localRemainLandTime == 0)
		{

			logger->important("Flight " + localFlight->getFlightNumber() + " has landed");
			logger->lockInput();
			// DİKKAT: serviceHandler thread-safe olmalı; içeride kilit alma düzenini kontrol et


			// === KAPI: Tek-thread erişim ===
			{
				std::scoped_lock gateLock(serviceGate);

				serviceHandler.serviceHandler(localFlight, true);

			}


			// Bu thread'in durumunu sıfırla (diğer thread'leri etkilemez)
			{
				std::scoped_lock lock(refLock);
				localNode.reset();
				localFlight = nullptr;
			}



			return;
		}


		// Eğer süre bitmediyse uçağın inmesi için geri sayımı yazdır. Loggeri gecikme ve deadklockun önüne geçmek adına kilit dışında kullanıyoruz
		else
		{
			logger->printInfo("Flight " + localFlight->getFlightNumber() + " will land in " + std::to_string(localRemainLandTime) + " seconds");
			--localRemainLandTime;
		}


		std::this_thread::sleep_for(std::chrono::seconds(1)); // her saniye 1 kez bu döngüyü çevir




	}

}


int LandingHandler::hasWork(std::map<std::string, Flight>& flightRecords)
{
	std::scoped_lock lock(refLock);
	return flightRecords.size();
}
