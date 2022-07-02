#pragma once
#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h" 

enum class Fonts;

class Score : public Component {
public:
    Score(int startingScore, Fonts fontToUse);
    void AddScore(int newPoints);
    void Draw(math::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int score;
    Texture scoreTexture;
};

class Boring : public Component {
public:
    Boring(int startingScore, Fonts fontToUse);
    void Add(int newPoints);
    void Draw(math::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int bored;
    Texture boredTexture;
};

class Doupting : public Component {
public:
    Doupting(int startingScore, Fonts fontToUse);
    void Add(int newPoints);
    void Draw(math::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int Doupt;
    Texture douptTexture;
};

class Tired : public Component {
public:
    Tired(int startingScore, Fonts fontToUse);
    void Add(int newPoints);
    void Draw(math::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int tired;
    Texture tiredTexture;
};
