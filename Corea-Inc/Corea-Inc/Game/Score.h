#pragma once
#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h" 

enum class Fonts;

class Score : public coconut::Component {
public:
    Score(int startingScore, Fonts fontToUse);
    void AddScore(int newPoints);
    void Draw(glm::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int score;
    coconut::Texture scoreTexture;
};

class Boring : public coconut::Component {
public:
    Boring(int startingScore, Fonts fontToUse);
    void Add(int newPoints);
    void Draw(glm::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int bored;
    coconut::Texture boredTexture;
};

class Doupting : public coconut::Component {
public:
    Doupting(int startingScore, Fonts fontToUse);
    void Add(int newPoints);
    void Draw(glm::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int Doupt;
    coconut::Texture douptTexture;
};

class Tired : public coconut::Component {
public:
    Tired(int startingScore, Fonts fontToUse);
    void Add(int newPoints);
    void Draw(glm::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int tired;
    coconut::Texture tiredTexture;
};
