open Cmdliner;

let defaultCmd = {
  let doc = "list directory as a tree, reasonml implementaion";

  let path = Arg.( required 
  & pos(0, some( string ),None) 
  & info([],~docv="path", ~doc="the path")
  );

  Reason_ls.((     
  Term.(const( dir => Utils.dir_contents(dir) 
  |> List.fold(~init="", ~f=(a,b) => a ++ "\n" ++ b )
  |> Console.log) $ path),
    Term.info(
      "reason-ls",
      ~doc,
      ~envs=Man.envs,
      ~version=Man.version,
      ~exits=Man.exits,
      ~man=Man.man,
      ~sdocs=Man.sdocs,
    ))
  );
};

let argv =
  Sys.get_argv()
  |> Array.map(~f=arg =>
       switch (arg) {
       | "-v" => "--version"
       | x => x
       }
     );

let _ = Term.exit @@ Term.eval(defaultCmd, ~argv);
