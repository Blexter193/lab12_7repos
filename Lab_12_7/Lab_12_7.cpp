#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Node
{
    std::string word;
    Node* next;

    Node(const std::string& w) : word(w), next(nullptr) {}
};

void addWordToList(Node*& head, const std::string& word)
{
    Node* newNode = new Node(word);

    if (head == nullptr)
    {
        head = newNode;
    }
    
    else
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printList(const Node* head)
{
    const Node* current = head;
    while (current != nullptr)
    {
        std::cout << current->word << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

Node* createWordList(const std::vector<std::string>& words)
{
    Node* head = nullptr;

    if (!words.empty())
    {
        std::vector<std::string> sortedWords = words;
        std::sort(sortedWords.begin(), sortedWords.end());

        addWordToList(head, sortedWords[0]);

        for (size_t i = 1; i < sortedWords.size(); i++)
        {
            if (sortedWords[i][0] == sortedWords[i - 1][sortedWords[i - 1].length() - 1])
            {
                addWordToList(head, sortedWords[i]);
            }
        }

        if (head == nullptr)
        {
            for (const std::string& word : sortedWords)
            {
                addWordToList(head, word);
            }
        }
    }

    return head;
}

std::vector<std::string> getWordsFromInput()
{
    std::vector<std::string> words;

    std::string input;
    std::cout << "Введіть послідовність слів: ";
    std::getline(std::cin, input);

    std::string word;
    for (char c : input)
    {
        if (c == ' ')
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
        
        else
        {
            word += c;
        }
    }
    
    if (!word.empty())
    {
        words.push_back(word);
    }

    return words;
}

std::vector<std::string> getWordsFromFile(const std::string& filename)
{
    std::vector<std::string> words;
    std::ifstream file("/Users/user/text12_7.txt");

    if (file.is_open())
    {
        std::string word;
        while (file >> word)
        {
            words.push_back(word);
        }
        file.close();
    }
    
    else
    {
        std::cerr << "Помилка відкриття файлу!" << std::endl;
    }

    return words;
}

int main()
{
    std::vector<std::string> words;

    std::string choice;
    std::cout << "Виберіть спосіб введення слів (1 - з клавіатури, 2 - з файлу): ";
    std::getline(std::cin, choice);

    if (choice == "1")
    {
        words = getWordsFromInput();
    }
    
    else if (choice == "2")
    {
        std::string filename;
        std::cout << "Введіть назву файлу: ";
        std::getline(std::cin, filename);
        words = getWordsFromFile(filename);
    }
    
    else
    {
        std::cerr << "Неправильний вибір!" << std::endl;
        return 1;
    }
    
    Node* wordList = createWordList(words);

    std::cout << "Створений список слів: ";
    printList(wordList);

    while (wordList != nullptr)
    {
        Node* temp = wordList;
        wordList = wordList->next;
        delete temp;
    }

    return 0;
}
