#ifndef ITEMS_H_
#define ITEMS_H_


#define ITEM_INIT(itemNum) namespace item##itemNum \
                           {

#define ITEM_END void run(); \
             }

namespace MECPP
{
    void runItem(unsigned int item);

    //tem 18: Use std::unique_ptr for exclusive-ownership resource management.
    ITEM_INIT(18)

    ITEM_END

    //Item 19: Use std::shared_ptr for shared-ownership resource management.
    ITEM_INIT(19)

    ITEM_END

} //namespace MECPP


#endif //ITEMS_H_