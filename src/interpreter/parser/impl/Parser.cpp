#include "../api/Parser.h"
#include "../../statements/api/Drop.h"
#include "../../statements/api/Select.h"
#include "../../statements/api/Insert.h"
#include "../../statements/api/Create.h"
#include <string>
using namespace std;

unique_ptr<SQLStatement> Parser::parse(string h) {
  return make_unique<SQLDrop>(h);
}
