#include "LandingHandler.h"
#include <random>

int LandingHandler::randomNumberGenerator(int i, int j)
{
	static thread_local std::mt19937 rng{ std::random_device{}() };
	return std::uniform_int_distribution<int>(i, j)(rng);
}




//Diğer thredlerle karışma olmaması adına içeride değiştirilen class değişkenlerini lokale atabdı
thread_local std::optional<std::map<std::string, Flight>::node_type> localNode;
thread_local Flight* localFlight = nullptr;
thread_local int localRemainLandTime = 0;
static std::mutex serviceGate; // Mutex for serviceHandler.


//CONSTRUCTOR. Aynı zamanda içeride logger oluşuyor.
LandingHandler::LandingHandler()
{
	logger = GlobalLogger::getInstance();
}

void LandingHandler::landingProcess(std::map<std::string, Flight>& flightRecords)
{
	
	while (true)
	{
		// Bu kısım kilit altında tutularak thread-safeliği sağlayan parça.
		{
			std::unique_lock<std::mutex> lock(refLock);

			// Flight nesnesi yoksa burası açılır
			if (!localNode)
			{
				// Kayıt dosyası boş değilse eğer buradan yeni Flight alınır
				if (!flightRecords.empty())
				{
					localNode.emplace(flightRecords.extract(flightRecords.begin()));	// Kopya oluşturmamak ve iterator kullanarak data race e neden olmamak adına Flight'ı mapten
					localFlight = &localNode->mapped();									// çıkarıp bir 2'li node'a atayarak kullanıyoruz. 
					
					localRemainLandTime = randomNumberGenerator(6, 13); // iniş sayacı başlat
				}

				// Kayıt dosyası boşsa uçuşlar bitmiş demektir. landging handler sona erer
				else
				{
					lock.unlock(); // Loggerin gecikme yapmaması için kilit açılır.

					logger->printInfo("Ucus kayit listesi bos. İnis sistemi beklemede");

					return;


				}

			}

		}


		// Uçak indiğinde logger ile yazı yazdır ve servive handleri çalıştır. Loggeri gecikme ve deadlockun önüne geçmemek adına kilit dışında kullanıyoruz.
		if (localRemainLandTime == 0)
		{

			logger->printInfo("Flight " + localFlight->getFlightNumber() + " has landed");

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
			localRemainLandTime--;
		}





		std::this_thread::sleep_for(std::chrono::seconds(1)); // her saniye 1 kez bu döngüyü çevir




	}

}


int LandingHandler::hasWork(std::map<std::string, Flight>& flightRecords)
{
	std::scoped_lock lock(refLock);
	return flightRecords.size();
}
