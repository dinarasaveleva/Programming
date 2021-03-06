#include <iostream>

using namespace std;

int *create (int size, int a = 0, int p = 0)
{
   int *arr = new int [size];
   int temp = a;
   for (int i = 0; i < size; i++)
   {
       arr[i] = temp;
       temp += p;
   }
    return arr;
}

int *print (int *arr, int size)
{
    cout << "[";
    for (int i = 0; i < size; i++)
    {
        if(i < size - 1){
            cout <<arr[i]<< ", ";
        }
        else if (i == (size - 1)){
            cout <<arr[i];
        }
    }
    cout << "]";

    return arr;
}

int *sort (int *arr, int size)
{
    int c=0;
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j>0 && arr[j-1]>arr[j];j--)
        {
              c++;
              int m=arr[j-1];
              arr[j-1]=arr[j];
              arr[j]=m;
         }
    }
     return arr;
}

int main()
{
  int sizepol, nach, shag;
  cin >> sizepol >> nach  >> shag;
  if (1<sizepol && sizepol < 10000 && -10000<nach && nach <10000 && -10000 < shag && shag < 10000)
  {
      int *arr2 = create (sizepol, nach, shag);
      sort (arr2, sizepol);
      print (arr2, sizepol);
      delete [] arr2;
  }
  else
  {
      cout << "Error" << endl;
  }
}
