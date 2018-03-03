//
// Created by sen on 18-2-18.
//

#ifndef MAGICTOWER_WORDINGSTORE_H
#define MAGICTOWER_WORDINGSTORE_H

#include <string>
#include <vector>
#include "Global.h"
#include <memory>
#include <map>

typedef std::vector<std::string> WordingList;
typedef std::shared_ptr<WordingList> WordingListPtr;

class Wording
{
public:
    Wording();

public:
    void attach(const WordingListPtr &ptr);
    bool hasNext();
    const std::string &next();
    void reset();

private:
    WordingListPtr ptr_;
    int32_t index_;
};

class WordingStore
{
private:
    WordingStore();

public:
    static WordingStore &instance();

public:
    bool init(const Global &bs);

public:
    WordingListPtr get(uint32_t id);

public:
    std::map<uint32_t, WordingListPtr> store_;
};


#endif //MAGICTOWER_WORDINGSTORE_H
