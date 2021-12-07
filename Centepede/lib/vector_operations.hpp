#ifndef VECTOR_OPERATIONS_HPP
#define VECTOR_OPERATIONS_HPP

#include <iostream>
#include <vector>

template <typename TItem>
bool contains(std::vector<std::shared_ptr<TItem>> &vector, TItem &element){
    for(auto item : vector){
        if(*item == element){
            return true;
        }
    }
    return false;
}

template <typename TItem>
std::shared_ptr<std::vector<std::shared_ptr<TItem>>> where(std::vector<std::shared_ptr<TItem>> &vector,
            std::function<bool(TItem &item)> condition){
    auto collection = std::make_shared<std::vector<std::shared_ptr<TItem>>>();
    for(auto item : vector){
        if(condition(*item)){
            collection->push_back(item);
        }
    }
    return collection;
}

template <typename TItem>
std::shared_ptr<std::vector<std::shared_ptr<TItem>>> distinct(std::vector<std::shared_ptr<TItem>> &vector){
    auto collection = std::make_shared<std::vector<std::shared_ptr<TItem>>>();
    for(auto item : vector){
        if(!contains(*collection, *item)){
            collection->push_back(item);
        }
    }
    return collection;
}

template <typename TItem, typename TAttr>
std::shared_ptr<std::vector<std::shared_ptr<TItem>>> distinctBy(std::vector<std::shared_ptr<TItem>> &vector,
            std::function<TAttr(TItem&)> selector){
    auto collection = std::make_shared<std::vector<std::shared_ptr<TItem>>>();
    auto attrCollection = std::vector<TAttr>();
    for(auto item : vector){
        auto attr = selector(*item);
        if(!contains(attrCollection, attr)){
            collection->push_back(item);
            attrCollection.push_back(attr);
        }
    }
    return collection;
}

template <typename TItem, typename TResult>
std::shared_ptr<std::vector<std::shared_ptr<TResult>>> select(std::vector<std::shared_ptr<TItem>> &vector,
            std::function<TResult(TItem&)> selector){
    auto collection = std::make_shared<std::vector<std::shared_ptr<TResult>>>();
    for(auto item : vector){
        auto result = selector(*item);
        collection->push_back(std::make_shared<TResult>(result));
    }
    return collection;
}

template <typename TItem>
std::shared_ptr<TItem> aggregate(std::vector<std::shared_ptr<TItem>> &vector,
            std::function<TItem(TItem &current, TItem &next)> aggregator){
    auto result = std::make_shared<TItem>();
    if(vector.size() == 0){
        return result;
    }
    *result = *vector[0];
    for(int i = 1; i < vector.size(); i++){
        auto next = vector[i];
        *result = aggregator(*result, *next);
    }
    return result;
}

template <typename TItem>
int count(std::vector<TItem> &vector){
    return vector.size();
}


#endif