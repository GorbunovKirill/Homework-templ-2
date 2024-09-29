#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

class SqlSelectQueryBuilder {
public:
   
    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept {
        if (!columns_.empty()) {
            columns_ += ", ";
        }
        columns_ += column;
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (const auto& column : columns) {
            AddColumn(column);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) noexcept {
        if (!where_clauses_.empty()) {
            where_clauses_ += " AND ";
        }
        where_clauses_ += column + "=" + value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& [column, value] : kv) {
            AddWhere(column, value); 
        }
        return *this;
    }

    std::string BuildQuery() const {
        std::ostringstream query;

        if (columns_.empty()) {
            query << "SELECT *";
        }
        else {
            query << "SELECT " << columns_;
        }

        query << " FROM " << table_;

        if (!where_clauses_.empty()) {
            query << " WHERE " << where_clauses_;
        }

        query << ";";

        return query.str();
    }

private:
    std::string columns_;
    std::string table_;
    std::string where_clauses_;
};

int main() {
    SqlSelectQueryBuilder query_builder;

    std::vector<std::string> columns = { "name", "phone", "email" };
    query_builder.AddColumns(columns);

    query_builder.AddFrom("students");

    std::map<std::string, std::string> conditions = { {"id", "42"}, {"name", "John"} };
    query_builder.AddWhere(conditions);

    std::string query = query_builder.BuildQuery();
    std::cout << "Generated query: " << query << std::endl;

    return 0;
}
