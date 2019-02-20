#include<bits/stdc++.h>
using namespace std;

/*
 * Structure inspired by Geeks for Geeks https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
 * Does not use linear probing; each bucket is an array of values that can be sorted and binary searched
 */

//template for generic type
template<typename K, typename V>

class HashMap
{
	int tableCapacity = 1000;
    int bucketCapacity = 10;
	int size;

    //template for generic type
    template<typename K, typename V>
    struct HashNode
    {
        public:
            V values[bucketCapacity];
            K key;

        HashNode(K key)
        {
            for (int i = 0; i < values.length; i++)
                values[i] = NULL;
            this->key = key;
        }

        HashNode(K key, V values[])
        {
            this->values = values;
            this->key = key;
        }
    };
	//hash element array
	HashNode<K,V> **arr;
	//dummy node
	HashNode<K,V> *dummy;

	public:
	HashMap()
	{
		arr = new HashNode<K,V>*[tableCapacity];

		//Initialise all elements of array as NULL
		for(int i=0 ; i < tableCapacity ; i++)
			arr[i] = NULL;

		//dummy node with values and key -1
		dummy = new HashNode<K,V>(-1, -1);
	}
	// This implements hash function to find index
	// for a key
	int hashCode(K key)
	{
		return key % tableCapacity;
	}

	//Function to add key values pair
	void insertNode(K key, V value)
	{
		HashNode<K,V> *temp = new HashNode<K,V>(key, value);

		// Apply hash function to find index for given key
		int hashIndex = hashCode(key);

		//find next free space
		while(arr[hashIndex] != NULL && arr[hashIndex]->key != key
			&& arr[hashIndex]->key != -1)
		{
			hashIndex++;
			hashIndex %= tableCapacity;
		}

		//if new node to be inserted increase the current size
		if(arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
			size++;
		arr[hashIndex] = temp;
	}

	//Function to delete a key values pair
	V deleteNode(int key)
	{
		// Apply hash function to find index for given key
		int hashIndex = hashCode(key);

		//finding the node with given key
		while(arr[hashIndex] != NULL)
		{
			//if node found
			if(arr[hashIndex]->key == key)
			{
				HashNode<K,V> *temp = arr[hashIndex];

				//Insert dummy node here for further use
				arr[hashIndex] = dummy;

				// Reduce size
				size--;
				return temp->values;
			}
			hashIndex++;
			hashIndex %= tableCapacity;

		}

		//If not found return null
		return NULL;
	}

	//Function to search the values for a given key
	V get(int key)
	{
		// Apply hash function to find index for given key
		int hashIndex = hashCode(key);
		int counter=0;
		//finding the node with given key
		while(arr[hashIndex] != NULL)
		{ int counter =0;
			if(counter++>tableCapacity) //to avoid infinite loop
				return NULL;
			//if node found return its values
			if(arr[hashIndex]->key == key)
				return arr[hashIndex]->values;
			hashIndex++;
			hashIndex %= tableCapacity;
		}

		//If not found return null
		return NULL;
	}

	//Return current size
	int sizeofMap()
	{
		return size;
	}

	//Return true if size is 0
	bool isEmpty()
	{
		return size == 0;
	}

	//Function to display the stored key values pairs
	void display()
	{
		for(int i=0 ; i<tableCapacity ; i++)
		{
			if(arr[i] != NULL && arr[i]->key != -1)
				cout << "key = " << arr[i]->key
					<<" values = "<< arr[i]->values << endl;
		}
	}
};

//Driver method to test map class
int main()
{
	HashMap<int, long long> *h = new HashMap<int, long long>;
	h->insertNode(1,1);
	h->insertNode(2,2);
	h->insertNode(2,3);
	h->display();
	cout << h->sizeofMap() <<endl;
	cout << h->deleteNode(2) << endl;
	cout << h->sizeofMap() <<endl;
	cout << h->isEmpty() << endl;
	cout << h->get(2);

	return 0;
}
