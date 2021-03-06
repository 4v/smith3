//
// SMITH3 - generates spin-free multireference electron correlation programs.
// Filename: diagram.h
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the SMITH3 package.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef __DIAGRAM_H
#define __DIAGRAM_H

#include "tensor.h"
#include <initializer_list>

namespace SMITH3 {
namespace Prep {

class Diagram {
  protected:
    std::list<std::shared_ptr<Tensor>> op_;
    std::string label_;
    double fac_;
    std::string scalar_;
    std::pair<bool,bool> braket_;
    bool ci_derivative_;

  public:
    Diagram(const std::list<std::shared_ptr<Tensor>> o, const std::string la, double d)
     : op_(o), label_(la), fac_(d), scalar_(""), braket_(std::make_pair(false,false)), ci_derivative_(false) { }
    Diagram(const std::list<std::shared_ptr<Tensor>> o, const std::string la, std::string s)
     : op_(o), label_(la), fac_(1.0), scalar_(s), braket_(std::make_pair(false,false)), ci_derivative_(false) { }
    Diagram(const std::list<std::shared_ptr<Tensor>> o, const std::string la, double d, std::string s)
     : op_(o), label_(la), fac_(d), scalar_(s), braket_(std::make_pair(false,false)), ci_derivative_(false) { }

    Diagram(const std::list<std::shared_ptr<Tensor>> o, const std::string la, double d, std::pair<bool,bool> der)
     : op_(o), label_(la), fac_(d), scalar_(""), braket_(der), ci_derivative_(true) { }
    Diagram(const std::list<std::shared_ptr<Tensor>> o, const std::string la, std::string s, std::pair<bool,bool> der)
     : op_(o), label_(la), fac_(1.0), scalar_(s), braket_(der), ci_derivative_(true) { }
    Diagram(const std::list<std::shared_ptr<Tensor>> o, const std::string la, double d, std::string s, std::pair<bool,bool> der)
     : op_(o), label_(la), fac_(d), scalar_(s), braket_(der), ci_derivative_(true) { }

    const std::list<std::shared_ptr<Tensor>>& op() const { return op_; };
    std::string label() const { return label_; };
    std::string diag_label() const { return "d" + label_; };
    std::string eqn_label() const { return "e" + label_; };

    std::string index_str() const {
      std::stringstream ss;
      for (auto j = op_.begin(); j != op_.end(); ++j) {
        if (j != op_.begin()) ss << ", ";
        ss << (*j)->tag();
      }
      return ss.str();
    }

    std::string construct_str() const {
      std::stringstream ss;
      ss << "  list<shared_ptr<Operator>> " << label_ << " = {" << index_str() << "};" << std::endl;
      return ss.str();
    }

    std::string scalar() const { return scalar_; };

    std::string diagram_str() const {
      std::stringstream ss;
      if (!ci_derivative_) {
        ss << "  auto " << diag_label() << " = make_shared<Diagram>(" << label() << ", " << fac_ << ", \"" << scalar() << "\"" << ");" << std::endl;
      } else {
        ss << "  auto " << diag_label() << " = make_shared<Diagram>(" << label() << ", " << fac_ << ", \"" << scalar() << "\"" << (braket_.first == true ? ", make_pair(true, false));" : ", make_pair(false, true));") << std::endl;
      }
      return ss.str();
    };

    std::string equation_str() const {
      std::stringstream ss;
      ss << "  auto " << eqn_label() << " = make_shared<Equation>(" << diag_label() << ", theory);" << std::endl;
      return ss.str();
    }

};

}}

#endif
