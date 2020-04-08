type file = File of string * int | Dir of string * int 

let string_of_file = function
|Dir (name, depth) | File (name,depth) -> String.make ( depth+1 ) '-' ^ name

let traverse dir  = 
    let rec loop path depth =
        let files = Caml.Sys.readdir path in
        let fold file acc = 
            let path = Caml.Filename.concat path file in
            if Caml.Sys.is_directory path then  
            Dir (file,depth)  :: (loop path (depth+1)) @ acc
            else File (file,depth) :: acc
        in
        Array.fold_right files ~init: [] ~f: fold             
    in
    loop dir 0