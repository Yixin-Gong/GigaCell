//
// Created by eric on 23-9-15.
//

#ifndef GIGACELL_GIGACELL_WRITER_WRITER_H_
#define GIGACELL_GIGACELL_WRITER_WRITER_H_
#include "placement/place_db.h"
namespace gigaplace{
class writer {
 public:
  writer() = default;
  static void exporter(PlaceDB &pl_db);

};

}

#endif //GIGACELL_GIGACELL_WRITER_WRITER_H_
