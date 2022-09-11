open Test_framework;
open Reason_ls;

/** Integration test suite for the hello command. */

let test_ls_tree = ({expect}) => {
  let output = Test_utils.run([|"./test/Dummy", "-c", "ascii"|]);
  let generated = String.strip(output);
  Console.log("\nstart'" ++ generated ++ "'end");
  expect.string(generated).toMatchSnapshot();
};

/**
describe("Integration test ls-tree", ({test, _}) => {
  test("renders the test directory", test_ls_tree)
});
*/
