#include <iostream>

using namespace std;

struct IntArray
{
  int* data;
  int size;
};

void create(IntArray* arr, int size)
{
    arr->data = new int [size];
    arr->size = size;
}

void create(IntArray& arr, int size)
{
    arr.data = new int [size];
    arr.size = size;
}

int get(IntArray* arr, int index)
{
    if (arr->size > index)
    {
   return arr->data[index];
    }
    else
    {
        cout << "Error";
        exit(1);
    }
}

int get(IntArray& arr, int index)
{
    if (arr.size > index)
    {
   return arr.data[index];
    }
    else
    {
        cout << "Error";
        exit(1);
    }
}

void set(IntArray* arr, int index, int value)
{
     if (arr->size > index)
     {
      arr->data[index] = value;
     }
     else
     {
         cout << "Error";
         exit(1);
     }
}

void set(IntArray& arr, int index, int value)
{
     if (arr.size > index)
     {
      arr.data[index] = value;
     }
     else
     {
         cout << "Error";
         exit(1);
     }
}

void print(IntArray* arr)
{
    cout << "[";
    for (int i = 0; i < arr->size; i++)
    {
        if(i < arr->size - 1){
            cout <<get(arr, i)<< ", ";
        }
        else if (i == (arr->size - 1)){
            cout <<get(arr, i);
        }
    }
    cout << "]"<<endl;
}

void print(IntArray& arr)
{
    cout << "[";
    for (int i = 0; i < arr.size; i++)
    {
        if(i < arr.size - 1){
            cout <<get(arr, i)<< ", ";
        }
        else if (i == (arr.size - 1)){
            cout <<get(arr, i);
        }
    }
    cout << "]" << endl;
}

void resize(IntArray* arr, int newSize)
{
    int* arr2 = new int [newSize];
    if (arr->size < newSize)
    {
        for (int i = 0; i < arr->size; i++)
        {
            arr2[i] = arr->data[i];
        }
        for (int i = arr->size; i< newSize; i++)
        {
            arr2[i]=0;
        }
        delete[] arr->data;
        arr->data = arr2;
        arr->size = newSize;
    }
    else if (arr->size > newSize)
    {
        for (int i = 0; i < newSize; i++)
        {
            arr2[i] = arr->data[i];
        }

        delete[] arr->data;
        arr->data = arr2;
        arr->size = newSize;
    }
}

void resize(IntArray& arr, int newSize)
{
    int* arr2 = new int [newSize];
    if (arr.size < newSize)
    {
        for (int i = 0; i < arr.size; i++)
        {
            arr2[i] = arr.data[i];
        }
        for (int i = arr.size; i< newSize; i++)
        {
            arr2[i]=0;
        }
        delete[] arr.data;
        arr.data = arr2;
        arr.size = newSize;
    }
    else if (arr.size > newSize)
    {
        for (int i = 0; i < newSize; i++)
        {
            arr2[i] = arr.data[i];
        }

        delete[] arr.data;
        arr.data = arr2;
        arr.size = newSize;
    }
}

void destroy(IntArray* arr)
{
    if (arr->data != nullptr)
    {
    delete [] (arr->data);
    arr->data = nullptr;
    arr->size = 0;
    }
}
void destroy(IntArray& arr)
{
    if (arr.data != nullptr)
    {
    delete [] (arr.data);
    arr.data = nullptr;
    arr.size = 0;
    }
}

int main()
{
  IntArray nazvanie;
  create(nazvanie, 30);
  for (int i=0; i<30; i++)
  {
      set(nazvanie, i, i+1);
  }

  print(nazvanie);

  resize(nazvanie, 50);

  print (nazvanie);

  resize (nazvanie, 10);

  print(nazvanie);

  destroy(nazvanie);
}
