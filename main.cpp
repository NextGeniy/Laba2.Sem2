#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Node {
    int Data;
    Node* Prev, * Next;
    Node(int Data) {               /// Конструктор узлов
        this->Data = Data;
        this->Prev = this->Next = nullptr;

    }
};
struct List
{
    Node* Head, *Tail;
    List() {                       //Конструктор списка
        Head = Tail = nullptr;
    }   
    ~List() {                      //Деструктор списка
        while (Head != nullptr)
            DeleteFirst();
    }
    Node* CreateListRandom(int Lenght) {  //Метод
        Node* Ptr = 0;
        for (int i = 1; i <= Lenght; ++i) { 
            int Data = rand() % 100;
            Node* Ptr = new Node(Data);
            Ptr->Next = Head;
            if (Head != nullptr)
                Head->Prev = Ptr;
            if (Tail == nullptr)
                Tail = Ptr;
            Head = Ptr;

        }
        return Ptr;
    }
    Node* AddFirst(int Data) {
        Node* Ptr = new Node(Data);
        Ptr->Prev = Tail;
        if (Tail != nullptr)
            Tail->Next = Ptr;
        if (Head == nullptr)
            Head = Ptr;
        Tail = Ptr;
        return Ptr;
    }
    Node* AddLast(int Data) {
        Node* Ptr = new Node(Data);
        Ptr->Next = Head;
        if (Head != nullptr)
            Head->Prev = Ptr;
        if (Tail == nullptr)
            Tail = Ptr;
        Head = Ptr;
        return Ptr;
    }
    void DeleteFirst() {
        if (Head == nullptr)
            return;
        Node* Ptr = Head->Next;
        if (Ptr != nullptr)
            Ptr->Prev = nullptr;
        else
            Tail = nullptr;
        delete Head;
        Head = Ptr;
    }
    void DeleteLast() {
        if (Tail == nullptr)
            return;
        Node* Ptr = Tail->Prev;
        if (Ptr != nullptr)
            Ptr->Next = nullptr;
        else
            Head = nullptr;
        delete Tail;
        Tail = Ptr;
    }
    Node* GetIndex(int Index) {
        Node* Ptr = Head;
        int Temp = 1;
        while (Temp != Index) {
            if (Ptr == nullptr)
                return nullptr;
            Ptr = Ptr->Next;
            Temp++;
        }
        return Ptr;
    }
    Node* operator[] (int Index) {
        return GetIndex(Index);
    }
    int NumObj() {
        Node* Ptr = Head;
        int Temp = 1;
        while (Ptr != nullptr) {
            if (Ptr == nullptr)
                return NULL;
            Ptr = Ptr->Next;
            Temp++;
        }
        return Temp;
    }
    int GetDataIndex(int Data) {
        Node* Ptr = Head;
        for (int Temp = 0; Temp <= NumObj(); ++Temp) {
            if (Ptr->Data == Data)
                return Temp+1;
            Ptr = Ptr->Next;
        }
    }
    Node* Insertion(int Index, int Data) {
        Node* Right = GetIndex(Index);
        if (Right == nullptr) {
            return AddLast(Data);
        }
        Node* Left = Right->Prev;
        if (Left == nullptr) {
            return AddFirst(Data);
        }
        Node* Ptr = new Node(Data);
        Ptr->Prev = Left;
        Ptr->Next = Right;
        Left->Next = Ptr;
        Right->Prev = Ptr;
        return Ptr;
    }
    void Delete(int Index) {
        Node* Ptr = GetIndex(Index);
        if (Ptr == nullptr)
            return;
        if (Ptr->Prev == nullptr) {
            DeleteFirst();
            return;
        }
        if (Ptr->Next == nullptr) {
            DeleteLast();
            return;
        }
        Node* Right = Ptr->Next;
        Node* Left = Ptr->Prev;
        Left->Next = Right;
        Right->Prev = Left;
        delete Ptr;
    }
    void Change(int Index1, int Index2) {
        if (Index1 > Index2){
            int Temp = Index1;
            Index1 = Index2;
            Index2 = Temp;
        }
        if (Index1 <= 0 || Index1 == Index2)
            return;
        Node* Index1Node = GetIndex(Index1);
        Node* Index2Node = GetIndex(Index2);
        if (Index1Node == Head){
            swap(Index1Node->Prev, Index2Node->Prev);
            swap(Index1Node->Next, Index2Node->Next);
            Index1Node->Prev->Next = Index1Node;
            if (Index2Node == Tail){
                Index2Node->Next->Prev = Index2Node;
            }
            else{
                swap(Index1Node->Next->Prev, Index2Node->Next->Prev);
            }
            Head = Index2Node;
            Tail = Index1Node;
        }
        else if (Index2Node == Tail){
            swap(Index1Node->Prev, Index2Node->Prev);
            swap(Index1Node->Next, Index2Node->Next);
            swap(Index1Node->Prev->Next, Index2Node->Prev->Next);
            Index2Node->Next->Prev = Index2Node;
            Head = Index2Node;
        }
        else{
            swap(Index1Node->Prev->Next, Index2Node->Prev->Next);
            swap(Index1Node->Prev, Index2Node->Prev);
            swap(Index1Node->Next->Prev, Index2Node->Next->Prev);
            swap(Index1Node->Next, Index2Node->Next);
        }
    }
};


int main()
{   
    setlocale(0, "Rus");
    int I = 0, CreatedMList = 0;
    List MainList;
    srand(time(NULL));
    while (I != 8) {
        system("CLS");
        cout << "1-Генерация связного списка размерности N.\n";
        cout << "2-Вставка элемента, введите индекс и значение (идексация с 1).\n";
        cout << "3-Удаление элемента по индексу.\n";
        cout << "4-Удаление элемента по значению.\n";
        cout << "5-Получение элемента по индексу.\n";
        cout << "6-Получение элемента по значению.\n";
        cout << "7-Обмен элементов.\n";
        cout << "8 - Выход.\n";
        for (Node* Ptr = MainList.Head; Ptr != nullptr; Ptr = Ptr->Next) {
            cout << Ptr->Data << "  ";
        }
        cout << "\n";
        cout << "Введите пункт: ";
        cin >> I;
        auto start1 = steady_clock::now();
        auto end1 = steady_clock::now();
        switch (I) {
        case 1:
            system("CLS");
            cout << "Введите кол-во узлов:\n";
            int Lenght;
            cin >> Lenght;
            cout << "\n";
            start1 = steady_clock::now();
            MainList.CreateListRandom(Lenght);
            end1 = steady_clock::now();
            cout << "Время создания списка: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " наносекунд" << endl;
            for (Node* Ptr = MainList.Head; Ptr != nullptr; Ptr = Ptr->Next) {
            cout << Ptr->Data << "  ";
            }
            cout << "\n";
            CreatedMList = 1;
            system("pause");
            break;
        case 2:
            system("CLS");
            if (!CreatedMList) {
                cout << "Вы не создали список.\n";
                system("pause");
                break;
            }
            int Index, Data;
            cin >> Index;
            cout << "\n";
            cin >> Data;
            cout << "\n";
            start1 = steady_clock::now();
            MainList.Insertion(Index, Data);
            end1 = steady_clock::now();
            cout << "Время вставки элемента: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " наносекунд" << endl;
            for (Node* Ptr = MainList.Head; Ptr != nullptr; Ptr = Ptr->Next) {
                cout << Ptr->Data << "  ";
            }
            cout << "\n";
            system("pause");
            break;
        case 3:
            system("CLS");
            if (!CreatedMList) {
                cout << "Вы не создали список.\n";
                system("pause");
                break;
            }
            int Index1;
            cin >> Index1;
            cout << "\n";
            start1 = steady_clock::now();
            MainList.Delete(Index1);
            end1 = steady_clock::now();
            cout << "Время удаления элемента: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " наносекунд" << endl;
            for (Node* Ptr = MainList.Head; Ptr != nullptr; Ptr = Ptr->Next) {
                cout << Ptr->Data << "  ";
            }
            cout << "\n";
            system("pause");
            break;
        case 4:
            system("CLS");
            if (!CreatedMList) {
                cout << "Вы не создали список.\n";
                system("pause");
                break;
            }
            int Data1;
            cin >> Data1;
            cout << "\n";
            start1 = steady_clock::now();
            MainList.Delete(MainList.GetDataIndex(Data1));
            end1 = steady_clock::now();
            cout << "Время удаления элемента: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " наносекунд" << endl;
            for (Node* Ptr = MainList.Head; Ptr != nullptr; Ptr = Ptr->Next) {
                cout << Ptr->Data << "  ";
            }
            system("pause");
            break;
        case 5:
            system("CLS");
            if (!CreatedMList) {
                cout << "Вы не создали список.\n";
                system("pause");
                break;
            }
            int Index2;
            cin >> Index2;
            cout << "\n";
            start1 = steady_clock::now();
            cout << MainList[Index2]->Data << " ";
            end1 = steady_clock::now();
            cout << "Время получения элемента: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " наносекунд" << endl;
            system("pause");
            break;
        case 6:
            system("CLS");
            if (!CreatedMList) {
                cout << "Вы не создали список.\n";
                system("pause");
                break;
            }
                int Data2;
                cin >> Data2;
                cout << "\n";
                start1 = steady_clock::now();
                cout << MainList.GetDataIndex(Data2) << " ";
                end1 = steady_clock::now();
                cout << "Время получения элемента: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " наносекунд" << endl;
                system("pause");
                break;
        case 7:
            system("CLS");
            if (!CreatedMList) {
                cout << "Вы не создали список.\n";
                system("pause");
                break;
            }
            int Index_1, Index_2;
            cin >> Index_1;
            cout << "\n";
            cin >> Index_2;
            cout << "\n";
            start1 = steady_clock::now();
            MainList.Change(Index_1, Index_2);
            end1 = steady_clock::now();
            cout << "Время меняния элемента: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " наносекунд" << endl;
            for (Node* Ptr = MainList.Head; Ptr != nullptr; Ptr = Ptr->Next) {
                cout << Ptr->Data << "  ";
            }
            system("pause");
            break;
        case 9:
            cout << "Программа завершена\n";
        }
    }
}
