#include<bits/stdc++.h>
#include <SDL2/SDL.h>
using namespace std;
#undef main
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
int BAR_WIDTH;
const int MAX_BAR_HEIGHT = 500;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

void renderBars(const std::vector<int>& arr) {

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    for (size_t i = 0; i < arr.size(); ++i) {

        SDL_Rect barRect = {static_cast<int>(i * BAR_WIDTH), SCREEN_HEIGHT - arr[i], BAR_WIDTH, arr[i]};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &barRect);

        SDL_Rect borderRect = {static_cast<int>(i * BAR_WIDTH), SCREEN_HEIGHT - arr[i], BAR_WIDTH, arr[i]};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(gRenderer, &borderRect);

    }

    SDL_RenderPresent(gRenderer);
    
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;

            renderBars(arr);
            SDL_Delay(40);

        }
        arr[j + 1] = key;
    }
}

void merge(vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[middle + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];

            renderBars(arr);
            SDL_Delay(35);

            ++i;
            
        } else {
            arr[k] = R[j];

            renderBars(arr);
            SDL_Delay(35);

            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];

        renderBars(arr);
        SDL_Delay(35);

        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];

        renderBars(arr);
        SDL_Delay(35);

        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);

        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);

         renderBars(arr);
         SDL_Delay(30);
    }
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);

                renderBars(arr);
                SDL_Delay(30);

                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);

            renderBars(arr);
            SDL_Delay(60);
        }
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
            renderBars(arr);
            SDL_Delay(35);
        }
    }

    swap(arr[i + 1], arr[high]);

    renderBars(arr);
    SDL_Delay(35);

    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);

        quickSort(arr, pi + 1, high);

        renderBars(arr);
        SDL_Delay(20);
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);

        renderBars(arr);
        SDL_Delay(35);

        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);

        renderBars(arr);
        SDL_Delay(35);
    }
}

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout<< "SDL could not initialize! SDL_Error: " << SDL_GetError() <<endl;
        return 1;
    }

    cout<<endl<<endl<<"==============================Sorting Visualizer==============================\n\n"
        <<"Visualization of different sorting algorithms in C++ with SDL2 Library. A sorting algorithm is an algorithm that puts the elements of a list in a certain order."<<endl
        <<"In this implementation of sorting visualizer, we'll be looking at some of these sorting algorithms and visually comprehend their working."<<endl
        <<"The sorting algorithms covered here are Selection Sort, Insertion Sort, Bubble Sort, Merge Sort, Quick Sort and Heap Sort."<<endl
        <<"First enter the number of elements for array(between 60 & 100)."<<endl
        << "This visualizer will randomly generate the values."<<endl<<endl;
    
    int n;
    cin>>n;

    vector<int>arr(n);
    BAR_WIDTH=800/n;

    for(int i=0;i<n;i++){
        arr[i]=rand()%450;
    }

    vector<int>temp=arr;
    int c;

    cout <<"    Use 1 to start Selection Sort Algorithm.\n"
         <<"    Use 2 to start Insertion Sort Algorithm.\n"
         <<"    Use 3 to start Bubble Sort Algorithm.\n"
         <<"    Use 4 to start Merge Sort Algorithm.\n"
         <<"    Use 5 to start Quick Sort Algorithm.\n"
         <<"    Use 6 to start Heap Sort Algorithm.\n"
         <<"    Use 0 to exit out of Sorting Visualizer\n\n";

    c=10;

    while(c){

        cin>>c;

        if(c==1){
        gWindow = SDL_CreateWindow("Selection Sort Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
        cout<< "Window could not be created! SDL_Error: " << SDL_GetError() <<endl;
        return 1;
        }
    
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == nullptr) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
        }
        selectionSort(arr);

        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);

        arr=temp;

        }
        else if(c==2){

        gWindow = SDL_CreateWindow("Insertion Sort Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() <<endl;
        return 1;
        }
    
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == nullptr) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
        }
        insertionSort(arr);

        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);

        arr=temp;

        }
        else if(c==3){

        gWindow = SDL_CreateWindow("Bubble Sort Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
        }
    
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
        }
        bubbleSort(arr);

        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);   

        arr=temp;

        }
        else if(c==4){

        gWindow = SDL_CreateWindow("Merge Sort Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
        }
    
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == nullptr) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() <<endl;
        return 1;
        }

        mergeSort(arr,0,arr.size()-1);

        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);   

        arr=temp; 

        }
        else if(c==5){

        gWindow = SDL_CreateWindow("Quick Sort Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
        }
    
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == nullptr) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
        }

        quickSort(arr,0,arr.size()-1);

        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);    

        arr=temp;

        }
        else if(c==6){

        gWindow = SDL_CreateWindow("Heap Sort Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
        }
    
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == nullptr) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
        }

        heapSort(arr);

        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow); 

        arr=temp;   

        }
    }

    cout<<"Thank you for using our Sorting Visualiser"<<endl;

    SDL_Quit();

    return 0;

}
