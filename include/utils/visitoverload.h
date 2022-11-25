#ifndef TEA_UTILS_VISITOVERLOAD_H
#define TEA_UTILS_VISITOVERLOAD_H

namespace tea {

// utility to allow overloading lambdas for use in std::visit.
// sourced from https://stackoverflow.com/questions/64017982/c-equivalent-of-rust-enums,
// which sourced it from https://www.cppstories.com/2018/09/visit-variants/
template<class... Ts>
struct VisitOverload : Ts... {
    using Ts::operator()...;
};
template<class... Ts>
VisitOverload(Ts...) -> VisitOverload<Ts...>;

}

#endif // TEA_UTILS_VISITOVERLOAD_H