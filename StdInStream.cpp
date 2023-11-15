// StdInStream.cpp
// Implements the functionality of the StdInStream class

#include "StdInStream.h"

StdInStream::StdInStream(Player* playerToSet, InputParser* parserToSet)
{
    this->player = playerToSet;
    this->parser = parserToSet;
}

void StdInStream::loopInputRequest()
{
    std::cout << "Welcome to Katoche!" << std::endl;
    this->player->getHelp();
    this->player->enterRoom(this->player->getWorld()->getCurrentRoom());
    while (this->player->getContinueGame())
    {
        std::cout << "What do you do? ";
        this->userInput = this->takeInput();
        this->parser->parseInput(this->userInput);
    }
}

std::string StdInStream::takeInput()
{
    std::string userInput;
    std::getline(std::cin, userInput);
    userInput = this->cleanInput(userInput);
    userInput = this->removeArticles(userInput);
    return userInput;
}

std::string StdInStream::cleanInput(std::string inputToClean)
{
    int inputLength = inputToClean.size();
    for (int i = 0; i < inputLength; i++)
    {
        if (isupper(inputToClean[i]))
        {
            inputToClean[i] = tolower(inputToClean[i]);
        }
        if (!isalnum(inputToClean[i]) && !isspace(inputToClean[i]))
        {
            inputToClean.erase(i, 1);
            inputLength = inputLength - 1;
            i = i - 1;
        }
    }
    return inputToClean;
}

std::string StdInStream::removeArticles(std::string inputToClean)
{
    std::string articles[] = { "the ", "an ", "a " };
    for (std::string article : articles)
    {
        while (inputToClean.find(article) != std::string::npos)
        {
            std::size_t found = inputToClean.find(article);
            if (found != std::string::npos)
            {
                inputToClean.erase(found, article.size());
            }
        }
    }
    return inputToClean;
}

