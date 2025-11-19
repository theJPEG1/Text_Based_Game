#ifndef QUESTS_H
#define QUESTS_H

#include "attacksEffects.H"
#include "Enemy.h"

#include <string>
    using std::string;
#include <vector>
    using std::vector;

struct QuestObjective
{
    QuestObjective() = default;
    QuestObjective(bool getItem); 
    QuestObjective(CraftingMaterials itemToGet, int amt); 

    int collected = 0;
    int collectedTotal;

    CraftingMaterials item;
    bool hasItem;
};

class Quest
{
    public: 
        Quest() = default;
        Quest(string fileName)
        {
            ifstream file(fileName);

            if (!file.is_open()) 
            {
                cout << "Failed to open " << fileName << "\n";
            }

            json data;
            file >> data;

            for(size_t i = 0; i < data["Quest Messages"].size(); i++)
            {
                displayMessage.push_back(data["Quest Messages"][i]["message"]);
            }

            ID = data["id"];
            status = data["status"];
            questIndex = data["messageIndex"];
        };

        string getId() const {return ID;};
        int getStatus() const {return status;};
        int getQuestIndex() const {return questIndex;};

        vector<string> getMessages() const {return displayMessage;};
        void setStatus(int newStatus) {status = newStatus;};
        void setMessageIndex(int newIndex) 
        {
            if(static_cast<size_t>(newIndex) >= displayMessage.size())
            {
                questIndex = displayMessage.size() - 1;
            }

            else
            {
                questIndex = newIndex;
            }
        };

        void addObjective (QuestObjective qo) {o.push_back(qo);};
        vector<QuestObjective>& getObjective() {return o;};

    private:
        string ID;
        int status;
        vector<string> displayMessage;
        int questIndex;
        vector<QuestObjective> o;
};

#endif