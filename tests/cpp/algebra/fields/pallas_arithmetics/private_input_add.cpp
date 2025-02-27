#ifndef __ZKLLVM__
#include "../../../read_boost_json.hpp"
#include <fstream>
#endif

#include <nil/crypto3/algebra/curves/pallas.hpp>

using namespace nil::crypto3::algebra::curves;

[[circuit]] typename pallas::base_field_type::value_type
    pallas_field_add([[private_input]] typename pallas::base_field_type::value_type a,
                     [[private_input]] typename pallas::base_field_type::value_type b) {

    typename pallas::base_field_type::value_type c = a + b;

    #ifndef __ZKLLVM__
    std::cout << c.data <<std::endl;
    #endif

    return c;
}

#ifndef __ZKLLVM__

int main (int argc, char *argv[]){
    if (argc != 2) {
        std::cerr << "one command line argument must be provided\n";
        std::abort();
    }

    boost::json::value input_json = read_boost_json(std::string(argv[1]));

    using BlueprintFieldType = typename pallas::base_field_type;
    typename BlueprintFieldType::value_type a = read_field <BlueprintFieldType>(input_json, 0);
    typename BlueprintFieldType::value_type b = read_field <BlueprintFieldType>(input_json, 1);

    pallas_field_add(a, b);
    return 0;
}
#endif
