module Filename = {
  let ensure_trailing = s =>
    switch (Caml.String.get(s, Caml.String.length(s) - 1)) {
    | '/' => s
    | _ => s ++ "/"
    };
};

let greet = name => "Hello " ++ name ++ "!";
  /** [dir_is_empty dir] is true, if [dir] contains no files except
 * "." and ".."
 */
let dir_is_empty = dir => Array.length(Caml.Sys.readdir(dir)) == 0;

/** [dir_contents] returns the paths of all regular files that are
 * contained in [dir]. Each file is a path starting with [dir].
  */
let dir_contents = dir => {
  open Caml
  let rec loop = result =>
    fun
    | [f, ...fs] when Sys.is_directory(f) =>
      Sys.readdir(f)
      |> Array.to_list
      |> List.map(Caml.Filename.concat(f))
      |> List.append(fs)
      |> loop(result)
    | [f, ...fs] => loop([f, ...result], fs)
    | [] => result;

  loop([], [dir]);
};
