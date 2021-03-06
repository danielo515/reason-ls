open Cmdliner;
open Reason_ls;

let defaultCmd = {
  let doc = "list directory as a tree, reasonml implementaion";

  let path =
    Arg.(
      required
      & pos(0, some(string), None)
      & info([], ~docv="PATH", ~doc="the path")
    );
  let charset =
    Arg.(
      value
      & opt(string, "unicode")
      & info(["c", "charset"], ~doc="charset to use")
    );

  let run = (dir, charset) => {
    let (p, m, l) =
      switch (charset) {
      | "ascii" => ("|", "|--", "`--")
      | _ => ("│", "├", "└")
      };
    module R =
      Dir.RENDER({
        let pipe = p;
        let middle = m;
        let last = l;
      });
    let run_cmd = () => dir ++ "\n" ++ (Dir.traverse(dir) |> R.compile_tree);
    run_cmd |> Errors.handle_errors |> Console.log;
  };
  Reason_ls.(
    Term.(const(run) $ path $ charset),
    Term.info(
      "reason-ls",
      ~doc,
      ~envs=Man.envs,
      ~version=Man.version,
      ~exits=Man.exits,
      ~man=Man.man,
      ~sdocs=Man.sdocs,
    ),
  );
};

let argv =
  Sys.get_argv()
  |> Array.map(~f=arg =>
       switch (arg) {
       | "-v" => "--version"
       | "-h" => "--help"
       | x => x
       }
     );

let _ = Term.exit @@ Term.eval(defaultCmd, ~argv);
