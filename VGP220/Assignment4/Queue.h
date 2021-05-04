#pragma once

//TODO: 5 - Implement a Queue class from scratch
//Remember that your queue should follow the FIFO standard (First In First Out)

template<typename T>
class Queue
{
public:
	Queue() : mCapacity(10), mCurrentSize(0)
	{
		mData = new T[mCapacity];
	}	
	Queue(int capacity) : mCapacity(capacity), mCurrentSize(0)
	{
		mData = new T[mCapacity];
	}
	~Queue()
	{
		delete mData;
		mData = nullptr;
	}
	//Inserts the data in the queue.
	void Enqueue(T data)
	{
		if (mCapacity == mCurrentSize)
		{
			std::cout << "Queue overflow!" << std::endl;
			return;
		}

		mData[mCurrentSize] = data;
		mCurrentSize++;
	}

	//Removes an element from the queue and returns this element in the output parameter
	//Also it returns true if the object was removed and false if the Queue is empty
	bool Daqueue(T& output)
	{
		if (mCurrentSize == 0)
		{
			std::cout << "The queue is empty!" << std::endl;
			return false;
		}

		for (int i = 0; i < mCurrentSize; ++i)
		{
			mData[i] = mData[i++];
		}

		mCurrentSize--;
		return true;
	}

	//Returns true if queue is empty, false otherwise
	bool isEmpty()
	{
		return mCurrentSize == 0;
	}

	//Display all the elements in the queue:
	//Example, lets suppose you inserted 1, 2, 3, 4, 5
	//Display should print: "front->1, 2, 3, 4, 5<-rear"
	void DisplayQueue()
	{

	}

private:
	int front;
	int rear;
	int mCurrentSize;
	int mCapacity;
	T* mData;
};