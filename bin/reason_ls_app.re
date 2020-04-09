open Cmdliner;

let defaultCmd = {
  let doc = "list directory as a tree, reasonml implementaion";

  let path =
    Arg.(
      required
      & pos(0, some(string), None)
      & info([], ~docv="PATH", ~doc="the path")
    );

  Reason_ls.(
    Term.(
      const(dir => {
        module R =
          Dir.RENDER({
            let pipe = "│";
            let middle = "├";
            let last = "└";
          });
        dir ++ "\n" ++ (Dir.traverse(dir) |> R.compile_tree) |> Console.log;
      })
      $ path
    ),
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
