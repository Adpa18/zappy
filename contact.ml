(* Module Case *)
module type CONTACT =
 sig
  type contact = {mutable All: string; mutable Id: int;
 mutable Name: string; mutable Surname: string; mutable Age: int; mutable Email: string; mutable Phone: string; };

  val add : contact list -> string * string * int * string * string -> contact list
  val getId : contact list -> field -> string -> int
  val remove : contact list -> int -> contact list
  val replace : contact list -> int -> string * string * int * string * string -> contact list
  val print : contact list -> field -> string -> unit
end

module Contact : CONTACT =
 struct
  
end
