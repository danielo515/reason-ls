open Test_framework;
open Reason_ls;

/** Test suite for the Utils module. */

let test_hello_with_name = (name, {expect}) => {
  let greeting = Utils.greet(name);
  let expected = "Hello " ++ name ++ "!";
  expect.string(greeting).toEqual(expected);
};

describe("Utils", ({test, _}) => {
  test("can greet Tom", test_hello_with_name("Tom"));
  test("can greet John", test_hello_with_name("John"));
});