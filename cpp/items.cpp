#include "items.h"

#include <algorithm>

std::vector<ItemStack>::iterator ItemContainer::Iter(uint32_t id) {
  static const auto callback = [id](const ItemStack &item) {return item.Id() == id;};
  return std::find_if(m_items.begin(), m_items.end(), callback);
}

bool ItemContainer::operator+=(Iq iq) {
  if (iq.id == 0) {
    return false;
  }
  auto it = Iter(iq.id);
  if (it != m_items.end()) {
    (*it) += iq.n;
  } else {
    m_items.push_back(ItemStack(this, iq.id, iq.n));
  }
  return true;
}

bool ItemContainer::operator-=(Iq iq) {
  if (iq.id == 0) {
    return false;
  }
  auto it = Iter(iq.id);
  if (it != m_items.end()) {
    (*it) -= iq.n;
    if ((*it).Size() == 0) {
      m_items.erase(it);
    }
  }
  return true;
}

bool ItemContainer::Move(Ti ti) {
  if (!ti.cont || ti.cont == this) {
    return false;
  }
  // has item / quantity sufficient
  uint64_t count = Count(ti.iq.id);
  if (HasItem(ti.iq.id) && count >= ti.iq.n) {
    if (ti.all) {
      Iq all(ti.iq.id, count);
      *this -= all;
      ti.cont += all;
    } else {
      *this -= ti.iq;
      ti.cont += ti.iq;
    }
    return true;
  }
  return false;
}

bool ItemContainer::MoveAll(ItemContainer *cont) {
  if (!cont || ti.cont == this) {
    return false;
  }
  auto it = m_items.begin();
  while (it != m_items.end()) {
    cont->m_items += Iq((*it).Id(), (*it).Size());
    m_items.erase(it);
    it++;
  }
  return true;
}
