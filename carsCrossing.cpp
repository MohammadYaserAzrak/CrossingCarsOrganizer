#include <QSemaphore>
#include <QMutex>
#include <QThread>
#include <iostream>

QSemaphore road(2);
QMutex block;

class car : public QThread
{
private:
	int id, dir; // 1 = West, 2 = East
public:
	car(int ID, int DIR) : id(ID), dir(DIR) {}

	void run()
	{
		if (dir == 1) // West
		{
			block.lock();
			std::cout << "Car " << id << " is waiting to cross" << std::endl;
			block.unlock();
			road.acquire(1);
			block.lock();
			std::cout << "Car " << id << " is crossing from east to west" << std::endl;
			block.unlock();
			srand(time(0));
			sleep(rand() % 5);
			block.lock();
			std::cout << "Car " << id << " finished crossing" << std::endl;
			block.unlock();
			road.release(1);
		}
		else if (dir == 2) // East
		{
			block.lock();
			std::cout << "Car " << id << " is waiting to cross" << std::endl;
			block.unlock();
			road.acquire(2);
			block.lock();
			std::cout << "Car " << id << " is crossing from west to east" << std::endl;
			block.unlock();
			srand(time(0));
			sleep(rand() % 5);
			block.lock();
			std::cout << "Car " << id << " finished crossing" << std::endl;
			block.unlock();
			road.release(2);
		}
	}
};

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage <cars>" << std::endl;
		exit(1);
	}

	int nCars = atoi(argv[1]);
	car *cars[nCars];
	srand(time(0));
	int dir = 0;

	for (int i = 0; i < nCars; i++)
	{
		dir = rand() % 2 + 1;
		cars[i] = new car(i, dir);
		cars[i]->start();
	}

	for (int i = 0; i < nCars; i++)
	{
		cars[i]->wait();
	}

	for (int i = 0; i < nCars; i++)
	{
		delete cars[i];
	}

	return 0;
}
