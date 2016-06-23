(* Interface Case *)
module type CONTACT =
 sig
  type status  =  int
  type p1      =  bool
  type p2      =  bool
  type p3      =  bool
  type p4      =  bool
  type t

  val create : status -> p1 -> p2 -> p3 -> p4 -> t

  val get_status  : t -> status
  val get_p1      : t -> p1
  val get_p2      : t -> p2
  val get_p3      : t -> p3
  val get_p4      : t -> p4

  val print       : t -> unit
  val islink      : t -> bool
  val set_p1      : int -> t -> t
  val set_p2      : int -> t -> t
  val set_p3      : int -> t -> t
  val set_p4      : status -> t -> t
end

module Contact : CONTACT
