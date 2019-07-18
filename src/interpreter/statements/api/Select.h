#ifndef LOODB_SQLSELECT_H
#define LOODB_SQLSELECT_H

#include "Statement.h"
#include "../../../schema/api/Entry/Entry.h"
#include <memory>
#include <tuple>
#include <vector>

using namespace std;

class SQLSelect : public SQLStatement {
  // Place public first so Impl
  // can recognize WhereTree
  public:
    // Public class representing where tree
    class WhereTree {
      public:
        friend class SQLSelect;

        // leaf: is a leaf
        bool leaf_;

        // op: "AND" or "OR" if leaf == false
        std::string op_;

        // operands if leaf == false
        std::unique_ptr<WhereTree> where1_;
        std::unique_ptr<WhereTree> where2_;

        // column name and entry if leaf == true
        std::tuple<std::string, std::unique_ptr<Entry>> expr_;

        // Lead constructor
        WhereTree(std::string, std::unique_ptr<Entry>);

        // Non leaf constructor
        // Takes in operation and two operands
        WhereTree(std::string, std::unique_ptr<WhereTree>, std::unique_ptr<WhereTree>);
    };

    // Constructor
    SQLSelect(std::string, std::vector<std::string>, bool, unique_ptr<SQLSelect::WhereTree>);

    // Get columns
    std::vector<std::string>& getColumns() const;

    // Return if statement has a where
    bool hasWhere() const;
    // Get where tree
    unique_ptr<SQLSelect::WhereTree>& getWhereTree() const;
    // Print where tree
    void printWhere();
  
  private:
    // Private members of SQLSelect
    class Impl{
        // columns_: vector of column names
        vector<string> columns_;

        // where_: has a where clause
        bool where_;

        // whereTree_: a parse tree of where clause
        unique_ptr<SQLSelect::WhereTree> whereTree_;

        // Print whereTreeHelper_
        void printWhereTreeHelper(std::unique_ptr<SQLSelect::WhereTree>&);
      public:

        // Impl Constructor
        Impl(vector<string> columns, bool where, unique_ptr<SQLSelect::WhereTree> whereTree);

        // Get columns
        std::vector<std::string>& getColumns_();
        // Get where_
        bool getWhere();
        // Get whereTree_
        unique_ptr<SQLSelect::WhereTree>& getWhereTree_();
        // Print whereTree_
        void printWhereTree();
    };

    // Private pImpl for SQLSelect
    std::unique_ptr<Impl> impl_;
};

#endif
