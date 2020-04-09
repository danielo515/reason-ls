open Test_framework;
open Reason_ls;

/** Integration test suite for the hello command. */

let test_hello_world = ({expect}) => {
  let output = Test_utils.run([|"hello", "World"|]);
  let generated = String.strip(output);
  expect.string(generated).toEqual("Hello World!");
};

describe("Integration test hello", ({test, _}) => {
  test("can display hello world", test_hello_world)
});
