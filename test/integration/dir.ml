
open Test_framework
open Reason_ls

    module R = Dir.RENDER(struct let pipe = "|" let middle = "|--" let last = "`--" end)
let test_render_tree { expect } = 
    let tree = Dir.([
        Dir("A",0,false);
        Dir("A1",1,true);
        Dir("B",0,false);
        Dir("B1",1,false);
        Dir("B2",1,true);
        Dir("C",0,true)
        ]) in
    let actual = R.compile_tree tree in
    (expect.string actual).toMatchSnapshot ()

let _ = describe "Compile a basic tree" (fun {test} -> 
    test "creates correct string representation" test_render_tree
)