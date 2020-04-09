open Test_framework;
open Reason_ls;

/** Integration test suite that performs smoke tests. */

let test_version = ({expect}) => {
  let version = Test_utils.run([|"--version"|]);
  let generated = String.strip(version);
  expect.string(generated).toEqual("%%VERSION%%");
};

describe("Integration test --version", ({test, _}) => {
  test("can display the version", test_version)
});
