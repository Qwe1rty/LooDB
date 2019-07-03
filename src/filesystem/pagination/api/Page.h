#ifndef LOODB_PAGE_H
#define LOODB_PAGE_H

class Page {

public:

    enum Type { // consider switching to enum class when converters/enum util are implemented

        DB_HEAD = 0,
        TABLE_HEAD,
        COLUMN_HEAD,

        BP_LEAF,
        BP_INTERNAL,
        B_NODE,

        DATA_ENTRY,
        OVERFLOW
    };

private:

    Type type_;

    explicit Page(Type);


    Page(const Page&) = default;
    Page& operator= (const Page&) = default;

    Page(Page&&) noexcept = default;
    Page& operator= (Page&&) noexcept = default;

    virtual ~Page() = 0;
};


#endif //LOODB_PAGE_H
