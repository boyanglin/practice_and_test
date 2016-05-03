#ifndef ITEMS_H_
#define ITEMS_H_


#define ITEM_INIT(itemNum) namespace item##itemNum \
                           {

#define ITEM_END void run(); \
             }

namespace EMCPP
{
    void runItem(unsigned long item);
} //namespace EMCPP


#endif //ITEMS_H_