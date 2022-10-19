#pragma once
#include <string>

#include "IController.h"
#include "Table.h"
#include "Response.h"
#include "TupleDeserializer.h"

namespace Controllers {

    template<class Key, class Head, class...Tail>
    class TableController : public IController {
        Models::Table<Key, Head, Tail...> table;

    protected:
        Response add(const std::string & args) {
            std::istringstream is(args);

            std::tuple<Key, Head, Tail...> t;
            try {
                t = TupleDeserializer<Key, Head, Tail...>::deserialize(is);
            } catch (std::invalid_argument & e) {
                return {e.what(), BadRequest};
            } catch (std::exception & e) {
                return {e.what(), InternalServerError};
            }
            table.add(std::move(t));

            return {"", Ok};
        }

    private:
        void printArgs(std::ostream & os) {}

        template<class HHead, class...TTail>
        void printArgs(std::ostream & os, HHead&& head, TTail&&...tail) {
            os << std::forward<HHead>(head) << " ";
            printArgs(os, std::forward<TTail>(tail)...);
        }

    protected:
        Response print(const std::string & args) {
            if (!args.empty()) return {"", BadRequest};

            std::ostringstream os(args);

            for(auto & it : table) {
                applyTuple([&os, this](const Key & key, const Head & head, const Tail & ... tail){
                    printArgs(os, key, head, tail...);
                }, it);
                os << '\n';
            }

            return {os.str(), Ok};
        }

    public:
        TableController() = default;


        ~TableController() override = default;

        TableController(TableController && matrixController) noexcept {
            table = std::move(matrixController.table);
        }

    };
}