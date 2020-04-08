type file = File of string * int * bool| Dir of string * int * bool

let string_of_file = function
| Dir (name, depth, is_last) 
| File (name,depth, is_last) -> (if(is_last) then "└ " else "├ ") ^ name 

let depth_of_file = function
| Dir (_, depth, _) | File (_,depth, _) -> depth

let render_row file below_files =
    let len = depth_of_file file in
    let segments = Array.create ~len " " in
    let rec loop cur_depth remain = 
    if cur_depth = 0 then segments
    else match remain with
    | f::tail -> 
        let depth = depth_of_file f in
        if depth < cur_depth then begin 
            segments.(depth_of_file f) <- "│";
            loop depth tail
            end
        else loop cur_depth tail
    | [] -> segments
    in
    loop len below_files |> String.concat_array

let compile_tree tree = 
    let rec loop res = function
    | f::tail -> 
        let res =  res ^ render_row f tail ^ string_of_file f ^ "\n" in 
        loop res tail
    | [] -> res
    in
    loop "" tree

let fold_right arr ~init ~f =
    snd @@ 
    Array.fold_right arr ~init:(true, init) ~f: (fun i (is_last,acc) -> (false, f i acc is_last))

let traverse dir  = 
    let rec loop path depth =
        let files = Caml.Sys.readdir path in
        let fold file acc is_last = 
            let path = Caml.Filename.concat path file in
            if Caml.Sys.is_directory path then  
            Dir (file,depth, is_last)  :: (loop path (depth+1)) @ acc
            else File (file,depth, is_last) :: acc
        in
        fold_right files ~init: [] ~f: fold             
    in
    loop dir 0