#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Array.h"
#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h" 

using namespace std;

const int MAX_STRUCTS = 100;  // Максимальное количество разных структур каждого типа

// Массивы указателей для хранения структур данных
Stack* stacks[MAX_STRUCTS] = { nullptr };
Queue<string>* queues[MAX_STRUCTS] = { nullptr };
HashTable* hashTables[MAX_STRUCTS] = { nullptr };
Array* arrays[MAX_STRUCTS] = { nullptr };
LinkedList* linkedLists[MAX_STRUCTS] = { nullptr };
DoublyLinkedList* doublyLinkedLists[MAX_STRUCTS] = { nullptr };
CompleteBinaryTree* trees[MAX_STRUCTS] = { nullptr };  // Массив указателей на корни деревьев
string stackNames[MAX_STRUCTS], queueNames[MAX_STRUCTS], hashTableNames[MAX_STRUCTS], arrayNames[MAX_STRUCTS], linkedListNames[MAX_STRUCTS], doublyLinkedListNames[MAX_STRUCTS], treeNames[MAX_STRUCTS];

// Функция поиска и создания структуры данных
template<typename T>
int findOrCreate(string* names, T** structs, const string& name) {
    for (int i = 0; i < MAX_STRUCTS; i++) {
        if (names[i] == name) {
            return i;  // Найден существующий элемент
        }
        if (names[i].empty()) {  // Пустая ячейка
            names[i] = name;
            if constexpr (is_same<T, CompleteBinaryTree>::value) {
                structs[i] = nullptr;  // Для дерева оставляем корень пустым (nullptr)
            } else {
                structs[i] = new T();  // Для остальных структур — стандартная инициализация
                structs[i]->initialize();
            }
            return i;
        }
    }
    throw runtime_error("Exceeded maximum structures allowed.");
}



// Считывание данных из файла
void loadFromFile(const string& fileName) {
    ifstream inputFile(fileName);
    string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string type, name;
            iss >> type >> name;

            if (type == "stack") {
                int idx = findOrCreate(stackNames, stacks, name);
                string value;
                while (iss >> value) {
                    stacks[idx]->push(value);
                }
            } else if (type == "queue") {
                int idx = findOrCreate(queueNames, queues, name);
                string value;
                while (iss >> value) {
                    queues[idx]->push(value);
                }
            } else if (type == "hashtable") {
                int idx = findOrCreate(hashTableNames, hashTables, name);
                string keyValue;
                while (iss >> keyValue) {
                    size_t eqPos = keyValue.find('=');
                    string key = keyValue.substr(0, eqPos);
                    string value = keyValue.substr(eqPos + 1);
                    hashTables[idx]->insert(key, value);
                }
            } else if (type == "array") {
                int idx = findOrCreate(arrayNames, arrays, name);
                string value;
                while (iss >> value) {
                    arrays[idx]->add(value);
                }
            } else if (type == "linkedlist") {
                int idx = findOrCreate(linkedListNames, linkedLists, name);
                string value;
                while (iss >> value) {
                    linkedLists[idx]->push_back(value);
                }
            } else if (type == "doublylist") {
                int idx = findOrCreate(doublyLinkedListNames, doublyLinkedLists, name);
                string value;
                while (iss >> value) {
                    doublyLinkedLists[idx]->push_back(value);
                }
            } else if (type == "tree") {
                int idx = findOrCreate(treeNames, trees, name);
                int value;

                // Если дерево еще не создано, инициализируем корень
                if (trees[idx] == nullptr && iss >> value) {
                    trees[idx] = new CompleteBinaryTree(value);
                }
                // Добавляем оставшиеся узлы
                while (iss >> value) {
                    insert(trees[idx], value);
                }
            }
        }
        inputFile.close();
    } else {
        cerr << "Unable to open file for loading: " << fileName << endl;
    }
}

// Сохранение данных в файл
void saveToFile(const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        cerr << "Unable to open file for saving: " << fileName << endl;
        return;
    }

    for (int i = 0; i < MAX_STRUCTS; i++) {
        if (!stackNames[i].empty()) {
            outputFile << "stack " << stackNames[i];
            Stack temp = *stacks[i];
            while (temp.top != nullptr) {
                outputFile << " " << temp.top_elem();
                temp.pop();
            }
            outputFile << endl;
        }
        if (!queueNames[i].empty()) {
            outputFile << "queue " << queueNames[i];
            Queue<string> temp = *queues[i];
            while (temp.head != nullptr) {
                outputFile << " " << temp.front_elem();
                temp.pop();
            }
            outputFile << endl;
        }
      if (!hashTableNames[i].empty()) {
            outputFile << "hashtable " << hashTableNames[i];
            for (int j = 0; j < hashTables[i]->size; ++j) {
                HashNode* node = hashTables[i]->table[j];
                while (node != nullptr) {
                    ValueNode* valNode = node->values;
                // Для каждого значения, связанного с данным ключом
                while (valNode != nullptr) {
                    outputFile << " " << node->key << "=" << valNode->value;
                    valNode = valNode->next;
            }
            node = node->next;
        }
    }
    outputFile << endl;
}
        if (!arrayNames[i].empty()) {
            outputFile << "array " << arrayNames[i];
            for (size_t j = 0; j < arrays[i]->length; ++j) {
                outputFile << " " << arrays[i]->get(j);
            }
            outputFile << endl;
        }
        if (!linkedListNames[i].empty()) {
            outputFile << "linkedlist " << linkedListNames[i];
            ListNode* temp = linkedLists[i]->head;
            while (temp != nullptr) {
                outputFile << " " << temp->data;
                temp = temp->next;
            }
            outputFile << endl;
        }
        if (!doublyLinkedListNames[i].empty()) {
            outputFile << "doublylist " << doublyLinkedListNames[i];
            DoublyNode* temp = doublyLinkedLists[i]->head;
            while (temp != nullptr) {
                outputFile << " " << temp->data;
                temp = temp->next;
            }
            outputFile << endl;
        }
        if (!treeNames[i].empty()) {
            outputFile << "tree " << treeNames[i];
            if (trees[i] != nullptr) {
                queue<CompleteBinaryTree*> q;
                q.push(trees[i]);

                while (!q.empty()) {
                    CompleteBinaryTree* node = q.front();
                    q.pop();
                    outputFile << " " << node->value;

                    if (node->left) q.push(node->left);
                    if (node->right) q.push(node->right);
                }
            }
            outputFile << endl;
        }
    }
    outputFile.close();
}


// Обработка запроса
void processQuery(const string& query, ofstream& outputFile) {
    istringstream iss(query);
    string operation, name;
    iss >> operation >> name;

    if (operation == "SPUSH") {
        string value;
        iss >> value;
        int idx = findOrCreate(stackNames, stacks, name);
        stacks[idx]->push(value);
        outputFile << "Added " << value << " to stack " << name << endl;

    } else if (operation == "SPOP") {
        int idx = findOrCreate(stackNames, stacks, name);
        stacks[idx]->pop();
        outputFile << "Popped from stack " << name << endl;

    } else if (operation == "QPUSH") {
        string value;
        iss >> value;
        int idx = findOrCreate(queueNames, queues, name);
        queues[idx]->push(value);
        outputFile << "Added " << value << " to queue " << name << endl;

    } else if (operation == "QPOP") {
        int idx = findOrCreate(queueNames, queues, name);
        queues[idx]->pop();
        outputFile << "Popped from queue " << name << endl;

    } else if (operation == "QPEEK") {
    int idx = findOrCreate(queueNames, queues, name);
    try {
        string value = queues[idx]->front_elem();
        outputFile << "Front element in queue " << name << ": " << value << endl;
    } catch (const std::out_of_range&) {
        outputFile << "Queue " << name << " is empty" << endl;
    }

    } else if (operation == "HSET") {
    string key, value;
    iss >> key >> value;
    int idx = findOrCreate(hashTableNames, hashTables, name);
    hashTables[idx]->insert(key, value);
    outputFile << "Added value " << value << " to key " << key << " in hash table " << name << endl;

    } else if (operation == "HGET") {
    string key;
    iss >> key;
    int idx = findOrCreate(hashTableNames, hashTables, name);
    try {
        string values = hashTables[idx]->get(key);  // Получаем строку со всеми значениями
        outputFile << "Values for key " << key << " in hash table " << name << ": " << values << endl;
    } catch (const out_of_range&) {
        outputFile << "Key " << key << " not found in hash table " << name << endl;
    }

    } else if (operation == "HDEL") {
    string key;
    iss >> key;
    int idx = findOrCreate(hashTableNames, hashTables, name);
    hashTables[idx]->remove(key);
    outputFile << "Deleted all values for key " << key << " from hash table " << name << endl;

    } else if (operation == "MPUSH") {
        string value;
        iss >> value;
        int idx = findOrCreate(arrayNames, arrays, name);
        arrays[idx]->add(value);
        outputFile << "Added " << value << " to array " << name << endl;

    } else if (operation == "MGET") {
        size_t index;
        iss >> index;
        int idx = findOrCreate(arrayNames, arrays, name);
        try {
            string value = arrays[idx]->get(index);
            outputFile << "Array element at index " << index << ": " << value << endl;
        } catch (const out_of_range&) {
            outputFile << "Index out of range for array " << name << endl;
        }

    } else if (operation == "MDEL") {
        size_t index;
        iss >> index;
        int idx = findOrCreate(arrayNames, arrays, name);
        arrays[idx]->removeAt(index);
        outputFile << "Deleted element at index " << index << " from array " << name << endl;

    } else if (operation == "MINSERT") {
        size_t index;
        string value;
        iss >> index >> value;
        int idx = findOrCreate(arrayNames, arrays, name);
        try {
            arrays[idx]->insertAt(index, value);
            outputFile << "Inserted " << value << " at index " << index << " in array " << name << endl;
            } catch (const out_of_range&) {
        outputFile << "Index out of range for array " << name << endl;
        }

    } else if (operation == "MSET") {
        size_t index;
        string value;
        iss >> index >> value;
        int idx = findOrCreate(arrayNames, arrays, name);
        try {
            arrays[idx]->setAt(index, value);
            outputFile << "Set element at index " << index << " to " << value << " in array " << name << endl;
        } catch (const out_of_range&) {
            outputFile << "Index out of range for array " << name << endl;
        }
    } else if (operation == "LLPUSH_FRONT") {
        string value;
        iss >> value;
        int idx = findOrCreate(linkedListNames, linkedLists, name);
        linkedLists[idx]->push_front(value);
        outputFile << "Added " << value << " to linked list " << name << endl;
 
    } else if (operation == "LLPUSH_BACK") {
        string value;
        iss >> value;
        int idx = findOrCreate(linkedListNames, linkedLists, name);
        linkedLists[idx]->push_back(value);
        outputFile << "Added " << value << " to linked list " << name << endl;

    } else if (operation == "LLREMOVE") {
        string value;
        iss >> value;
        int idx = findOrCreate(linkedListNames, linkedLists, name);
        linkedLists[idx]->remove(value);
        outputFile << "Removed " << value << " from linked list " << name << endl;

    } else if (operation == "LREMOVE_FRONT") {
    int idx = findOrCreate(linkedListNames, linkedLists, name);
    linkedLists[idx]->remove_front();
    outputFile << "Removed element from the front of list " << name << endl;

} else if (operation == "LREMOVE_BACK") {
    int idx = findOrCreate(linkedListNames, linkedLists, name);
    linkedLists[idx]->remove_back();
    outputFile << "Removed element from the back of list " << name << endl;

} else if (operation == "LFIND") {
    string value;
    iss >> value;
    int idx = findOrCreate(linkedListNames, linkedLists, name);
    bool found = linkedLists[idx]->find(value);
    outputFile << "Element " << value << " in list " << name << " is " << (found ? "found" : "not found") << endl;

} else if (operation == "DLADD_FRONT") {
        string value;
        iss >> value;
        int idx = findOrCreate(doublyLinkedListNames, doublyLinkedLists, name);
        doublyLinkedLists[idx]->push_front(value);
        outputFile << "Added " << value << " to front of doubly linked list " << name << endl;

    } else if (operation == "DLADD_BACK") {
        string value;
        iss >> value;
        int idx = findOrCreate(doublyLinkedListNames, doublyLinkedLists, name);
        doublyLinkedLists[idx]->push_back(value);
        outputFile << "Added " << value << " to back of doubly linked list " << name << endl;

    } else if (operation == "DLREMOVE") {
        string value;
        iss >> value;
        int idx = findOrCreate(doublyLinkedListNames, doublyLinkedLists, name);
        doublyLinkedLists[idx]->remove(value);
        outputFile << "Removed " << value << " from doubly linked list " << name << endl;

    }else if (operation == "DLREMOVE_FRONT") {
    int idx = findOrCreate(doublyLinkedListNames, doublyLinkedLists, name);
    doublyLinkedLists[idx]->remove_front();
    outputFile << "Removed element from the front of list " << name << endl;

} else if (operation == "DLREMOVE_BACK") {
    int idx = findOrCreate(doublyLinkedListNames, doublyLinkedLists, name);
    doublyLinkedLists[idx]->remove_back();
    outputFile << "Removed element from the back of list " << name << endl;

} else if (operation == "DLFIND") {
    string value;
    iss >> value;
    int idx = findOrCreate(doublyLinkedListNames, doublyLinkedLists, name);
    bool found = doublyLinkedLists[idx]->find(value);
    outputFile << "Element " << value << " in list " << name << " is " << (found ? "found" : "not found") << endl;

} else if (operation == "TINSERT") {
        int value;
        iss >> value;
        
        // Находим индекс дерева или создаем его
        int idx = findOrCreate(treeNames, trees, name);
        
        // Если дерево не существует, создаем корневой элемент
        if (trees[idx] == nullptr) {
            trees[idx] = new CompleteBinaryTree(value);
        } else {
            insert(trees[idx], value);  // Вставляем элемент в существующее дерево
        }
        
        outputFile << "Inserted " << value << " into tree " << name << endl;

    } else if (operation == "TDEL") {
        int value;
        iss >> value;
        int idx = findOrCreate(treeNames, trees, name);

    // Удаляем узел с заданным значением
        remove(trees[idx], value);

    // Проверяем, является ли дерево полным
        bool complete = isComplete(trees[idx]);
        outputFile << "Deleted " << value << " from tree " << name << endl;
        outputFile << "Complete is " << (complete ? "true" : "false") << endl;

    } else if (operation == "TGET") {
        int value;
        iss >> value;
        int idx = findOrCreate(treeNames, trees, name);
        bool found = find(trees[idx], value);
        if (found) {
            outputFile << "Value " << value << " found in tree " << name << endl;
        } else {
            outputFile << "Value " << value << " not found in tree " << name << endl;
        }
    } else if (operation == "TCOMPLETE") {
        int idx = findOrCreate(treeNames, trees, name);
        bool complete = isComplete(trees[idx]);
        outputFile << "Tree " << name << (complete ? " is complete" : " is not complete") << endl;
}
}

// Основная функция
int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 5) {
        cerr << "Usage: " << argv[0] << " --file <file.data> [--query '<query>']" << endl;
        return 1;
    }

    string fileArg = argv[1];
    string fileName = argv[2];
    string queryArg = argc == 5 ? argv[3] : "";
    string query = argc == 5 ? argv[4] : "";

    if (fileArg != "--file" || (argc == 5 && queryArg != "--query")) {
        cerr << "Invalid arguments. Usage: " << argv[0] << " --file <file.data> [--query '<query>']" << endl;
        return 1;
    }

    // Загружаем данные из файла
    loadFromFile(fileName);

    // Если есть запрос, обработаем его
    if (!query.empty()) {
        ofstream outputFile("output.txt", ios::app);
        processQuery(query, outputFile);
        outputFile.close();

        // Сохраняем изменения в файл данных
        saveToFile(fileName);
    } else {
        // Если нет параметра --query, переходим в интерактивный режим
        cout << "Enter commands (type 'exit' to quit):" << endl;
        ofstream outputFile("output.txt", ios::app);
        while (true) {
            cout << "> ";
            getline(cin, query);
            if (query == "exit") break;
            processQuery(query, outputFile);
            saveToFile(fileName);
        }
        outputFile.close();
    }

    return 0;
}

