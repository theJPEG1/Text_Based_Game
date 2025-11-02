#ifndef QUESTS_H
#define QUESTS_H

#include <string>
    using std::string;
#include <vector>
    using std::vector;


class Quest
{
    public: 
        /// @brief Construsts a quest
        /// @param questDescriptions The series of descriptions of the quest
        /// @param questPosition the position you are currently on in the quest
        /// @param questCompleted have you completed or not
        Quest(vector<string> questDescriptions, int questPosition)
        {
            questDesc = questDescriptions;
            questPos = questPosition;
        };

        /// @brief Gets the current part of the quest
        /// @return returns a string from the vector of the current questPosition
        string getQuest()
        {
            return questDesc.at(questPos);
        };

        void completeQuest()
        {
            if(static_cast<size_t> (questPos) >= questDesc.size())
            {
                completed = true;
            }
        };

        /// @brief Has a quest been completed or not
        /// @return if the quest is completed
        bool isCompletedQuest()
        {
            return completed;
        };
        
    
    private:
        vector<string> questDesc;
        int questPos;
        bool completed;

};

#endif