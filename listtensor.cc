//
// Author : Toru Shiozaki
// Date   : Jan 2012
//

#include "listtensor.h"

using namespace std;

ListTensor::ListTensor(shared_ptr<Diagram> d) {
  // factor
  fac_ = d->fac();
  // vector of tensors
  for (auto i = d->op().begin(); i != d->op().end(); ++i) {
    shared_ptr<Tensor> t(new Tensor(*i));
    list_.push_back(t);
  }
  if (d->rdm()) {
    shared_ptr<Tensor> t(new Tensor(d->rdm()));
    list_.push_back(t);
  }
  // dag
  dagger_ = d->dagger();
}


void ListTensor::print() const {
  cout << setw(4) << setprecision(1) << fixed <<  fac_ << " ";
  for (auto i = list_.begin(); i != list_.end(); ++i) cout << (*i)->str();
  if (dagger_) cout << " ** Daggered object added **";
  cout << endl;
  for (auto i = list_.begin(); i != list_.end(); ++i) {
    if ((*i)->active()) (*i)->active()->print("   ");
  }

  cout << endl;
  
}


void ListTensor::absorb_all_internal() {
  auto j = list_.begin();
  // first find active
  for (auto i = list_.begin(); i != list_.end(); ++i) {
    if ((*i)->active()) j = i;
  }
  list<list<shared_ptr<Tensor> >::iterator> remove;
  for (auto i = list_.begin(); i != list_.end(); ++i) {
    if ((*i)->all_active() && !(*i)->active()) {
      (*j)->merge(*i);
      remove.push_back(i);
    }
  }
  for (auto i = remove.begin(); i != remove.end(); ++i) list_.erase(*i);
}


shared_ptr<Tensor> ListTensor::target() const {
  list<shared_ptr<Index> > ind;
  for (auto t = list_.begin(); t != list_.end(); ++t) {
    list<shared_ptr<Index> > index = (*t)->index();
    for (auto j = index.begin(); j != index.end(); ++j) {
      bool found = false;
      list<shared_ptr<Index> >::iterator remove;
      for (auto i = ind.begin(); i != ind.end(); ++i) {
        if ((*i)->num() == (*j)->num()) {
          found = true;
          remove = i;
          break;
        }
      }
      if (found) {
        ind.erase(remove);
      } else {
        ind.push_back(*j);
      }
    }
  }
  shared_ptr<Tensor> t(new Tensor(1.0, "I", ind));
  return t;
}


shared_ptr<ListTensor> ListTensor::rest() const {
  list<shared_ptr<Tensor> > r = list_; 
  r.pop_front();     
  shared_ptr<ListTensor> out(new ListTensor(fac_, r, dagger_));
  return out;
}
