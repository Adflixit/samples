#ifndef ITEMS_H
#define ITEMS_H

class ItemContainer;

/* Items can only exist inside containers */
class ItemStack {
public:
  ItemStack(ItemContainer *cont, uint32_t id, uint64_t size=1L)
    : m_cont(cont)
    , m_id(id)
    , m_size(size) {}
  ~ItemStack() {}

  ItemContainer *Container() const {return m_cont;}
  uint64_t Size() const {return m_size;}
  std::string &Name() const {return m_name;}
  uint32_t Id() const {return m_id;}

  uint64_t operator+(uint64_t a) {return m_size + a;}
  uint64_t operator-(uint64_t a) {return m_size - a;}
  uint64_t operator*(float a) {return m_size * a;}
  uint64_t operator/(float a) {return m_size / a;}
  uint64_t &operator++() {return ++m_size;}
  uint64_t operator++(int) {return m_size++;}
  uint64_t &operator--() {return --m_size;}
  uint64_t operator--(int) {return m_size--;}
  uint64_t &operator+=(uint64_t a) {return m_size += a;}
  uint64_t &operator-=(uint64_t a) {return m_size -= a;}
  uint64_t &operator*=(uint64_t a) {return m_size *= a;}
  uint64_t &operator/=(uint64_t a) {return m_size /= a;}
  bool operator==(const ItemStack &item) const {return m_size == item.Size();}
  bool operator!=(const ItemStack &item) const {return m_size != item.Size();}
  bool operator>(const ItemStack &item) const {return m_size > item.Size();}
  bool operator<(const ItemStack &item) const {return m_size < item.Size();}
  bool operator>=(const ItemStack &item) const {return m_size >= item.Size();}
  bool operator<=(const ItemStack &item) const {return m_size <= item.Size();}

private:
  ItemContainer *m_cont;
  uint32_t m_id;
  ftuint64_t m_size;
};

/* Item quantifier */
struct Iq {
  Iq(uint32_t _id, uint64_t _n=1L) : id(_id), n(_n) {}
  const uint32_t id;
  const uint64_t n;
};

/* Item transmit info */
struct Ti {
  Ti(ItemContainer *_cont, Iq _iq, bool _all=false) : cont(_cont), iq(_iq), all(_all) {}
  const ItemContainer *cont;
  const Iq iq;
  const bool all;
};

class ItemContainer {
public:
  ItemContainer();
  ~ItemContainer();

  virtual bool HasItem(uint32_t id) {return Iter(id) != m_items.end();}
  virtual uint64_t Count(uint32_t id) {return Access(id).Size();}
  virtual bool operator+=(Iq iq);             // return true if item has been added successfully
  virtual bool operator-=(Iq iq);             // return true if item has been removed successfully  
  virtual bool Move(It it);                   // return true if items have been moved successfully
  virtual bool MoveAll(ItemContainer *cont);  // return true if all items have been moved into this containter successfully

private:
  std::vector<ItemStack>::iterator Iter(uint32_t id);  // find iterator by id

  std::vector<ItemStack> m_items;
};

#endif
