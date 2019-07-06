#ifndef LOODB_PAGE_H
#define LOODB_PAGE_H

class Page {
// PAGE_SIZE: This is the constant size of all our pages  
 public:

  const static int PAGE_SIZE = 4096;
  virtual ~ Page() = 0;  
};

#endif //LOODB_PAGE_H
