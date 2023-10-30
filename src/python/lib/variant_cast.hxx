#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <variant>

// this does not work for MSVC14, as specified here:
// see https://pybind11.readthedocs.io/en/stable/advanced/cast/stl.html#c-17-library-containers
namespace pybind11 {
namespace detail {


    template <typename... Ts>
    struct type_caster<std::variant<Ts...>> : variant_caster<std::variant<Ts...>> {};

    // Specifies the function used to visit the variant -- using `std::visit`
    template <>
    struct visit_helper<std::variant> {
        template <typename... Args>
        static auto call(Args &&...args) -> decltype(std::visit(args...)) {
            return std::visit(args...);
        }
    };
}
}
