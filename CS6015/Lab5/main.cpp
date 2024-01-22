/**
 * \mainpage MSDScript
 * \author Laura Zhang
 * \date 02-07-2023
 */

#define CATCH_CONFIG_RUNNER

#include "catch.h"
#include "expr.h"
#include "parse.h"
#include "cmdline.h"
#include <iostream>

bool run_tests() {
     const char *argv[] = {"arith"};
     return (Catch::Session().run(1, argv) == 0);
}

run_mode_t use_arguments(int argc, const char * argv[]) {
    if (argc > 1) {
        bool tested = false;

        // iterate through all the arguments
        for (int i = 1; i < argc; i++) {
            std::string cur_cmd = argv[i];

            if (cur_cmd == "--help") {
                std::cout << "Options include:" << std::endl;
                std::cout << "    --help <get helper text that describes what arguments are allowed>" << std::endl;
                std::cout << "    --test <run catch2 test on current execution file>" << std::endl;
                std::cout << "    --interp <accept a single expression and print the result>" << std::endl;
                std::cout << "    --print <accept a single expression and print it to standard output>" << std::endl;
                std::cout << "    --pretty-print <accept a single expression and print it to standard output using the pretty_print method>" << std::endl;

                exit(0);
            }
            else if (cur_cmd == "--test") {
                // if "--test" is seen before
                if (tested) {
                    std::cerr << "Error: Duplicated tests." << std::endl;
                    exit(1);
                }

                // run catch2 tests, exit with 1 if there are any failures
                if (! run_tests()) {
                    exit(1);
                }

                tested = true;
            }
            else if (cur_cmd == "--interp") {
                std::cout << "Type your expression here: ";

                std::string line;
                while (std::getline(std::cin, line)) {
                    std::cout << "--------------------" << std::endl;
                    std::cout << "interp value: " << parse_str(line)->interp() << std::endl;
                    std::cout << "--------------------" << std::endl << std::endl;
                }

                return do_interp;
            }
            else if (cur_cmd == "--print") {
                std::cout << "Type your expression here: ";

                std::string line;
                while (std::getline(std::cin, line)) {
                    std::cout << "--------------------" << std::endl;
                    std::cout << "print value: ";
                    parse_str(line)->print(std::cout);
                    std::cout << std::endl;
                    std::cout << "--------------------" << std::endl << std::endl;
                }

                return do_print;
            }
            else if (cur_cmd == "--pretty-print") {
                std::cout << "Type your expression here: ";

                std::string line;
                while (std::getline(std::cin, line)) {
                    std::cout << "--------------------" << std::endl;
                    std::cout << "pretty print value: " << std::endl;
                    std::cout << parse_str(line)->pretty_print_to_string() << std::endl;
                    std::cout << "--------------------" << std::endl << std::endl;
                }

                return do_pretty_print;
            }
            else {
                std::cerr << "Error: Invalid command." << std::endl;
                exit(1);
            }
        }
    }
    else {
        std::cerr << "Error: At least two arguments are required. "
                  << "Please use --help for the options." << std::endl;
        exit(1);
    }

    exit(0);
}

int main(int argc, const char * argv[]) {
    try {
        use_arguments(argc, argv);

        switch (use_arguments(argc, argv)) {
            case do_nothing:
                exit(0);
            case do_interp:
                exit(0);
            case do_print:
                exit(0);
            case do_pretty_print:
                exit(0);
            default:
                exit(0);
        }
    }
    catch (std::runtime_error exn) {
        std::cerr << exn.what() << std::endl;
        return 1;
    }
}

TEST_CASE("equals") {
    // testing NumExpr::equals()
    CHECK((new NumExpr(1))->equals(new NumExpr(1)));
    CHECK((new NumExpr(1))->equals(new NumExpr(0)) == false);
    CHECK((new NumExpr(1))->equals(new NumExpr(-1)) == false);
    CHECK((new NumExpr(5))->equals(nullptr) == false);

    // testing AddExpr::equals()
    // adding NumExpr
    CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))->equals(new AddExpr(new NumExpr(1),new NumExpr(2))));
    CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new NumExpr(3),new NumExpr(2))) == false);
    CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(nullptr) == false);
    // adding VarExpr
    CHECK((new AddExpr(new VarExpr("abc"), new VarExpr("")))->equals(new AddExpr(new VarExpr("abc"), new VarExpr(""))));
    CHECK((new AddExpr(new VarExpr("abc"), new VarExpr("def")))->equals(new AddExpr(new VarExpr("abc"), new VarExpr(""))) == false);

    // testing MultExpr::equals()
    // multiplying NumExpr
    CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))->equals(new MultExpr(new NumExpr(1),new NumExpr(2))));
    CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))->equals(new MultExpr(new NumExpr(2),new NumExpr(1))) == false);
    CHECK((new MultExpr(new NumExpr(-2), new NumExpr(2)))->equals(new AddExpr(new NumExpr(1),new NumExpr(2))) == false);
    // multiplying VarExpr
    CHECK((new MultExpr(new VarExpr("abc"), new VarExpr("")))->equals(new MultExpr(new VarExpr("abc"), new VarExpr(""))));
    CHECK((new MultExpr(new VarExpr("abc"), new VarExpr("def")))->equals(new MultExpr(new VarExpr("abc"), new VarExpr("abc"))) == false);

    // testing VarExpr::equals()
    CHECK((new VarExpr("abc"))->equals(new VarExpr("abc")));
    CHECK((new VarExpr(""))->equals(new VarExpr("")));
    CHECK((new VarExpr("abc"))->equals(new VarExpr("")) == false);
    CHECK((new VarExpr("x"))->equals(new VarExpr("y")) == false);
    CHECK((new VarExpr("x"))->equals(new NumExpr(1)) == false);
    CHECK((new VarExpr("abc"))->equals(nullptr) == false);

    // testing LetExpr::equals()
    CHECK((new LetExpr("", (new NumExpr(-1)), (new AddExpr(new VarExpr(""), new NumExpr(2)))))->equals(nullptr) == false);
    CHECK((new LetExpr("x", (new NumExpr(0)), (new AddExpr(new VarExpr("x"), new NumExpr(2)))))
    ->equals((new LetExpr("x", (new NumExpr(0)), (new AddExpr(new VarExpr("x"), new NumExpr(2)))))));
}

TEST_CASE("interp") {
    // testing NumExpr::interp()
    CHECK((new NumExpr(0))->interp() == 0);
    CHECK((new NumExpr(2))->interp() == 2);
    CHECK((new NumExpr(-1))->interp() == -1);
    
    // testing AddExpr::interp()
    CHECK((new AddExpr(new NumExpr(-100), new NumExpr(100)))->interp() == 0);
    CHECK((new AddExpr(new AddExpr(new NumExpr(10), new NumExpr(15)),
                       new AddExpr(new NumExpr(20), new NumExpr(20))))->interp() == 65);
    
    // testing MultExpr::interp()
    CHECK((new MultExpr(new NumExpr(3), new NumExpr(2)))->interp() == 6);
    CHECK((new MultExpr(new MultExpr(new NumExpr(-1), new NumExpr(2)),
                        new MultExpr(new NumExpr(3), new NumExpr(4))))->interp() == -24);
    
    // testing VarExpr::interp()
    CHECK_THROWS_WITH((new VarExpr("x"))->interp(), "no value for variable");
    CHECK_THROWS_WITH((new VarExpr(""))->interp(), "no value for variable");

    // testing LetExpr::interp()
    CHECK((new AddExpr(
            new MultExpr(
                    new NumExpr(5),
                    (new LetExpr("x", new NumExpr(5), new VarExpr("x")))),
            new NumExpr(1)))->interp() == 26);

}

TEST_CASE("has_variable"){
    // testing NumExpr::has_variable()
    CHECK((new NumExpr(0))->has_variable() == false);
    CHECK((new NumExpr(-5))->has_variable() == false);
    
    // testing AddExpr::has_variable()
    CHECK((new AddExpr(new NumExpr(3), new NumExpr(1)))->has_variable() == false);
    CHECK((new AddExpr(new VarExpr("VarExpr"), new NumExpr(2)))->has_variable());
    CHECK((new AddExpr(new VarExpr("VarExpr_1"), new VarExpr("VarExpr_2")))->has_variable());
    
    // testing MultExpr::has_variable()
    CHECK((new MultExpr(new NumExpr(3), new NumExpr(1)))->has_variable() == false);
    CHECK((new MultExpr(new VarExpr("VarExpr"), new NumExpr(5)))->has_variable());
    CHECK((new MultExpr(new VarExpr("VarExpr_1"), new VarExpr("VarExpr_2")))->has_variable());
    
    // testing VarExpr::has_variable()
    CHECK((new VarExpr("x"))->has_variable());
    CHECK((new VarExpr(""))->has_variable());

    // testing LetExpr::has_variable()
    CHECK((new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))))->has_variable());
    CHECK((new LetExpr("y", new NumExpr(3), new AddExpr(new NumExpr(1), new NumExpr(2))))->has_variable() == false);
}

TEST_CASE("subst") {
    // testing NumExpr::subst()
    CHECK((new NumExpr(0))->subst("VarExpr", new NumExpr(0)));
    CHECK((new NumExpr(-10))->subst("VarExpr", new NumExpr(-10)));
    CHECK((new NumExpr(5))->subst("VarExpr", new NumExpr(5)));
    
    // testing AddExpr::subst()
    CHECK((new AddExpr(new NumExpr(2), new NumExpr(7)))->subst("x", new NumExpr(9)));
    CHECK((new AddExpr(new VarExpr("x"), new NumExpr(7)))->subst("x", new VarExpr("y"))
          ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));
    
    // testing MultExpr::subst()
    CHECK((new MultExpr(new NumExpr(3), new NumExpr(4)))->subst("x", new NumExpr(12)));
    
    // testing VarExpr::subst()
    CHECK((new VarExpr("VarExpr_1"))->subst("VarExpr_1", new VarExpr("VarExpr_1")));
    CHECK((new VarExpr("VarExpr_2"))->subst("VarExpr_1", new VarExpr("VarExpr_1")));
    CHECK((new VarExpr("x"))->subst("x", new AddExpr(new VarExpr("y"), new NumExpr(7)))
          ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));

    // testing LetExpr::subst()
    CHECK((new LetExpr("y", new NumExpr(3), new NumExpr(2)))->subst("y", new VarExpr("x"))->equals(new LetExpr("y", new NumExpr(3), new NumExpr(2))));
    CHECK((new LetExpr("y", new NumExpr(3), new NumExpr(2)))->subst("a", new VarExpr("x"))->equals(new LetExpr("y", new NumExpr(3), new NumExpr(2))));
}

TEST_CASE("print") {
    // testing to_string()
    CHECK((new MultExpr((new MultExpr(
                            (new NumExpr(10)),
                            (new NumExpr(10)))),
                        (new MultExpr(
                            (new NumExpr(10)),
                            (new NumExpr(10))))))->to_string() == "((10*10)*(10*10))");

    // testing NumExpr::print()
    std::stringstream ot1("");
    (new NumExpr(0))->print(ot1);
    CHECK(ot1.str() == "0");

    // testing VarExpr::print()
    std::stringstream ot2("");
    (new VarExpr("variable"))->print(ot2);
    CHECK(ot2.str() == "variable");

    // testing AddExpr::print()
    std::stringstream ot3("");
    (new AddExpr((new NumExpr(-1)), (new VarExpr("rhs"))))->print(ot3);
    CHECK(ot3.str() == "(-1+rhs)");

    // testing MultExpr::print()
    std::stringstream ot4("");
    (new MultExpr((new VarExpr("lhs")), (new NumExpr(0))))->print(ot4);
    CHECK(ot4.str() == "(lhs*0)");

    // testing LetExpr::print()
    std::stringstream ot5("");
    (new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->print(ot5);
    CHECK(ot5.str() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
}

TEST_CASE("pretty_print") {
    // testing NumExpr::pretty_print()
    CHECK((new NumExpr(0))->pretty_print_to_string() == "0");

    // testing VarExpr::pretty_print()
    CHECK((new VarExpr("variable"))->pretty_print_to_string() == "variable");

    // testing AddExpr::pretty_print()
    CHECK((new AddExpr((new NumExpr(-1)), (new VarExpr("rhs"))))->pretty_print_to_string() == "-1 + rhs");

    // testing MultExpr::pretty_print()
    CHECK((new MultExpr((new VarExpr("lhs")), (new NumExpr(0))))->pretty_print_to_string() == "lhs * 0");

    // going wild
    CHECK((new AddExpr(new NumExpr(1), new MultExpr(new NumExpr(2), new NumExpr(3))))->pretty_print_to_string() == "1 + 2 * 3");

    CHECK((new MultExpr(new NumExpr(1), new AddExpr(new NumExpr(2), new NumExpr(3))))->pretty_print_to_string() == "1 * (2 + 3)");

    CHECK((new MultExpr(new MultExpr(new NumExpr(2), new NumExpr(3)), new NumExpr(4)))->pretty_print_to_string() == "(2 * 3) * 4");

    CHECK((new MultExpr(new NumExpr(2), new MultExpr(new NumExpr(3), new NumExpr(4))))->pretty_print_to_string() == "2 * 3 * 4");

    CHECK((new AddExpr(
        new MultExpr(
            new NumExpr(9),
            new AddExpr(
                new NumExpr(4),
                new NumExpr(3))),
        new AddExpr(
            new MultExpr(
                new NumExpr(2),
                new NumExpr(4)),
            new NumExpr(1))))->pretty_print_to_string() == "9 * (4 + 3) + 2 * 4 + 1");

    CHECK((new MultExpr(
        new MultExpr(
            new NumExpr(10),
            new MultExpr(
                new MultExpr(
                    new NumExpr(10),
                    new NumExpr(10)),
                new NumExpr(10))),
        new MultExpr(
            new NumExpr(10),
            new NumExpr(10))))->pretty_print_to_string() == "(10 * (10 * 10) * 10) * 10 * 10");

    CHECK((new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->pretty_print_to_string() == "_let x = 5\n"
                                   "_in (_let y = 3\n"
                                   "     _in y + 2) + x");

    CHECK((new MultExpr(new MultExpr(new NumExpr(2), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1)))), new NumExpr(3)))
    ->pretty_print_to_string() == "(2 * _let x = 5\n"
                                  "     _in x + 1) * 3");
}

TEST_CASE("Pretty Print examples_Kevin") {
    std::stringstream out("");
    (new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = 5\n"
                       "_in x + 1");
    out.str(std::string());
    (new AddExpr(new LetExpr("x", new NumExpr(5), new VarExpr("x")), new NumExpr(1)))->pretty_print(out);
    CHECK(out.str() == "(_let x = 5\n"
                       " _in x) + 1");
    out.str(std::string());
    (new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1)))))->pretty_print(out);
    CHECK(out.str() == "5 * _let x = 5\n"
                       "    _in x + 1");
    out.str(std::string());
    (new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new VarExpr("x"))), new NumExpr(1)))->pretty_print(out);
    CHECK(out.str() == "5 * (_let x = 5\n"
                       "     _in x) + 1");
    out.str(std::string());
    (new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))
            ->pretty_print(out);
    CHECK(out.str() == "_let x = 5\n"
                       "_in (_let y = 3\n"
                       "     _in y + 2) + x");
    out.str(std::string());
    (new LetExpr("x", new LetExpr("y", new NumExpr(6), new MultExpr(new VarExpr("y"), new NumExpr(2))), new AddExpr(new VarExpr("x"), new NumExpr(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = _let y = 6\n"
                       "         _in y * 2\n"
                       "_in x + 1");

    LetExpr* tripleNestedLetExpr = new LetExpr("x", new NumExpr(1),
                                   new LetExpr("y", new NumExpr(1),
                                           new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z"))));
    LetExpr* tripleNestedLetExpr2 = new LetExpr("x", new NumExpr(1),
                                    new LetExpr("y", new NumExpr(1),
                                            new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
                                                    new AddExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z")))));
    LetExpr* tripleNestedLetExpr3 = new LetExpr("x", new NumExpr(1),
                                    new LetExpr("y", new NumExpr(1),
                                            new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
                                                    new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z")))));


    CHECK(tripleNestedLetExpr -> pretty_print_to_string() ==
          "_let x = 1\n"
          "_in _let y = 1\n"
          "    _in (x + y) * z"
    );
    CHECK(tripleNestedLetExpr2 -> pretty_print_to_string() ==
          "_let x = 1\n"
          "_in _let y = 1\n"
          "    _in _let z = x + 1\n"
          "        _in (x + y) + z"
    );
    CHECK(tripleNestedLetExpr3 -> pretty_print_to_string() ==
          "_let x = 1\n"
          "_in _let y = 1\n"
          "    _in _let z = x + 1\n"
          "        _in (x + y) * z"
    );
    LetExpr* tripleNestedLetExpr4 =new LetExpr("x", new NumExpr(5),
                                   new LetExpr("y", new NumExpr(3),
                                           new AddExpr(new VarExpr("y"), new NumExpr(2))));
    LetExpr* tripleNestedLetExpr5 =new LetExpr("x", new NumExpr(5),
                                   new AddExpr(new LetExpr("y", new NumExpr(3),
                                                   new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x")));

    SECTION("assignment_examples") {
        CHECK((new MultExpr(new MultExpr(new NumExpr (2), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x") ,new  NumExpr(1)))), new NumExpr(3))) -> pretty_print_to_string()
               == "(2 * _let x = 5\n"
                  "     _in x + 1) * 3");
    }
    SECTION("new_edge") {
        CHECK((new MultExpr(new NumExpr (2), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x") ,new  NumExpr(1))) )) -> pretty_print_to_string()
               == "2 * _let x = 5\n"
                  "    _in x + 1");
        CHECK((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1)))-> pretty_print_to_string()
               == "5 * (_let x = 5\n"
                  "     _in x * 2) + 1");
        CHECK((new MultExpr((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1))), new NumExpr(7)))-> pretty_print_to_string()
               == "(5 * (_let x = 5\n"
                  "      _in x * 2) + 1) * 7");
        CHECK((new LetExpr("x", new NumExpr(10), new MultExpr( new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new NumExpr(10))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       ->pretty_print_to_string()  == "_let x = 10\n"
                                                      "_in (x * (10 * 10) * 10) * 10 * 10");
        CHECK((new LetExpr("x", new NumExpr(1), new MultExpr( new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in (x * (10 * 10) * x) * 10 * 10" );
        CHECK((new LetExpr("x", new NumExpr(1), new MultExpr( new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new VarExpr("y"), new NumExpr(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in (x * (10 * 10) * x) * y * 10" );
    }
}

TEST_CASE("LetExpr_equals_mine") {
    SECTION("Values_same") {
        REQUIRE((new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x"))))->equals(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")))));
    }
    SECTION("Values_same_different_rhs") {
        REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x"))))->equals(new LetExpr("x", new NumExpr(5), new AddExpr(new NumExpr(2), new VarExpr("x")))));
    }
    SECTION("Values_same_different_lhs") {
        REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x"))))->equals(new LetExpr("y", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")))));
    }
    SECTION("Values_same_different_body") {
        REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x"))))->equals(new LetExpr("x", new NumExpr(4), new MultExpr(new NumExpr(3), new VarExpr("y")))));
    }
    SECTION("different_types") {
        REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x"))))->equals( new MultExpr(new NumExpr(3), new VarExpr("y"))));
    }
    SECTION("has") {
        REQUIRE((new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x"))))->has_variable());
    }
    SECTION("does_not_has") {
        REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new NumExpr(4))))->has_variable());
    }

    CHECK((new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x")))) -> to_string()
           == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
    CHECK((new LetExpr("x", new NumExpr(1),
                    new LetExpr("y", new NumExpr(1),
                            new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
                                    new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z")))))) -> to_string()
           == "(_let x=1 _in (_let y=1 _in (_let z=(x+1) _in ((x+y)*z))))");

    SECTION("hw_examples") {
        CHECK((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new VarExpr("x"))), new NumExpr(1))) -> interp() == 26);
        CHECK((new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))))) -> interp() == 30);
    }
    SECTION("from_pretty_print_edge") {
        CHECK((new MultExpr((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1))), new NumExpr(7))) -> interp() == 357); // 51 * 7
        CHECK((new LetExpr("x", new NumExpr(10), new MultExpr( new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new NumExpr(10))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       ->interp()  == 1000000);
        CHECK((new LetExpr("x", new NumExpr(1), new MultExpr( new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       ->interp()  == 10000);
        CHECK_THROWS_WITH( ((new LetExpr("x", new NumExpr(1), new MultExpr( new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new VarExpr("y"), new NumExpr(10)))))
                                    -> interp() == 10000), "no value for variable");
    }
    SECTION("bypass_middle_let") {
        CHECK ((new LetExpr("x", new NumExpr(2), new LetExpr("z", new NumExpr(4), new AddExpr(new VarExpr("x"), new NumExpr(10)))))
                       -> interp() == 12);
    }
}

TEST_CASE("parse") {
    CHECK_THROWS_WITH(parse_str(""), "bad input");
    CHECK_THROWS_WITH(parse_str("()"), "bad input");

    CHECK(parse_str("(1)")->equals(new NumExpr(1)));
    CHECK(parse_str("(((1)))")->equals(new NumExpr(1)));

    CHECK_THROWS_WITH(parse_str("(1"), "bad input");

    CHECK(parse_str("1")->equals(new NumExpr(1)));
    CHECK(parse_str("10")->equals(new NumExpr(10)));
    CHECK(parse_str("-3")->equals(new NumExpr(-3)));
    CHECK(parse_str("  \n 5  ")->equals(new NumExpr(5)));
    CHECK_THROWS_WITH(parse_str("-"), "invalid input");
    CHECK_THROWS_WITH(parse_str(" -   5  "), "invalid input");
    CHECK_THROWS_WITH( parse_str("0 + "), "bad input");
    CHECK_THROWS_WITH( parse_str("0        ++"), "bad input");

    CHECK(parse_str("x")->equals(new VarExpr("x")));
    CHECK(parse_str("xyz")->equals(new VarExpr("xyz")));
    CHECK(parse_str("xYz")->equals(new VarExpr("xYz")));
    CHECK_THROWS_WITH( parse_str("*t"), "bad input");
    CHECK_THROWS_WITH( parse_str("x Y"), "invalid input" );
    CHECK_THROWS_WITH(parse_str("x_z"), "invalid input");

    CHECK(parse_str("x + y")->equals(new AddExpr(new VarExpr("x"), new VarExpr("y"))));
    CHECK(parse_str("x * y")->equals(new MultExpr(new VarExpr("x"), new VarExpr("y"))));
    CHECK(parse_str("z * x + y")
                   ->equals(new AddExpr(new MultExpr(new VarExpr("z"), new VarExpr("x")),
                                    new VarExpr("y"))));
    CHECK(parse_str("z * (x + y)")
                   ->equals(new MultExpr(new VarExpr("z"),
                                     new AddExpr(new VarExpr("x"), new VarExpr("y")))));

    CHECK_THROWS_WITH( parse_str("_leet x = 5 _in 1"), "bad input");
    CHECK_THROWS_WITH( parse_str("_let x 5 _in 1"), "bad input");
    CHECK_THROWS_WITH( parse_str("_let x = 5 _on 1"), "bad input");

    CHECK( parse_str("  _let  x  =  5  _in  x  +  1")->equals(new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1)))) );
    CHECK( parse_str("_let x=5 _in (_let y = 3 _in y+2)+x")
                   ->equals(new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x")))) );
}
