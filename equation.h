//
// Author : Toru Shiozaki
// Date   : Jan 2012
//

#ifndef __EQUATION_H
#define __EQUATION_H

#include <list>
#include "diagram.h"

class Equation {
  protected:
    // list of diagrams
    std::list<std::shared_ptr<Diagram> > diagram_;
    // internal function used by factorize()
    void duplicates_(const bool);

  public:
    Equation(std::shared_ptr<Diagram>);
    ~Equation() {};

    // print function
    void print();
    // active parts are processed
    void active();
    // identifys the same terms
    void duplicates();
    // refresh indices in each diagram
    void refresh_indices();

    std::list<std::shared_ptr<Diagram> > diagram() { return diagram_; };

};

#endif
