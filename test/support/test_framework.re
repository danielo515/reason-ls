/** Initialize the test framework.

    Here we are specifying where snapshots should be stored as well as
    the root directory of your project for the formatting of terminal output. */
let ic = Unix.open_process_in("uname");
let uname = Stdio.In_channel.input_line(ic);
let _ = Stdio.In_channel.close(ic);
let snapshotDir =
  switch (uname) {
  | Some("Linux") => "test/_snapshots/unix"
  | _ => "test/_snapshots"
  };
include Rely.Make({
  let config =
    Rely.TestFrameworkConfig.initialize({snapshotDir, projectDir: ""});
});
