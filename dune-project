(lang dune 2.0)
(name reason-ls)
(source (github danielo515/reason-ls))
(documentation "https://github.com/danielo515/reason-ls")
(license MIT)
(authors "Danielo")
(maintainers "Danielo")

(generate_opam_files true)

(package
 (name reason-ls)
 (synopsis "learning reason building a simple cli")
 (description "\
learning reason building a simple cli
")
 (depends
  (ocaml (>= 4.06.0))
  (dune (>= 2.0))
  ; Add Rely when released on Opam
  ; (rely :with-test)
  (odoc :with-doc)
  (reason :build)
  base
  cmdliner
  lwt
  stdio))
