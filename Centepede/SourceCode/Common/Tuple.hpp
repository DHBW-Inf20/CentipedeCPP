#ifndef TUPLE_HPP
#define TUPLE_HPP

template<typename TItem1, typename TItem2>
class Tuple
{
    private:
        TItem1 item1;
        TItem2 item2;

    public:
        Tuple(TItem1 item1, TItem2 item2)
            :item1(item1), item2(item2)
        {
        }

        void setItem1(TItem1 item1)
        {
            this->item1 = item1;
        }

        void setItem2(TItem2 item2)
        {
            this->item2 = item2;
        }

        TItem1 getItem1()
        {
            return this->item1;
        }

        TItem2 getItem2()
        {
            return this->item2;
        }
};

#endif