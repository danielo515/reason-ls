open Cmdliner;

let man = [
  `S(Manpage.s_common_options),
  `S(Manpage.s_environment),
  `P("These environment variables affect the execution of $(mname):"),
  `Noblank,
  `S(Manpage.s_bugs),
  `P("File bug reports at https://github.com/danielo515/reason-ls"),
];

let version = Package.version;

let envs =
  Reason_ls.Config.all
  |> Reason_ls.Errors.handle_errors
  |> List.map(~f=el =>
       Reason_ls.Config.(
         Term.env_info(
           ~doc=Printf.sprintf("%s\ndefaults to \"%s\"", el.doc, el.default),
           el.name,
         )
       )
     );

let sdocs = Manpage.s_common_options;

let exits =
  List.concat([
    Reason_ls.Errors.all()
    |> List.map(~f=el =>
         Reason_ls.Errors.(Term.exit_info(el.exit_code, ~doc=el.doc))
       ),
    Term.default_exits,
  ]);
