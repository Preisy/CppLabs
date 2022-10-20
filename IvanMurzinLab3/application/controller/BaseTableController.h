#pragma once
#include <string>

#include "IController.h"
#include "Table.h"
#include "Response.h"
#include "TupleDeserializer.h"

namespace Controllers {

    template<class Key, class Head, class...Tail>
    class BaseTableController : public IController {
        Models::Table<Key, Head, Tail...> table;

    protected:
        Response get(const std::string & args) {
            std::istringstream is(args);

            std::tuple<Key> t;
            try {
                t = TupleDeserializer<Key>::deserialize(is);
            } catch (std::exception & e) {
                return {e.what(), InternalServerError};
            }
            if (!is || !is.eof()) {
                return {"Unknown parameter pack", BadRequest};
            }

            auto resource = table.getItem(std::get<0>(t));

            if (resource.hasData())
                return {
                    TupleDeserializer<Key, Head, Tail...>::serialize(resource.getData())
                , Ok};
            else
                return {"Not Found", NotFound};
        }

        Response post(const std::string & args) {
            std::istringstream is(args);

            std::tuple<Key, Head, Tail...> t;
            try {
                t = TupleDeserializer<Key, Head, Tail...>::deserialize(is);
            } catch (std::exception & e) {
                return {e.what(), InternalServerError};
            }
            if (!is || !is.eof()) {
                return {"Unknown parameter pack", BadRequest};
            }

            if (table.add(std::move(t)))
                return {"", Ok};
            else
                return {"Already in", Ok};
        }

        Response put(const std::string & args) {
            std::istringstream is(args);

            std::tuple<Key, Head, Tail...> t;
            try {
                t = TupleDeserializer<Key, Head, Tail...>::deserialize(is);
            } catch (std::exception & e) {
                return {e.what(), InternalServerError};
            }
            if (!is || !is.eof()) {
                return {"Unknown parameter pack", BadRequest};
            }

            if (table.update(std::move(t)))
                return {"", Ok};
            else
                return {"Not Found", Ok};
        }

        Response del(const std::string & args) {
            std::istringstream is(args);

            std::tuple<Key> t;
            try {
                t = TupleDeserializer<Key>::deserialize(is);
            } catch (std::exception & e) {
                return {e.what(), InternalServerError};
            }
            if (!is || !is.eof()) {
                return {"Unknown parameter pack", BadRequest};
            }
            if (table.remove(std::get<0>(t)))
                return {"", Ok};
            else
                return {"Not Found", NotFound};
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
                os << TupleDeserializer<Key, Head, Tail...>::serialize(it);
                os << std::endl;
            }

            return {os.str(), Ok};
        }

    public:
        BaseTableController() = default;


        ~BaseTableController() override = default;

        BaseTableController(BaseTableController && matrixController) noexcept {
            table = std::move(matrixController.table);
        }

    };
}