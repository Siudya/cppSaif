/*
 * Copyright (c) 2014-2014 Wei Song <songw@cs.man.ac.uk>
 * Advanced Processor Technologies Group, School of Computer Science
 * University of Manchester, Manchester M13 9PL UK
 *
 * This source code is free software; you can redistribute it
 * and/or modify it in source code form under the terms of the GNU
 * General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

/*
 * A saif database
 * 06/02/2014 Wei Song
 *
 *
 */

#ifndef SAIF_DB_H_
#define SAIF_DB_H_

#include <gmpxx.h>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace saif {

// a switch record
class SaifRecord {
  public:
  SaifRecord();
  mpz_class T0;
  mpz_class T1;
  mpz_class TX;
  mpz_class TZ;
  mpz_class TC;
  mpz_class IG;
  mpz_class TB;

  virtual std::ostream &streamout(std::ostream &) const;
};

inline std::ostream &operator<<(std::ostream &os, const SaifRecord &rhs) {
  return rhs.streamout(os);
}

// a signal (single or multi bits)
class SaifSignal {
  public:
  std::unordered_map<int, std::shared_ptr<SaifSignal>> bits;
  std::shared_ptr<SaifRecord> data;

  virtual std::ostream &streamout(std::ostream &) const;
  virtual std::ostream &streamout(std::ostream &, const std::string &,
                                  const std::string &,
                                  unsigned int indent = 0) const;
};

inline std::ostream &operator<<(std::ostream &os, const SaifSignal &rhs) {
  return rhs.streamout(os);
}

// instance
class SaifInstance {
  public:
  std::unordered_map<std::string, std::shared_ptr<SaifSignal>> signals;
  std::unordered_map<std::string, std::shared_ptr<SaifInstance>> instances;
  std::string module_name;

  virtual std::ostream &streamout(std::ostream &, const std::string &,
                                  unsigned int indent = 0) const;
  virtual std::ostream &streamout(std::ostream &) const;
};

inline std::ostream &operator<<(std::ostream &os, const SaifInstance &rhs) {
  return rhs.streamout(os);
}

// database
class SaifDB {
  public:
  std::string version;
  std::string direction;
  std::string date;
  std::string vendor;
  std::string program_name;
  std::string tool_version;
  std::string divider;
  mpz_class duration;
  std::pair<mpz_class, std::string> timescale;

  std::shared_ptr<SaifInstance> top;
  std::string top_name;

  virtual std::ostream &streamout(std::ostream &) const;
};

inline std::ostream &operator<<(std::ostream &os, const SaifDB &rhs) {
  return rhs.streamout(os);
}

}// namespace saif

#endif
