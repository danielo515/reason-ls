open Reason_ls;

/** Create a new temporary directory.

    The directory name will be prefixed with "reason-ls-test-" and will be suffixed with a timestamp. */
let get_tempdir = name => {
  Printf.sprintf(
    "reason-ls-test-%s-%s",
    name,
    Unix.time() |> Float.to_int |> Int.to_string,
  )
  |> Caml.Filename.concat(Caml.Filename.get_temp_dir_name());
};

let exe_path =
  Lwt_process.pread_chars(("", [|"esy", "x", "which", "reason-ls"|]))
  |> Lwt_stream.to_string
  |> Lwt.map(String.strip)
  |> Lwt_main.run;

/** Run reason-ls binary with the given arguments and return the standard output. */
let run = args => {
  let arguments = Array.append([|exe_path|], args);

  let env =
    Unix.environment()
    |> Array.append([|
         Printf.sprintf(
           "%s=%s",
           Reason_ls.Config.REASON_LS_CACHE_DIR.name,
           get_tempdir("cache_dir"),
         ),
       |]);

  Lwt_process.pread_chars(~env, ("", arguments))
  |> Lwt_stream.to_string
  |> Lwt_main.run;
};
