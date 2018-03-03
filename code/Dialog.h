//
// Created by sen on 18-2-18.
//

#ifndef MAGICTOWER_DIALOG_H
#define MAGICTOWER_DIALOG_H

#include <SDL/SDL.h>
#include <string>
#include <vector>
#include <memory>
#include "tools/WordingStore.h"
#include "tools/WordingCreator.h"

class Dialog
{
public:
    Dialog(SDL_Surface *parent, int x, int y);
    virtual ~Dialog();

public:
    virtual void show();
    SDL_Surface *getParent();
    int getX() const;
    int getY() const;

protected:
    virtual void onEvent(SDL_Event &e) = 0;
    void breakDialog();
    void startLoop();

private:
    SDL_Surface *parent_;
    int x_;
    int y_;
    bool wouldBreak_;
};

typedef std::shared_ptr<Dialog> DialogPtr;

class WordingDialog : public Dialog
{
public:
    WordingDialog(SDL_Surface *parent, int x, int y);

public:
    void show() override;

protected:
    void onEvent(SDL_Event &e) override;

public:
    void setWording(const std::string &bg, const WordingListPtr &lst);

protected:
    void showFrame(const std::string &str);

private:
    Wording wordingWrap_;
    std::string bg_;
};

class MsgBox : public WordingDialog
{
public:
    MsgBox(SDL_Surface *parent, int x, int y, const std::string &bg, const std::string &msg);
};

class Button
{
public:
    Button(SDL_Surface *parent, int x, int y, const SDL_SurfacePtr &bg, const SDLKey &key);
    Button(SDL_Surface *parent, int x, int y, const std::string &bg, const SDLKey &key);

public:
    bool isMouseDown(const SDL_Event &e);
    bool isMouseUp(const SDL_Event &e);
    bool isKeyDown(const SDL_Event &e);
    bool isKeyUp(const SDL_Event &e);
    bool isOnRect(const SDL_Event &e);
    bool isHotKeyPressed(const SDL_Event &e);
    bool isClicked(const SDL_Event &e);
    void draw();

private:
    SDL_Surface *parent_;
    SDL_SurfacePtr bg_;
    int x_;
    int y_;
    SDLKey hotKey_;
};

typedef std::shared_ptr<Button> ButtonPtr;

class SelectDialog : public Dialog
{
public:
    SelectDialog(SDL_Surface *parent, int x, int y, const std::string &bg, const std::string &item, const std::vector<std::string> &items);

public:
    void show() override;

protected:
    void onEvent(SDL_Event &e) override;

public:
    bool hasSelected() const;
    int32_t getSelected() const;

private:
    std::string bg_;
    std::string item_;
    std::vector<std::string> items_;
    std::vector<ButtonPtr> btns_;
    int32_t selected_;
};

class CheckDialog : public Dialog
{
public:
    CheckDialog(SDL_Surface *parent, int x, int y, const std::string &msg);

public:
    void show() override;
    bool checkResult() const;

protected:
    void onEvent(SDL_Event &e) override;

private:
    bool result_;
    std::string msg_;
    ButtonPtr btnOk_;
    ButtonPtr btnCl_;
};

#endif //MAGICTOWER_DIALOG_H
