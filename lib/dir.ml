type file = File of string * int * bool| Dir of string * int * bool

let string_of_file = function
| Dir (name, depth, is_last) 
| File (name,depth, is_last) -> String.make ( depth+1 ) ' ' ^ (if(is_last) then "`" else "-") ^ name

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